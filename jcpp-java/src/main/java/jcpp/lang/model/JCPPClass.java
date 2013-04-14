package jcpp.lang.model;

import javax.xml.bind.annotation.*;
import javax.xml.bind.*;
import java.util.*;
import java.io.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class JCPPClass{
    @XmlElement(name="class")
    private CPPClass clazz;

    public JCPPClass(){
        clazz=new CPPClass();
    }

    public CPPClass getClazz(){
        return clazz;
    }

    public void setClazz(CPPClass i){
        this.clazz=i;
    }

    public void write(OutputStream out) throws Exception{
        JAXBContext jaxbContext=JAXBContext.newInstance(JCPPClass.class);
        jaxbContext.createMarshaller().marshal(this,out);
    }

    public static JCPPClass from(InputStream in) throws Exception{
        JAXBContext jaxbContext=JAXBContext.newInstance(JCPPClass.class);
        JCPPClass jcppClass=(JCPPClass)jaxbContext.createUnmarshaller().unmarshal(in);
        in.close();
        return jcppClass;
    }
}