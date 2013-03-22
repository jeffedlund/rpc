package jcpp.rmi.server.impl.connection;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import jcpp.rmi.server.impl.transport.Connection;
import jcpp.rmi.server.impl.transport.EndPoint;
import jcpp.rmi.server.impl.transport.ITransportDispatcher;
import jcpp.rmi.server.impl.transport.TransportConfiguration;


public class ConnectionTransportDispatcher implements ITransportDispatcher {
    private static Log log = LogFactory.getLog(ConnectionTransportDispatcher.class);
    private ObjectInformations objectInformations;


    public ConnectionTransportDispatcher(ObjectInformations objectInformations) {
        this.objectInformations = objectInformations;
    }


    @Override
    public void dispatch(EndPoint fromEndPoint, EndPoint toEndPoint, Connection connection) throws Throwable {
        ConnectionInputStream ois = new ConnectionInputStream(connection.getInputStream(), objectInformations, fromEndPoint);
        String objectId = null;
        long digest = 0;
        Object[] args = null;
        Exception readException = null;
        try {
            objectId = ois.readUTF();
            digest = ois.readLong();
            args = (Object[]) ois.readObject();
        } catch (Exception e) {
            readException = e;
        } finally {
            ois.done();
        }

        ConnectionOutputStream oos = new ConnectionOutputStream(connection.getOutputStream(), objectInformations, fromEndPoint);
        try {
            if (readException != null) {
                throw readException;
            }
            InvocationResult invocationResult = invokeMethod(objectId, digest, args, fromEndPoint);
            Object result = invocationResult.getResult();
            if (invocationResult.isExceptionThrown()) {
                throw (Throwable) result;
            }
            oos.writeByte((int) TransportConfiguration.MSG_TYPE_OK);
            oos.writeObject(result);
            connection.sendOk(); // for the Call
        } catch (Throwable throwable) {
            if (log.isDebugEnabled()) {
                log.debug("Exception occured while invoking method on object of ID: " + objectId + " on connection: " + connection, throwable);
            }
            oos.writeByte((int) TransportConfiguration.MSG_TYPE_EXCEPTION);
            oos.writeObject(throwable);
            oos.flush();
            connection.sendOk(); // for the Call
        } finally {
            try {
                oos.done();
            } catch (Throwable throwable) {
                if (log.isDebugEnabled()) {
                    log.debug("Error while calling ConnectionOutputStream.done() after invoking method of digest:" + digest + " on object of ID: " + objectId, throwable);
                }
            }
        }
    }

    public InvocationResult invokeMethod(String id, long digest, Object[] args, EndPoint endPoint) {
        Object object = null;
        Method method = null;
        Object result = null;
        boolean exceptionThrown = false;

        ObjectInformation objectInformation = objectInformations.getObjectInformation(id);
        if (objectInformation == null) {
            exceptionThrown = true;
            result = new ConnectionException("Object of ID: " + id + " has not been exported in " + objectInformations.getTransport().getLocalEndPoint());
        } else {
            object = objectInformation.getObject();
            method = objectInformations.getMethodDigester().getMethodFromDigest(object, digest);
            if (method == null) {
                exceptionThrown = true;
                Method[] methods = objectInformations.getMethodDigester().getMethods(object);
                String classDescription = "Methods available for type " + object.getClass() + ":\n";
                for (Method classMethod : methods) {
                    classDescription += "\t" + classMethod.toString() + ";\n";
                }
                result = new ConnectionException("No method found for digest: " + digest + " on object: " + object + "\n" + classDescription);
            } else {
                try {
                    result = method.invoke(object, args);
                } catch (Throwable e) {
                    exceptionThrown = true;
                    IInvocationExceptionHandler handler = objectInformations.getServer().getInvocationExceptionHandler();
                    if (handler != null) {
                        result = handler.handleException(object, method, args, e);
                    } else {
                        if (e instanceof InvocationTargetException) {
                            result = e.getCause();
                        } else {
                            result = e;
                        }
                    }
                }
            }
        }
        return new InvocationResult(object, method, result, exceptionThrown);
    }


    public static class InvocationResult {
        private Object object;
        private Method method;
        private Object result;
        private boolean exceptionThrown;


        public InvocationResult(Object object, Method method, Object result, boolean exceptionThrown) {
            this.object = object;
            this.method = method;
            this.result = result;
            this.exceptionThrown = exceptionThrown;
        }


        public Object getObject() {
            return object;
        }

        public Method getMethod() {
            return method;
        }

        public Object getResult() {
            return result;
        }

        public boolean isExceptionThrown() {
            return exceptionThrown;
        }

    }
}
