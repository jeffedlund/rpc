package jcpp.rmi.server.impl.transport;

public interface ITransportDispatcher {

    public void dispatch(EndPoint fromEndPoint, EndPoint toEndPoint, Connection connection) throws Throwable;
    
}
