package jcpp.rmi.server.impl.connection;

import java.io.IOException;
import java.io.InputStream;
import java.io.ObjectInputStream;
import java.io.ObjectStreamClass;

import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Modifier;
import java.lang.reflect.Proxy;

import java.util.HashMap;
import java.util.Map;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import jcpp.rmi.server.impl.connection.serialization.NotSerializableException;
import jcpp.rmi.server.impl.transport.EndPoint;


public class ConnectionInputStream extends ObjectInputStream {
    private static Log log = LogFactory.getLog(ConnectionInputStream.class);
    private ObjectInformations objectInformations;
    private Map<ObjectPointer, Object> gcObjectPointers;
    private EndPoint remoteEndPoint;


    public ConnectionInputStream(InputStream in, ObjectInformations objectInformations, EndPoint remoteEndPoint) throws IOException {
        super(in);
        enableResolveObject(true);
        this.objectInformations = objectInformations;
        this.gcObjectPointers = new HashMap<ObjectPointer, Object>();
        this.remoteEndPoint = remoteEndPoint;
    }


    public void done() throws Exception {
        objectInformations.getGCClient().add(gcObjectPointers);
        gcObjectPointers.clear();
    }

    @Override
    protected Object resolveObject(Object obj) throws IOException {
        if (Proxy.isProxyClass(obj.getClass())) {
            InvocationHandler invocationHandler = Proxy.getInvocationHandler(obj);
            if (invocationHandler instanceof ObjectHandler) {
                ObjectHandler objectHandler = (ObjectHandler) invocationHandler;
                objectHandler.setObjectInformations(objectInformations);
                ObjectPointer objectPointer = objectHandler.getInvoker().getObjectPointer();
                if (objectPointer.getEndPoint().equals(objectInformations.getTransport().getLocalEndPoint())) {
                    return objectInformations.getObjectInformation(objectPointer.getId()).getObject();
                }
                gcObjectPointers.put(objectPointer, obj);
                return obj;
            }
        } else if (obj instanceof NotSerializableException) {
            throw (NotSerializableException) obj;
        }
        return obj;
    }

    @Override
    protected ObjectStreamClass readClassDescriptor() throws IOException, ClassNotFoundException {
        // This method has been overriden to ignore SerialVersionUIDs when they do not match.
        // This is especially helpful when interacting with the C++
        //
        ObjectStreamClass resultClassDescriptor = super.readClassDescriptor(); // initially streams descriptor
        Class<?> localClass; // the class in the local JVM that this descriptor represents.
        try {
            localClass = Class.forName(resultClassDescriptor.getName());
        } catch (ClassNotFoundException e) {
            log.debug("No local class for " + resultClassDescriptor.getName(), e);
            return resultClassDescriptor;
        }
        ObjectStreamClass localClassDescriptor = ObjectStreamClass.lookup(localClass);
        if (localClassDescriptor != null) { // only if class implements serializable
            final long localSUID = localClassDescriptor.getSerialVersionUID();
            final long streamSUID = resultClassDescriptor.getSerialVersionUID();
            if (streamSUID != localSUID) { // check for serialVersionUID mismatch.
                resultClassDescriptor = localClassDescriptor; // Use local class descriptor for deserialization
            }
        }
        return resultClassDescriptor;
    }
}
