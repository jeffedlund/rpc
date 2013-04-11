package jcpp.lang.model;

import javax.xml.bind.annotation.*;
import java.util.*;

@XmlRootElement
public class CPPMethod{
    @XmlElement
    private String name;
    @XmlElement
    private String returnType;
    @XmlElementWrapper
    @XmlElement
    private List<String> parameterType;
    @XmlElement
    private boolean isReturnTypeVoid;

    public CPPMethod(){
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
        this.isReturnTypeVoid=n.equals("void");
    }

    public List<String> getParameterType(){
        return parameterType;
    }

    public void setParameterType(List<String> p){
        this.parameterType=p;
    }

    public boolean getIsReturnTypeVoid(){
        return this.isReturnTypeVoid;
    }

    public void setIsReturnTypeVoid(boolean isReturnTypeVoid){
        this.isReturnTypeVoid=isReturnTypeVoid;
    }
}