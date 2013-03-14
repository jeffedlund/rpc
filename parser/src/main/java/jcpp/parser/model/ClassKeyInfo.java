package jcpp.parser.model;

import javax.xml.bind.annotation.*;
import java.util.*;

@XmlRootElement
public class ClassKeyInfo{
    @XmlElementWrapper
    @XmlElement
    private List<String> packageName;
	@XmlElement
	private String className;

    public ClassKeyInfo(){
		packageName=new ArrayList<String>();
    }

    public List<String> getPackageName(){
    	return packageName;
    }

    public void setPackageName(List<String> p){
    	this.packageName=p;
    }

    public String getDirectory(){
    	String str="";
    	for (String s : packageName){
    		str+=s+"/";
    	}
    	return str;
    }

	public String getClassName(){
		return className;
	}

	public void setClassName(String name){
		this.className=name;
	}
}
