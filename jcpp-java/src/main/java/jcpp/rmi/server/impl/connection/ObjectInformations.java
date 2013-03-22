package jcpp.rmi.server.impl.connection;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;

import java.util.HashMap;
import java.util.IdentityHashMap;
import java.util.Map;

import jcpp.rmi.server.impl.transport.Transport;


public class ObjectInformations {
    private Map<String, ObjectInformation> idMap;
    private Map<Object, ObjectInformation> objectMap;
    private Transport transport;
    private ILifecycle lifecycle;
    private Server server;
    private GC gc;
    private GCClient gcClient;
    private IInvocationListener invocationListener;
    private MethodDigester methodDigester;


    public ObjectInformations(ILifecycle lifecycle, Server server, GC gc, GCClient gcClient,IInvocationListener invocationListener) {
        this.idMap = new HashMap<String, ObjectInformation>();
        this.objectMap = new IdentityHashMap<Object, ObjectInformation>();
        this.lifecycle = lifecycle;
        this.server = server;
        this.gc = gc;
        this.gcClient = gcClient;
        this.invocationListener = invocationListener;
        this.methodDigester = new MethodDigester();
    }


    public void setTransport(Transport transport) {
        this.transport = transport;
    }

    public Transport getTransport() {
        return transport;
    }

    public Server getServer() {
        return server;
    }

    public GC getGC() {
        return gc;
    }

    public GCClient getGCClient() {
        return gcClient;
    }

    public IInvocationListener getInvocationListener() {
        return invocationListener;
    }

    public MethodDigester getMethodDigester() {
        return methodDigester;
    }

    public void export(String id, Object object, Class<?>[] interfaces) throws IOException, ConnectionException {
        ObjectInformation objInfo;
        synchronized (this) {
            if (idMap.get(id) != null) {
                throw new ConnectionException("Object[" + object.toString() + "] with ID[" + id + "] already exists in ObjectInformations idMap");
            }
            if (objectMap.get(object) != null) {
                throw new ConnectionException("Object[" + object.toString() + "] with ID[" + id + "] already exists in ObjectInformations objectMap");
            }
            objInfo = new ObjectInformation(id, object, interfaces, this, lifecycle, gc);
            idMap.put(id, objInfo);
            objectMap.put(object, objInfo);
            if (idMap.size() == 1) {
                transport.export();
            }
        }

        objInfo.exported();
    }

    public ObjectInformation unexport(String id) throws IOException {
        ObjectInformation objInfo = remove(id);
        if (objInfo != null) {
            objInfo.unexport();
        }
        return objInfo;
    }

    public ObjectInformation unexport(Object object) throws IOException {
        ObjectInformation objInfo;
        synchronized (this) {
            objInfo = objectMap.get(object);
        }
        if (objInfo != null) {
            return unexport(objInfo.getId());
        }
        return null;
    }

    public void unexport() throws IOException {
        ObjectInformation[] objInfoArray;
        synchronized (this) {
            objInfoArray = idMap.values().toArray(new ObjectInformation[0]);
            idMap.clear();
            objectMap.clear();
        }
        for (ObjectInformation objInfo : objInfoArray) {
            objInfo.unexport();
        }
        transport.unexport();
        methodDigester.clear();
    }

    public synchronized String[] list() {
        return idMap.keySet().toArray(new String[0]);
    }

    public synchronized ObjectInformation getObjectInformation(String id) {
        return idMap.get(id);
    }

    public synchronized ObjectInformation getObjectInformation(Object object) {
        return objectMap.get(object);
    }

    @Override
    public String toString() {
        return "" + objectMap;
    }

    protected ObjectInformation remove(String id) throws IOException {
        ObjectInformation objInfo;
        synchronized (this) {
            objInfo = idMap.remove(id);
            if (objInfo != null) {
                objectMap.remove(objInfo.getObject());
                if (idMap.size() == 0) {
                    transport.unexport();
                }
            }
        }
        return objInfo;
    }
}
