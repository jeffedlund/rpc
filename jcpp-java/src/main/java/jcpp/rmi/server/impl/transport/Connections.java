package jcpp.rmi.server.impl.transport;

import java.io.IOException;

import java.util.ArrayList;
import java.util.List;

import edu.emory.mathcs.backport.java.util.concurrent.ScheduledFuture;
import edu.emory.mathcs.backport.java.util.concurrent.TimeUnit;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import jcpp.rmi.server.impl.gateway.Route;


public class Connections {
    private static Log log = LogFactory.getLog(Connections.class);
    private EndPoint remoteEndPoint;
    private List<Connection> freeConnectionList;
    private List<Connection> takenConnectionList;
    private Transport transport;
    private long connectionTimeout;
    private ThreadLocal<Boolean> limitInvocationTime;
    private ScheduledFuture scheduledFuture;


    public Connections(EndPoint remoteEndPoint, Transport transport) {
        this.remoteEndPoint = remoteEndPoint;
        this.transport = transport;
        this.freeConnectionList = new ArrayList<Connection>();
        this.takenConnectionList = new ArrayList<Connection>();
        this.connectionTimeout = transport.getTransportConfiguration().getConnectionPoolTimeout();
        this.limitInvocationTime = new ThreadLocal<Boolean>() {
            @Override
            protected Boolean initialValue() {
                return Boolean.FALSE;
            }
        };
        launchTimeoutTimer();
    }


    public synchronized Connection createConnection() throws Exception {
        int socketTimeout = limitInvocationTime.get() ? transport.getTransportConfiguration().getLimitedSocketTimeout() : transport.getTransportConfiguration().getSocketTimeout();
        while (freeConnectionList.size() > 0) {
            Connection connection = freeConnectionList.remove(0);
            if (!connection.isDead()) {
                takenConnectionList.add(connection);
                connection.getSocket().setSoTimeout(socketTimeout);
                return connection;
            }
        }
        Route route = transport.getTransportRouter().findRoute(transport.getLocalEndPoint().getSite(), remoteEndPoint);
        if ((route == null) || (route.getAddressList().size() == 0)) {
            throw new IOException("No route found from [" + transport.getLocalEndPoint() + "] to [" + remoteEndPoint + "]");
        }
        Connection connection = new Connection(route, this,  transport.getTransportConfiguration().getGatewayConfiguration());
        takenConnectionList.add(connection);
        connection.getSocket().setSoTimeout(socketTimeout);
        return connection;
    }

    public void setInvocationTimeLimit() {
        this.limitInvocationTime.set(Boolean.TRUE);
    }

    public void removeInvocationTimeLimit() {
        this.limitInvocationTime.set(Boolean.FALSE);
    }

    public long getConnectionTimeout() {
        return this.connectionTimeout;
    }

    public synchronized void freeAll() {
        for (Connection connection : takenConnectionList.toArray(new Connection[0])) {
            connection.free();
        }
    }

    public synchronized void killAll() throws IOException {
        for (Connection connection : takenConnectionList.toArray(new Connection[0])) {
            connection.kill();
        }
        for (Connection connection : freeConnectionList.toArray(new Connection[0])) {
            connection.kill();
        }
        takenConnectionList.clear();
        freeConnectionList.clear();
        remove();
    }

    public EndPoint getRemoteEndPoint() {
        return remoteEndPoint;
    }

    public Transport getTransport() {
        return transport;
    }

    @Override
    public String toString() {
        return "Connections[localEndPoint=" + transport.getLocalEndPoint() + ", remoteEndPoint=" + remoteEndPoint + "]";
    }

    protected synchronized void free(Connection connection) {
        if (takenConnectionList.remove(connection)) {
            connection.setLastUsed();
            freeConnectionList.add(0, connection);
        }
    }

    protected synchronized void kill(Connection connection) throws IOException {
        boolean wasTaken = takenConnectionList.remove(connection);
        boolean wasFree = freeConnectionList.remove(connection);
        if (takenConnectionList.isEmpty() && freeConnectionList.isEmpty()) {
            remove();
        }
    }

    private void remove() throws IOException {
        scheduledFuture.cancel(true);
        transport.remove(this);
    }

    private void launchTimeoutTimer() {
        scheduledFuture = transport.getScheduledExecutorService().scheduleAtFixedRate(new ConnectionTimeOutRunnable(), transport.getTransportConfiguration().getTimeoutTimerInterval(),
                transport.getTransportConfiguration().getTimeoutTimerInterval(), TimeUnit.MILLISECONDS);
    }


    protected class ConnectionTimeOutRunnable implements Runnable {

        public ConnectionTimeOutRunnable() {
        }


        @Override
        public void run() {
            String oldName = Thread.currentThread().getName();
            try {
                Thread.currentThread().setName("Connections Timeout Thread - " + Connections.this.toString());
                Connection[] freeArray;
                synchronized (this) {
                    freeArray = freeConnectionList.toArray(new Connection[0]);
                }
                long currentTime = System.currentTimeMillis();
                for (Connection connection : freeArray) {
                    long diff = currentTime - connection.getLastUsed();
                    if (diff > getConnectionTimeout()) {
                        try {
                            connection.kill();
                        } catch (IOException e) {
                            if (log.isDebugEnabled()) {
                                log.debug("Unable to kill connection after timeout.", e);
                            }
                        }
                    }
                }
            } finally {
                Thread.currentThread().setName(oldName);
            }

        }

    }
}
