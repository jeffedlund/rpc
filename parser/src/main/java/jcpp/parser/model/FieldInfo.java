package jcpp.parser.model;

import javax.xml.bind.annotation.*;
import java.util.*;

@XmlRootElement
public class FieldInfo{
    @XmlElement
    String name;
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
}
