package jcpp.rmi.server.impl.connection;

import jcpp.rmi.server.impl.transport.EndPoint;


public interface IGCClient {

    EndPoint[] getEndPoints() throws Exception;

}
