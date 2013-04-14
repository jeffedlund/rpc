package jcpp.lang.model;

import javax.xml.bind.annotation.*;
import javax.xml.bind.*;
import java.util.*;
import java.io.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class JavaClass{
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
    private List<JavaField> fields;
    @XmlElementWrapper
    @XmlElement
    private List<JavaMethod> methods;
    @XmlElement
    private boolean isInterface;
    @XmlElement
    private long serialVersionUID;

    public JavaClass(){
		imports=new ArrayList<String>();
		interfaces=new ArrayList<String>();
    	fields=new ArrayList<JavaField>();
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

	public List<JavaField> getFields(){
		return fields;
	}

	public void setFields(List<JavaField> f){
		this.fields=f;
	}

	public List<JavaMethod> getMethods(){
		return methods;
	}

	public void setMethods(List<JavaMethod> m){
		this.methods=m;
	}

	public boolean isInterface(){
		return isInterface;
	}

	public void setIsInterface(boolean isInterface){
		this.isInterface=isInterface;
	}

	public long getSerialVersionUID(){
		return serialVersionUID;
	}

	public void setSerialVersionUID(long serialVersionUID){
		this.serialVersionUID=serialVersionUID;
	}

	public void write(OutputStream out) throws Exception{
		JAXBContext jaxbContext=JAXBContext.newInstance(JavaClass.class);
		jaxbContext.createMarshaller().marshal(this,out);
	}

	public static JavaClass from(InputStream in) throws Exception{
		JAXBContext jaxbContext=JAXBContext.newInstance(JavaClass.class);
		JavaClass jc=(JavaClass)jaxbContext.createUnmarshaller().unmarshal(in);
		in.close();
		return jc;
	}
}
