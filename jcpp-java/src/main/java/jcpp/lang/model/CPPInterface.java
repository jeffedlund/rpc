package jcpp.lang.model;

import javax.xml.bind.annotation.*;
import java.util.*;

@XmlRootElement
public class CPPInterface{
    @XmlElement
    private HCPPInterface hInterface;
    @XmlElement
    private HCPPInterface proxyInterface;

    public CPPInterface(){
        hInterface=new HCPPInterface();
        proxyInterface=new HCPPInterface();
    }

    public HCPPInterface getHInterface(){
        return hInterface;
    }

    public void setHInterface(HCPPInterface i){
        this.hInterface=i;
    }

    public HCPPInterface getProxyInterface(){
        return proxyInterface;
    }

    public void setProxyInterface(HCPPInterface i){
        this.proxyInterface=i;
    }
}
