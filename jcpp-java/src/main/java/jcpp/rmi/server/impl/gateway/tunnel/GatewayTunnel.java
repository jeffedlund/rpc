package jcpp.rmi.server.impl.gateway.tunnel;

import java.io.IOException;
import java.io.ObjectOutputStream;
import java.io.OutputStream;

import java.net.Socket;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ExecutorService;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import jcpp.rmi.server.impl.gateway.Address;
import jcpp.rmi.server.impl.gateway.Gateway;
import jcpp.rmi.server.impl.gateway.GatewayConfiguration;
import jcpp.rmi.server.impl.gateway.Route;


public class GatewayTunnel {
    private static Log log = LogFactory.getLog(Gateway.class);

    public static final int BUFFER_SIZE = 21 * 1024;
    public static final byte CREATE = 0x01;
    public static final byte WRITE = 0x02;
    public static final byte CLOSE = 0x04;

    private int nextId;

    private final List<Socket> tunnelSockets;
    private final Gateway gateway;
    private final Address tunnelAddress;
    private final GatewayConfiguration gatewayConfiguration;
    private final ExecutorService executorService;
    private final Map<Integer, VirtualSocket> virtualSockets;


    public GatewayTunnel(Gateway gateway, Address tunnelAddress, GatewayConfiguration gatewayConfiguration, ExecutorService executorService) {
        this.gateway = gateway;
        this.tunnelAddress = tunnelAddress;
        this.gatewayConfiguration = gatewayConfiguration;
        this.executorService = executorService;
        this.virtualSockets = new HashMap<Integer, VirtualSocket>();
        this.tunnelSockets = new ArrayList<Socket>();
    }


    public VirtualSocket getVirtualSocket(int socketId) {
        return virtualSockets.get(socketId);
    }

    public synchronized void addTunnelSocket(final Socket tunnelSocket) {
        tunnelSockets.add(tunnelSocket);
        executorService.submit(new GatewayTunnelReader(this, tunnelSocket));
        if (log.isInfoEnabled()) {
            log.info("Tunnel socket added " + tunnelSocket);
        }
    }

    public synchronized void removeVirtualSocket(int socketId) {
        virtualSockets.remove(socketId);
    }

    public Socket getTunnelSocket() {
        // TODO load balancing between multiple tunnelsockets to enhance performance;
        return tunnelSockets.get(0);
    }

    public Address getTunnelAddress() {
        return tunnelAddress;
    }

    public Gateway getGateway() {
        return gateway;
    }

    public synchronized VirtualSocket create(Route route) throws IOException {
        if (log.isInfoEnabled()) {
            log.info("Creating new virtual socket on tunnel " + getTunnelSocket());
        }
        VirtualSocket virtualSocket = new VirtualSocket(nextId, this);
        virtualSockets.put(nextId, virtualSocket);
        OutputStream out = getTunnelSocket().getOutputStream();
        writeIntToStream(out, virtualSocket.getId());
        out.write(CREATE);
        route.popAddress(); // remove address of current gateway which would have otherwise been remove in GatewaySocket constructor
        new ObjectOutputStream(out).writeObject(route);
        out.flush();
        nextId++;
        return virtualSocket;
    }

    public VirtualSocket accept(int socketId, Route route) throws IOException {
        VirtualSocket virtualSocket = null;
        synchronized (this) {
            if (log.isInfoEnabled()) {
                log.info("Accepting new virtual socket on tunnel " + getTunnelSocket());
            }
            virtualSocket = new VirtualSocket(socketId, this);
            virtualSocket.setRoute(route);
            virtualSockets.put(socketId, virtualSocket);
        }
        try {
            gateway.handleAcceptedSocket(virtualSocket);
        } catch (ClassNotFoundException e) {
            throw new IOException(e);
        }
        return virtualSocket;
    }

    public synchronized void write(byte[] data, int length, int socketId) throws IOException {
        OutputStream out = getTunnelSocket().getOutputStream();
        writeIntToStream(out, socketId);
        out.write(WRITE);
        writeIntToStream(out, length);
        out.write(data, 0, length);
        out.flush();
    }

    public synchronized void flush(int socketId) throws IOException {
        if (virtualSockets.containsKey(socketId)) {
            OutputStream out = getTunnelSocket().getOutputStream();
            out.flush();
        }
    }

    public synchronized void close(int socketId) throws IOException {
        if (log.isInfoEnabled()) {
            log.info("Closing to tunnel (socketId==" + socketId + ") " + getTunnelSocket());
        }
        if (virtualSockets.containsKey(socketId)) {
            OutputStream out = getTunnelSocket().getOutputStream();
            writeIntToStream(out, socketId);
            out.write(CLOSE);
            out.flush();
            virtualSockets.remove(socketId);
        }
    }

    public GatewayConfiguration getGatewayConfiguration() {
        return gatewayConfiguration;
    }

    private void writeIntToStream(OutputStream out, int value) throws IOException {
        out.write(value >> 24);
        out.write(value >> 16);
        out.write(value >> 8);
        out.write(value);
    }

}
