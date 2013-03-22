package jcpp.rmi.server.impl.connection;

import java.io.IOException;

import java.lang.management.ManagementFactory;
import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Method;
import java.lang.reflect.Proxy;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Hashtable;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import javax.management.MalformedObjectNameException;
import javax.management.ObjectName;

import edu.emory.mathcs.backport.java.util.concurrent.ScheduledExecutorService;

import jcpp.rmi.server.impl.connection.serialization.INotSerializableObjectHandler;
import jcpp.rmi.server.impl.transport.EndPoint;
import jcpp.rmi.server.impl.transport.ITransportRouter;
import jcpp.rmi.server.impl.transport.Transport;


public class Server implements IServer {
    private static final String NANO_TIMER_PROVIDER_PROP = "edu.emory.mathcs.backport.java.util.concurrent.NanoTimerProvider";
    private static Map<Integer, Server> servers = Collections.synchronizedMap(new LinkedHashMap<Integer, Server>());
    private static int globalId;

    private EndPoint endPoint;
    private int id;
    private IRegistry registry;
    private Transport transport;
    private ObjectInformations objectInformations;
    private LifecycleImpl lifecycleImpl;
    private List<ILifecycle> lifecycles;
    private GCClientListenerImpl gcClientListenerImpl;
    private List<IGCClientListener> gcClientListeners;
    private InvocationListenerImpl invocationListenerImpl;
    private List<IInvocationListener> invocationListeners;
    private INotExportedObjectListener notExportedObjectListener;
    private INotSerializableObjectHandler notSerializableObjectHandler;
    private GC gc;
    private GCClient gcClient;
    private ScheduledExecutorService scheduledExecutorService;
    private ExecutorService executorService;
    private ConnectionTransportDispatcher connectionTransportDispatcher;
    private ConnectionConfiguration connectionConfiguration;
    private IInvocationExceptionHandler invocationExceptionHandler;


    protected Server(EndPoint endPoint, ITransportRouter transportRouter, ConnectionConfiguration connectionConfiguration) throws Exception {
        this.endPoint = endPoint;
        synchronized (Server.class) {
            this.id = globalId++;
        }
        this.connectionConfiguration = connectionConfiguration;
        this.lifecycles = new ArrayList<ILifecycle>();
        this.lifecycleImpl = new LifecycleImpl();
        this.gcClientListeners = new ArrayList<IGCClientListener>();
        this.gcClientListenerImpl = new GCClientListenerImpl();
        this.invocationListeners = new ArrayList<IInvocationListener>();
        this.executorService = Executors.newCachedThreadPool();

        System.setProperty(NANO_TIMER_PROVIDER_PROP, "edu.emory.mathcs.backport.java.util.concurrent.helpers.Utils$MillisProvider");
        this.scheduledExecutorService = edu.emory.mathcs.backport.java.util.concurrent.Executors.newScheduledThreadPool(connectionConfiguration.getExecutorCorePoolSize());

        this.gc = new GC(executorService, scheduledExecutorService, connectionConfiguration);
        this.gcClient = new GCClient(this, gcClientListenerImpl);
        this.objectInformations = new ObjectInformations(lifecycleImpl, this, gc, gcClient, invocationListenerImpl);
        this.connectionTransportDispatcher = new ConnectionTransportDispatcher(objectInformations);
        this.transport = new Transport(endPoint, transportRouter, connectionTransportDispatcher, executorService, scheduledExecutorService, connectionConfiguration.getTransportConfiguration());
        this.objectInformations.setTransport(transport);
        this.registry = new Registry(objectInformations);
        this.registry.bind(IRegistry.class.getName(), registry, new Class[] { IRegistry.class });
        this.registry.bind(IServer.class.getName(), this, new Class[] { IServer.class });
        this.registry.bind(IGC.class.getName(), gc, new Class[] { IGC.class });
        this.registry.bind(IGCClient.class.getName(), gcClient, new Class[] { IGCClient.class });
        servers.put(id, this);
    }


    public static Server create(EndPoint endPoint, ITransportRouter transportRouter,  ConnectionConfiguration connectionConfiguration) throws Exception {
        return new Server(endPoint, transportRouter, connectionConfiguration);
    }

    public static IServer getRemoteServer(Object object) throws Exception {
        if (Proxy.isProxyClass(object.getClass())) {
            ObjectHandler objectHandler = getObjectHandlerFromProxy(object);
            ObjectPointer objectPointer = objectHandler.getInvoker().getObjectPointer();
            return objectHandler.getInvoker().getObjectInformations().getServer().lookup(objectPointer.getEndPoint(), IServer.class);
        }
        return getServerFromExportedObject(object);
    }

    public static IServer getLocalServer(Object object) throws Exception {
        ObjectHandler objectHandler = getObjectHandlerFromProxy(object);
        return objectHandler.getInvoker().getObjectInformations().getServer();
    }

    public static Server[] getServers() {
        return servers.values().toArray(new Server[0]);
    }

    public static Server getServer(int id) {
        return servers.get(id);
    }

    public static String getHost(Object object) throws Exception {
        return getEndPoint(object).getHost();
    }

    public static int getPort(Object object) throws Exception {
        return getEndPoint(object).getPort();
    }

    public static String getSite(Object object) throws Exception {
        return getEndPoint(object).getSite();
    }

    public static EndPoint getEndPoint(Object object) throws Exception {
        if (Proxy.isProxyClass(object.getClass())) {
            ObjectPointer objectPointer = getObjectHandlerFromProxy(object).getInvoker().getObjectPointer();
            return objectPointer.getEndPoint();
        }
        return getServerFromExportedObject(object).getEndPoint();
    }

    public static String getId(Object object) throws Exception {
        ObjectPointer objectPointer = null;
        if (Proxy.isProxyClass(object.getClass())) {
            objectPointer = getObjectHandlerFromProxy(object).getInvoker().getObjectPointer();
        } else {
            Server server = getServerFromExportedObject(object);
            ObjectHandler objectHandler = server.getObjectInformations().getObjectInformation(object).getObjectHandler();
            objectPointer = objectHandler.getInvoker().getObjectPointer();
        }
        return objectPointer.getId();
    }

    @Override
    public <T> T lookup(EndPoint endPoint, Class<T> clazz) {
        return clazz.cast(lookup(clazz.getName(), endPoint, clazz.getClassLoader(), new Class[] { clazz }));
    }

    public Object lookup(String id, EndPoint endPoint, ClassLoader classLoader, Class<?>[] interfaces) {
        ObjectHandler objectHandler = new ObjectHandler(objectInformations, classLoader, interfaces, new ObjectPointer(endPoint, id));
        return objectHandler.getProxy();
    }

    @Override
    public IRegistry getRegistry() {
        return registry;
    }

    public EndPoint getEndPoint() {
        return endPoint;
    }

    @Override
    public IGC getGC() {
        return gc;
    }

    @Override
    public IGCClient getGCClient() {
        return gcClient;
    }

    public ExecutorService getExecutorService() {
        return executorService;
    }

    public ScheduledExecutorService getScheduledExecutorService() {
        return scheduledExecutorService;
    }

    public ObjectInformations getObjectInformations() {
        return objectInformations;
    }

    public ConnectionTransportDispatcher getConnectionTransportDispatcher() {
        return connectionTransportDispatcher;
    }

    public ConnectionConfiguration getConnectionConfiguration() {
        return connectionConfiguration;
    }

    public INotExportedObjectListener getNotExportedObjectListener() {
        return notExportedObjectListener;
    }

    public void setNotExportedObjectListener(INotExportedObjectListener notExportedObjectListener) {
        this.notExportedObjectListener = notExportedObjectListener;
    }

    public INotSerializableObjectHandler getNotSerializableObjectHandler() {
        return notSerializableObjectHandler;
    }

    public void setNotSerializableObjectHandler(INotSerializableObjectHandler notSerializableObjectHandler) {
        this.notSerializableObjectHandler = notSerializableObjectHandler;
    }

    public IInvocationExceptionHandler getInvocationExceptionHandler() {
        return invocationExceptionHandler;
    }

    public void setInvocationExceptionHandler(IInvocationExceptionHandler invocationExceptionHandler) {
        this.invocationExceptionHandler = invocationExceptionHandler;
    }

    public void unexport() throws IOException {
        servers.remove(this.id);
        gcClient.unexport();
        gc.unexport();
        objectInformations.unexport();
        scheduledExecutorService.shutdownNow();
        executorService.shutdownNow();
    }

    @Override
    public String toString() {
        return "Server[" + endPoint + ", " + transport + "]";
    }

    public void addLifecycle(ILifecycle lifecycle) {
        lifecycles.add(lifecycle);
    }

    public void removeLifecycle(ILifecycle lifecycle) {
        lifecycles.remove(lifecycle);
    }

    public void addGCClientListener(IGCClientListener gcClientListener) {
        gcClientListeners.add(gcClientListener);
    }

    public void removeGCClientListener(IGCClientListener gcClientListener) {
        gcClientListeners.remove(gcClientListener);
    }

    public void addIInvocationListener(IInvocationListener invocationListener) {
        invocationListeners.add(invocationListener);
    }

    public void removeIInvocationListener(IInvocationListener invocationListener) {
        invocationListeners.remove(invocationListener);
    }

    private static ObjectHandler getObjectHandlerFromProxy(Object object) throws Exception {
        if (Proxy.isProxyClass(object.getClass())) {
            InvocationHandler invocationHandler = Proxy.getInvocationHandler(object);
            if (invocationHandler instanceof ObjectHandler) {
                ObjectHandler objectHandler = (ObjectHandler) invocationHandler;
                return objectHandler;
            }
            throw new Exception("The Proxy object: " + object + " is not an instance of ObjectHandler.");
        }
        throw new Exception("The object: " + object + " is not of type Proxy.");
    }

    private static Server getServerFromExportedObject(Object object) throws Exception {
        Collection<Server> servers = null;
        synchronized (Server.servers) {
            servers = Server.servers.values();
        }
        if (servers != null) {
            for (Server server : servers) {
                if (server.getObjectInformations().getObjectInformation(object) != null) {
                    return server;
                }
            }
        }
        throw new Exception("Unable to find a remote server for the object: " + object + ". The object is not of type Proxy, and has not been exported locally.");
    }

    private class LifecycleImpl implements ILifecycle {

        @Override
        public void export(ObjectInformation objectInformation, EndPoint endPoint) {
            for (ILifecycle lifecycle : lifecycles) {
                lifecycle.export(objectInformation, endPoint);
            }
        }

        @Override
        public void unexport(ObjectInformation objectInformation) {
            for (ILifecycle lifecycle : lifecycles) {
                lifecycle.unexport(objectInformation);
            }
        }

        @Override
        public void export(ObjectInformation objectInformation) {
            for (ILifecycle lifecycle : lifecycles) {
                lifecycle.export(objectInformation);
            }
        }

        @Override
        public void unexport(ObjectInformation objectInformation, EndPoint endPoint) {
            for (ILifecycle lifecycle : lifecycles) {
                lifecycle.unexport(objectInformation, endPoint);
            }
        }
    }

    private class GCClientListenerImpl implements IGCClientListener {

        @Override
        public void objectAlive(EndPoint endPoint, Object[] objects) {
            for (IGCClientListener gcClientListener : gcClientListeners) {
                gcClientListener.objectAlive(endPoint, objects);
            }
        }

        @Override
        public void objectDead(EndPoint endPoint, Object[] objects) {
            for (IGCClientListener gcClientListener : gcClientListeners) {
                gcClientListener.objectDead(endPoint, objects);
            }
        }

        @Override
        public void objectDead(EndPoint endPoint, Object[] objects, Throwable throwable) {
            for (IGCClientListener gcClientListener : gcClientListeners) {
                gcClientListener.objectDead(endPoint, objects, throwable);
            }
        }

        @Override
        public void objectMaybeDead(EndPoint endPoint, Object[] objects, Throwable throwable) {
            for (IGCClientListener gcClientListener : gcClientListeners) {
                gcClientListener.objectMaybeDead(endPoint, objects, throwable);
            }
        }

    }

    private class InvocationListenerImpl implements IInvocationListener {

        @Override
        public void invocationFailed(Object proxy, Method method, Object[] args, Throwable e) {
            for (IInvocationListener invocationListener : invocationListeners) {
                invocationListener.invocationFailed(proxy, method, args, e);
            }
        }

        @Override
        public void invocationSucceeded(Object proxy, Method method, Object[] args) {
            for (IInvocationListener invocationListener : invocationListeners) {
                invocationListener.invocationSucceeded(proxy, method, args);
            }
        }

    }
}
