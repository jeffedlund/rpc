package jcpp.rmi.server.impl.connection;

import jcpp.rmi.server.impl.transport.*;
import jcpp.rmi.server.impl.gateway.*;
import jcpp.*;
import java.io.*;

public class TestServer{


 	public static void main(String[] argv) throws Exception{
 		System.setProperty("org.apache.commons.logging.Log", "org.apache.commons.logging.impl.SimpleLog");
		System.setProperty("org.apache.commons.logging.simplelog.showdatetime", "true");
		System.setProperty("org.apache.commons.logging.simplelog.log.jcpp", "debug");
		System.setProperty("org.apache.commons.logging.simplelog.defaultlog", "debug");
 		EndPoint endPoint=new EndPoint("localhost",9876,"site1");
 		Server server=Server.create(endPoint,new TransportRouter(),new ConnectionConfiguration());
 		RemoteSample rs=new RemoteSample();
 		server.getRegistry().bind(IRemoteSample.class.getName(),rs,new Class[]{IRemoteSample.class});
    } 
}