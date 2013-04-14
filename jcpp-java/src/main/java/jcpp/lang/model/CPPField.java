package jcpp.lang.model;

import javax.xml.bind.annotation.*;
import java.util.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class CPPField{
    @XmlElement
    private String name;
    @XmlElement
    private String type;
    @XmlElement
    private String getter;
    @XmlElement
    private String setter;

    public CPPField(){
    }

    public String getName(){
        return name;
    }

    public void setName(String n){
        this.name=n;
    }

    public String getType(){
        return type;
    }

    public void setType(String n){
        this.type=n;
    }

    public String getGetter(){
        return getter;
    }

    public void setGetter(String n){
        this.getter=n;
    }

    public String getSetter(){
        return setter;
    }

    public void setSetter(String n){
        this.setter=n;
    }
}