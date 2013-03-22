package jcpp.rmi.server.impl.gateway;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;

import jcpp.rmi.server.impl.gateway.http.HttpRequestGatewaySocket;

public class GatewaySocketFactory {

    public static Socket createSocket(Route route, GatewayConfiguration gatewayConfiguration) throws UnknownHostException, IOException, ClassNotFoundException {
        if(route != null && route.isHttp()) {
            return new HttpRequestGatewaySocket(route, false, gatewayConfiguration);
        }
        return new GatewaySocket(route, false, gatewayConfiguration);
    }

    public static ServerSocket createServerSocket(int port, GatewayConfiguration gatewayConfiguration) throws IOException {
        return new GatewayServerSocket(port, false, gatewayConfiguration);
    }
}
