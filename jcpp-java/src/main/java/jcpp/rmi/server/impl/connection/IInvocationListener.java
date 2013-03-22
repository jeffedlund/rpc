package jcpp.rmi.server.impl.connection;

import java.lang.reflect.Method;

public interface IInvocationListener {
    
    public void invocationSucceeded(Object proxy, Method method, Object[] args);
    
    public void invocationFailed(Object proxy, Method method, Object[] args, Throwable e);

}
