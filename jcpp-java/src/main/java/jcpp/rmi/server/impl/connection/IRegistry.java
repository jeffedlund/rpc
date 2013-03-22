package jcpp.rmi.server.impl.connection;

public interface IRegistry {

    public void bind(String id, Object object, Class<?>[] interfaces) throws Exception;

    public String[] list() throws Exception;

    public Object lookup(String id) throws Exception;

    public void rebind(String id, Object object, Class<?>[] interfaces) throws Exception;

    public void unbind(String id) throws Exception;

}
