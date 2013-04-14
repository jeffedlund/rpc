package jcpp.lang.model;

import javax.xml.bind.annotation.*;
import javax.xml.bind.*;
import java.util.*;
import java.io.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class JCPPInterface{
    @XmlElement(name="interface")
    private CPPClass inter;
    @XmlElement(name="proxyInterface")
    private CPPClass proxyInterface;

    public JCPPInterface(){
        inter=new CPPClass();
        proxyInterface=new CPPClass();
    }

    public CPPClass getInterface(){
        return inter;
    }

    public void setInterface(CPPClass i){
        this.inter=i;
    }

    public CPPClass getProxyInterface(){
        return proxyInterface;
    }

    public void setProxyInterface(CPPClass i){
        this.proxyInterface=i;
    }

    public void write(OutputStream out) throws Exception{
        JAXBContext jaxbContext=JAXBContext.newInstance(JCPPInterface.class);
        jaxbContext.createMarshaller().marshal(this,out);
    }

    public static JCPPInterface from(InputStream in) throws Exception{
        JAXBContext jaxbContext=JAXBContext.newInstance(JCPPInterface.class);
        JCPPInterface jcppi=(JCPPInterface)jaxbContext.createUnmarshaller().unmarshal(in);
        in.close();
        return jcppi;
    }
}