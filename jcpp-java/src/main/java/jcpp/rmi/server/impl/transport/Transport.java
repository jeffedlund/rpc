package jcpp.rmi.server.impl.transport;

import java.io.IOException;

import java.net.ServerSocket;
import java.net.Socket;

import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Future;

import edu.emory.mathcs.backport.java.util.concurrent.ScheduledExecutorService;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import jcpp.rmi.server.impl.gateway.GatewaySocketFactory;


public class Transport {
    private static Log log = LogFactory.getLog(Transport.class);
    private Set<ConnectionHeaderReader> connectionReaders;
    private ExecutorService executorService;
    private Future<Void> future;
    private EndPoint localEndPoint;
    private Map<EndPoint, Connections> remoteConnectionsMap;
    private ScheduledExecutorService scheduledExecutorService;
    private ServerSocket serverSocket;
    private TransportConfiguration transportConfiguration;
    private ITransportDispatcher transportDispatcher;
    private ITransportRouter transportRouter;


    public Transport(EndPoint localEndPoint, ITransportRouter transportRouter, ITransportDispatcher transportDispatcher, ExecutorService executorService, ScheduledExecutorService scheduledExecutorService,
        TransportConfiguration transportConfiguration) {
        this.localEndPoint = localEndPoint;
        this.transportRouter = transportRouter;
        this.transportDispatcher = transportDispatcher;
        this.scheduledExecutorService = scheduledExecutorService;
        this.remoteConnectionsMap = new HashMap<EndPoint, Connections>();
        this.executorService = executorService;
        this.transportConfiguration = transportConfiguration;
        this.connectionReaders = Collections.synchronizedSet(new HashSet<ConnectionHeaderReader>());
    }


    public synchronized Connections getConnections(EndPoint remoteEndPoint) {
        Connections connections = remoteConnectionsMap.get(remoteEndPoint);
        if (connections == null) {
            connections = new Connections(remoteEndPoint, this);
            remoteConnectionsMap.put(remoteEndPoint, connections);
        }
        return connections;
    }

    public EndPoint getLocalEndPoint() {
        return localEndPoint;
    }

    public ScheduledExecutorService getScheduledExecutorService() {
        return scheduledExecutorService;
    }

    public TransportConfiguration getTransportConfiguration() {
        return transportConfiguration;
    }

    public ITransportDispatcher getTransportDispatcher() {
        return transportDispatcher;
    }

    public ITransportRouter getTransportRouter() {
        return transportRouter;
    }

    public void export() throws IOException {
        serverSocket = GatewaySocketFactory.createServerSocket(localEndPoint.getPort(), transportConfiguration.getGatewayConfiguration());
        localEndPoint.setPort(serverSocket.getLocalPort());

        future = executorService.submit(new Callable<Void>() {
                    @Override
                    public Void call() {
                        Thread.currentThread().setName("Transport Accept Socket thread - [Port:" + localEndPoint.getPort() + "] [ServerSocket:" + serverSocket + "]");
                        while ((serverSocket != null) && !serverSocket.isClosed()) {
                            try {
                                Socket socket = serverSocket.accept();
                                ConnectionHeaderReader connectionHeaderReader = new ConnectionHeaderReader(socket, Transport.this);
                                connectionReaders.add(connectionHeaderReader);
                                executorService.submit(connectionHeaderReader);
                            } catch (Throwable throwable) {
                                if (!serverSocket.isClosed() && log.isDebugEnabled()) {
                                    log.debug("Error while accepting socket.", throwable);
                                }
                            }
                        }
                        return null;
                    }
                });
    }

    public void unexport() throws IOException {
        Connections[] connectionsArray;
        ConnectionHeaderReader[] readers;
        synchronized (this) {
            connectionsArray = remoteConnectionsMap.values().toArray(new Connections[0]);
            readers = connectionReaders.toArray(new ConnectionHeaderReader[0]);
        }
        try {
            serverSocket.close();
        } catch (IOException e) {
            log.debug("Unable to close serverSocket while unexport() in Transport: " + localEndPoint, e);
        }
        future.cancel(false);
        for (ConnectionHeaderReader reader : readers) {
            reader.unexport();
        }
        for (Connections connections : connectionsArray) {
            connections.killAll();
        }
        synchronized (this) {
            connectionReaders.clear();
            remoteConnectionsMap.clear();
        }
    }

    protected synchronized void remove(ConnectionHeaderReader reader) throws IOException {
        connectionReaders.remove(reader);
    }

    protected synchronized void remove(Connections connections) throws IOException {
        remoteConnectionsMap.remove(connections.getRemoteEndPoint());
    }

}
