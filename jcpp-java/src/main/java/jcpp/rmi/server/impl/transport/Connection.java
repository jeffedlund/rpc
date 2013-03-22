package jcpp.rmi.server.impl.transport;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import java.net.Socket;
import java.net.UnknownHostException;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import jcpp.rmi.server.impl.gateway.GatewayConfiguration;
import jcpp.rmi.server.impl.gateway.GatewaySocketFactory;
import jcpp.rmi.server.impl.gateway.IGatewaySocket;
import jcpp.rmi.server.impl.gateway.Route;


public class Connection {
    private static Log log = LogFactory.getLog(Connection.class);
    private static int globalId;

    private int id;
    private Socket socket;
    private long lastUsed;
    private Connections connections;
    private DataOutputStream out;
    private DataInputStream in;
    private boolean opened;
    private Transport transport;
    private GatewayConfiguration gatewayConfiguration;


    public Connection(Route route, Connections connections, GatewayConfiguration gatewayConfiguration) throws UnknownHostException, IOException, ClassNotFoundException {
        this.socket = GatewaySocketFactory.createSocket(route, connections.getTransport().getTransportConfiguration().getGatewayConfiguration());
        this.socket.setSoTimeout(connections.getTransport().getTransportConfiguration().getSocketTimeout());
        this.socket.setTcpNoDelay(true);
        this.socket.setKeepAlive(true);
        this.connections = connections;
        synchronized (Connection.class) {
            this.id = globalId++;
        }
        this.gatewayConfiguration = gatewayConfiguration;
    }

    public Connection(Socket socket, Transport transport,  GatewayConfiguration gatewayConfiguration) {
        this.socket = socket;
        this.transport = transport;
        this.gatewayConfiguration = gatewayConfiguration;
        synchronized (Connection.class) {
            this.id = globalId++;
        }
    }


    public void free() {
        if (connections != null) {
            if (isReusable()) {
                connections.free(this);
            } else {
                try {
                    kill();
                } catch (IOException e) {
                    if (log.isDebugEnabled()) {
                        log.debug("Error killing the non-reusable connection: " + this, e);
                    }
                }
            }
        }
    }

    public void kill() throws IOException {
        if (connections != null) {
            connections.kill(this);
        }
        socket.close();
    }

    public boolean openConnection() throws IOException {
        if (!opened) {
            opened = true;
            getOutputStream();
            out.writeInt(TransportConfiguration.getMagicNumber());
            connections.getTransport().getLocalEndPoint().write(out);
            out.flush();

            if (isReusable()) {
                int oldTimeout = 0;
                try {
                    oldTimeout = socket.getSoTimeout();
                } catch (IOException e) {
                    if (log.isDebugEnabled()) {
                        log.debug("Error getting socket timeout during openConnection(). Socket - " + socket, e);
                    }
                    return false;
                }

                try {
                    if (connections == null) {
                        socket.setSoTimeout(transport.getTransportConfiguration().getPingTimeout());
                    } else {
                        socket.setSoTimeout(connections.getTransport().getTransportConfiguration().getPingTimeout());
                    }
                    return readOk();
                } catch (IOException e) {
                    if (log.isDebugEnabled()) {
                        log.debug("Error setting socket timeout and reading OK during openConnection(). Socket - " + socket, e);
                    }
                    return false;
                } finally {
                    try {
                        socket.setSoTimeout(oldTimeout);
                    } catch (IOException e) {
                        if (log.isDebugEnabled()) {
                            log.debug("Error setting socket timeout during openConnection(). Socket - " + socket, e);
                        }
                        return false;
                    }
                }
            } else {
                return true;
            }
        }
        return true;
    }

    public void startCall() throws IOException {
        getOutputStream();
        out.writeByte((int) TransportConfiguration.MSG_TYPE_CALL);
    }

    public void finishCall() throws IOException {
        getOutputStream();
        out.flush();
    }

    public void sendOk() throws IOException {
        getOutputStream();
        out.writeByte((int) TransportConfiguration.MSG_TYPE_OK);
        if (isReusable()) {
            out.flush();
        }
    }

    public boolean readOk() throws IOException {
        getInputStream();
        byte okByte = in.readByte();
        if (okByte != TransportConfiguration.MSG_TYPE_OK) {
            if (log.isDebugEnabled()) {
                log.debug("Reading: MSG_TYPE_OK expected, received: " + okByte + ". Socket - " + socket);
            }
            return false;
        }
        return true;
    }

    public boolean isDead() {
        boolean isDead = false;
        int oldTimeout = 0;
        try {
            oldTimeout = socket.getSoTimeout();
        } catch (IOException e) {
            if (log.isDebugEnabled()) {
                log.debug("Error getting socket timeout during isDead(). Considering socket as dead. Socket - " + socket, e);
            }
            return true;
        }
        try {
            sendPing();
            if (connections == null) {
                socket.setSoTimeout(transport.getTransportConfiguration().getPingTimeout());
            } else {
                socket.setSoTimeout(connections.getTransport().getTransportConfiguration().getPingTimeout());
            }
            if (!readOk()) {
                isDead = true;
            }
        } catch (IOException e) {
            if (log.isDebugEnabled()) {
                log.debug("Error while ping during isDead(). Considering socket as dead. Socket - " + socket, e);
            }
            isDead = true;
        } finally {
            if (isDead && !socket.isClosed()) {
                try {
                    socket.close();
                } catch (IOException e) {
                    if (log.isDebugEnabled()) {
                        log.debug("Error closing socket of dead connection. Socket - " + socket, e);
                    }
                }
            }
            try {
                socket.setSoTimeout(oldTimeout);
            } catch (IOException e) {
                if (log.isDebugEnabled()) {
                    log.debug("Error setting socket timeout during isDead(). Socket - " + socket, e);
                }
                return true;
            }
        }
        return isDead;
    }

    public DataOutputStream getOutputStream() throws IOException {
        if (out == null) {
            OutputStream outputStream = socket.getOutputStream();
            out = new DataOutputStream(new BufferedOutputStream(outputStream, gatewayConfiguration.getSendBufferSize()));
        }
        return out;
    }

    public DataInputStream getInputStream() throws IOException {
        if (in == null) {
            InputStream inputStream = socket.getInputStream();
            in = new DataInputStream(new BufferedInputStream(inputStream, gatewayConfiguration.getReceiveBufferSize()));
        }
        return in;
    }

    public void setLastUsed() {
        this.lastUsed = System.currentTimeMillis();
    }

    public boolean isReusable() {
        return ((IGatewaySocket) socket).isReausable();
    }

    public Socket getSocket() {
        return socket;
    }

    public long getLastUsed() {
        return lastUsed;
    }

    public Connections getConnections() {
        return connections;
    }

    @Override
    public String toString() {
        return "Connection[" + connections + ", " + socket + "]";
    }

    private void sendPing() throws IOException {
        out.writeByte((int) TransportConfiguration.MSG_TYPE_PING);
        out.flush();
    }
}
