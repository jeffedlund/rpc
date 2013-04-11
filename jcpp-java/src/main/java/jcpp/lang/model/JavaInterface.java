package jcpp.lang.model;

import javax.xml.bind.annotation.*;
import java.util.*;

@XmlRootElement
public class JavaInterface{
	@XmlElement
	private String canonicalName;
	@XmlElement
    private String simpleName;
	@XmlElement
    private String name;
    @XmlElementWrapper
    @XmlElement
    private List<String> imports;
    @XmlElement
    private String parent;
    @XmlElementWrapper
    @XmlElement
    private List<String> interfaces;
    @XmlElementWrapper
    @XmlElement
    private List<JavaMethod> methods;

    public JavaInterface(){
		imports=new ArrayList<String>();
		interfaces=new ArrayList<String>();
    	methods=new ArrayList<JavaMethod>();
    }

	public String getCanonicalName(){
		return canonicalName;
	}

	public void setCanonicalName(String canonicalName){
		this.canonicalName=canonicalName;
	}

	public String getSimpleName(){
		return simpleName;
	}

	public void setSimpleName(String simpleName){
		this.simpleName=simpleName;
	}

	public String getName(){
		return name;
	}

	public void setName(String n){
		this.name=n;
	}

    public List<String> getImports(){
    	return imports;
    }

    public void setImports(List<String> i){
    	this.imports=i;
    }

	public String getParent(){
		return parent;
	}

	public void setParent(String n){
		this.parent=n;
	}

    public List<String> getInterfaces(){
    	return interfaces;
    }

    public void setInterfaces(List<String> i){
    	this.interfaces=i;
    }

	public List<JavaMethod> getMethods(){
		return methods;
	}

	public void setMethods(List<JavaMethod> m){
		this.methods=m;
	}
}
