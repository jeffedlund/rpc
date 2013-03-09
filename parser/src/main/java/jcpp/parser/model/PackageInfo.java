package jcpp.parser.model;

import javax.xml.bind.annotation.*;
import java.util.*;

@XmlRootElement
public class PackageInfo{
	@XmlElement
	private String name;
	@XmlElementWrapper
	@XmlElement
	private List<String> classes;
	@XmlElementWrapper
	@XmlElement
	private List<String> packages;

    public PackageInfo(){
    	classes=new ArrayList<String>();
    	packages=new ArrayList<String>();
    }

	public String getName(){
		return name;
	}

	public void setName(String name){
		this.name=name;
	}

    public List<String> getClasses(){
    	return classes;
    }

    public void setClasses(List<String> c){
    	this.classes=c;
    }

	public List<String> getPackages(){
		return packages;
	}

	public void setPackages(List<String> f){
		this.packages=f;
	}
}
