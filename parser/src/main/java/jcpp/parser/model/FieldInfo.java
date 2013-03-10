package jcpp.parser.model;

import javax.xml.bind.annotation.*;
import java.util.*;

@XmlRootElement
public class FieldInfo{
    @XmlElement
    String name;
    @XmlElement
    String getter;
    @XmlElement
    String setter;
    @XmlElement
    String type;

    public FieldInfo(){
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

    public void setType(String t){
        this.type=t;
    }

    public String getGetter(){
        return getter;
    }

    public void setGetter(String t){
        this.getter=t;
    }

    public String getSetter(){
        return setter;
    }

    public void setSetter(String t){
        this.setter=t;
    }
}
