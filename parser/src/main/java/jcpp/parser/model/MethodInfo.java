package jcpp.parser.model;

import javax.xml.bind.annotation.*;
import java.util.*;

@XmlRootElement
public class MethodInfo{
    @XmlElement
    String name;
    @XmlElement
    String declaringClass;
    @XmlElement
    String returnType;
    @XmlElementWrapper
    @XmlElement
    List<String> parameterType;

    public MethodInfo(){
        parameterType=new ArrayList<String>();
    }

    public String getName(){
        return name;
    }

    public void setName(String n){
        this.name=n;
    }

    public String getDeclaringClass(){
        return declaringClass;
    }

    public void setDeclaringClass(String d){
        this.declaringClass=d;
    }

    public String getReturnType(){
        return returnType;
    }

    public void setReturnType(String n){
        this.returnType=n;
    }

    public List<String> getParameterType(){
        return parameterType;
    }

    public void setParameterType(List<String> p){
        this.parameterType=p;
    }
}
