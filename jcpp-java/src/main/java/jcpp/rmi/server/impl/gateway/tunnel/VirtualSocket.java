package jcpp.rmi.server.impl.gateway.tunnel;

import java.io.IOException;

import java.net.InetAddress;
import java.net.Socket;
import java.net.SocketException;

import jcpp.rmi.server.impl.gateway.IGatewaySocket;
import jcpp.rmi.server.impl.gateway.Route;


public class VirtualSocket extends Socket implements IGatewaySocket {
    private int id;
    private GatewayTunnel tunnel;
    private VirtualOutputStream output;
    private VirtualInputStream input;
    private Route route;


    public VirtualSocket(int id, GatewayTunnel tunnel) {
        this.id = id;
        this.tunnel = tunnel;
        this.output = new VirtualOutputStream(this);
        this.input = new VirtualInputStream();
    }


    public int getId() {
        return id;
    }

    public GatewayTunnel getTunnel() {
        return tunnel;
    }

    public void setRoute(Route route) {
        this.route = route;
    }

    @Override
    public Route getRoute() {
        return route;
    }

    @Override
    public boolean isReausable() {
        return ((IGatewaySocket) tunnel.getTunnelSocket()).isReausable();
    }

    @Override
    public VirtualInputStream getInputStream() throws IOException {
        return input;
    }

    @Override
    public VirtualOutputStream getOutputStream() throws IOException {
        return output;
    }

    @Override
    public void close() throws IOException {
        try {
            tunnel.close(id);
        } catch (IOException e) {
        }
        try {
            output.close();
        } catch (IOException e) {
        }
        try {
            input.close();
        } catch (IOException e) {
        }
        try {
            super.close();
        } catch (IOException e) {
        }
    }

    @Override
    public InetAddress getInetAddress() {
        return tunnel.getTunnelSocket().getInetAddress();
    }

    @Override
    public InetAddress getLocalAddress() {
        return tunnel.getTunnelSocket().getLocalAddress();
    }

    @Override
    public int getPort() {
        return tunnel.getTunnelSocket().getPort();
    }

    @Override
    public int getLocalPort() {
        return tunnel.getTunnelSocket().getLocalPort();
    }

    @Override
    public void setTcpNoDelay(boolean on) throws SocketException {
//        socket.setTcpNoDelay(on);
    }

    @Override
    public boolean getTcpNoDelay() throws SocketException {
        return tunnel.getTunnelSocket().getTcpNoDelay();
    }

    @Override
    public void setSoLinger(boolean on, int val) throws SocketException {
//        socket.setSoLinger(on, val);
    }

    @Override
    public int getSoLinger() throws SocketException {
        return tunnel.getTunnelSocket().getSoLinger();
    }

    @Override
    public void setSoTimeout(int timeout) throws SocketException {
//        socket.setSoTimeout(timeout);
    }

    @Override
    public int getSoTimeout() throws SocketException {
        return tunnel.getTunnelSocket().getSoTimeout();
    }

    @Override
    public String toString() {
        String strSocketType = "Virtual Socket";
        strSocketType += " [Tunnel Socket: " + tunnel.getTunnelSocket() + "]";
        return strSocketType;
    }

}
