package jcpp.parser.model;

import javax.xml.bind.annotation.*;
import java.util.*;

@XmlRootElement
public class EnumInfo{
    @XmlElement
    int ordinal;
    @XmlElement
    String name;

    public EnumInfo(){
    }

    public int getOrdinal(){
        return ordinal;
    }

    public void setOrdinal(int ordinal){
        this.ordinal=ordinal;
    }

    public String getName(){
        return name;
    }

    public void setName(String n){
        this.name=n;
    }
}
