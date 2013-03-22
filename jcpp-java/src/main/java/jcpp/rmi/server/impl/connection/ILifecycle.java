package jcpp.rmi.server.impl.connection;

import jcpp.rmi.server.impl.transport.EndPoint;

public interface ILifecycle {

    public void export(ObjectInformation objectInformation);
    
    public void export(ObjectInformation objectInformation, EndPoint endPoint);

    public void unexport(ObjectInformation objectInformation,EndPoint endPoint);

    public void unexport(ObjectInformation objectInformation);

}
