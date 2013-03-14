package jcpp.parser.model;

import javax.xml.bind.annotation.*;
import java.util.*;

@XmlRootElement
public class MethodInfo{
    @XmlElement
    String name;
    @XmlElement
    ClassKeyInfo returnType;
    @XmlElementWrapper
    @XmlElement
    List<ClassKeyInfo> parameterType;

    public MethodInfo(){
        parameterType=new ArrayList<String>();
    }

    public String getName(){
        return name;
    }

    public void setName(String n){
        this.name=n;
    }

    public ClassKeyInfo getReturnType(){
        return returnType;
    }

    public void setReturnType(ClassKeyInfo n){
        this.returnType=n;
    }

    public List<ClassKeyInfo> getParameterType(){
        return parameterType;
    }

    public void setParameterType(List<ClassKeyInfo> p){
        this.parameterType=p;
    }
}
