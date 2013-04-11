package jcpp.lang.model;

import javax.xml.bind.annotation.*;
import java.util.*;

@XmlRootElement
public class JavaMethod{
    @XmlElement
    private String name;
    @XmlElement
    private String returnType;
    @XmlElementWrapper
    @XmlElement
    private List<String> parameterType;

    public JavaMethod(){
        parameterType=new ArrayList<String>();
    }

    public String getName(){
        return name;
    }

    public void setName(String n){
        this.name=n;
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