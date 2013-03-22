package jcpp.rmi.server.impl.connection;

import jcpp.rmi.server.impl.transport.EndPoint;


public interface IServer {

    <T> T lookup(EndPoint endPoint, Class<T> clazz) throws Exception;

    IRegistry getRegistry() throws Exception;

    IGC getGC() throws Exception;

    IGCClient getGCClient() throws Exception;

}
