package jcpp.rmi.server.impl.connection;

import jcpp.rmi.server.impl.transport.EndPoint;

public interface IGCClientListener {
    
    public void objectAlive(EndPoint endPoint, Object[] objects);
    
    public void objectMaybeDead(EndPoint endPoint, Object[] objects, Throwable throwable);
    
    public void objectDead(EndPoint endPoint, Object[] objects,  Throwable throwable);

    public void objectDead(EndPoint endPoint, Object[] objects);

}
