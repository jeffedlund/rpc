package jcpp.rmi.server.impl.transport;

import jcpp.rmi.server.impl.gateway.Route;

public interface ITransportRouter {

    public Route findRoute(String localSite, EndPoint remoteEndPoint);
    
}
