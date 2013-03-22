package jcpp.rmi.server.impl.connection;

import jcpp.rmi.server.impl.transport.EndPoint;

public interface IGC {

    public boolean[] ping(EndPoint endPoint, String[] id) throws Throwable;

    public void endPointDead(EndPoint endPoint) throws Throwable;

    public EndPoint[] getExportedEndPoints() throws Throwable;
}
