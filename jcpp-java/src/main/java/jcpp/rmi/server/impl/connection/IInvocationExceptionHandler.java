package jcpp.rmi.server.impl.connection;

import java.lang.reflect.Method;


public interface IInvocationExceptionHandler {

    Throwable handleException(Object object, Method method, Object[] args, Throwable exception);

}
