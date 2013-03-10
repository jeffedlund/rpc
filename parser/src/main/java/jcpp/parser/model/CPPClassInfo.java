package jcpp.parser.model;

import javax.xml.bind.annotation.*;
import java.util.*;

@XmlRootElement
public class CPPClassInfo{
	@XmlElement
	private String ifndef;
    @XmlElementWrapper
    @XmlElement
    private List<String> includes;
    @XmlElementWrapper
    @XmlElement
    private List<String> useNamespace;
    @XmlElementWrapper
    @XmlElement
    private List<String> namespace;
	@XmlElement
	private String className;
    @XmlElement
    private String parentClass;
	@XmlElement
	private String canonicalName;
	@XmlElement
    private String simpleName;
	@XmlElement
    private String name;
    @XmlElementWrapper
    @XmlElement
    private List<FieldInfo> declaredFields;
    @XmlElementWrapper
    @XmlElement
    private List<String> interfaces;


    @XmlElement
    private String componentType;
    @XmlElementWrapper
    @XmlElement
    private List<EnumInfo> enumConstants;
    @XmlElementWrapper
    @XmlElement
    private List<MethodInfo> declaredMethods;
    @XmlElement
    private boolean bIsProxy;
    @XmlElement
    private boolean bIsEnum;
    @XmlElement
    private boolean bIsInterface;
    @XmlElement
    private boolean bIsPackage;
    @XmlElement
    private long serialVersionUID;

    public CPPClassInfo(){
		includes=new ArrayList<String>();
		useNamespace=new ArrayList<String>();
		namespace=new ArrayList<String>();
		interfaces=new ArrayList<String>();

    	enumConstants=new ArrayList<EnumInfo>();
    	declaredFields=new ArrayList<FieldInfo>();
    	declaredMethods=new ArrayList<MethodInfo>();
    	
    }

	public String getIfndef(){
		return ifndef;
	}

	public void setIfndef(String n){
		this.ifndef=n;
	}

    public List<String> getIncludes(){
    	return includes;
    }

    public void setIncludes(List<String> i){
    	this.includes=i;
    }

    public String getDirectory(){
    	String str="";
    	for (String s : namespace){
    		str+=s+"/";
    	}
    	return str;
    }

    public List<String> getUseNamespace(){
    	return useNamespace;
    }

    public void setUseNamespace(List<String> u){
    	this.useNamespace=u;
    }

    public List<String> getNamespace(){
    	return namespace;
    }

    public void setNamespace(List<String> u){
    	this.namespace=u;
    }

	public String getClassName(){
		return className;
	}

	public void setClassName(String name){
		this.className=name;
	}

	public String getParentClass(){
		return parentClass;
	}

	public void setParentClass(String n){
		this.parentClass=n;
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

	public List<FieldInfo> getDeclaredFields(){
		return declaredFields;
	}

	public void setDeclaredFields(List<FieldInfo> f){
		this.declaredFields=f;
	}

    public List<String> getInterfaces(){
    	return interfaces;
    }

    public void setInterfaces(List<String> i){
    	this.interfaces=i;
    }






    public String getComponentType(){
    	return componentType;
    }

    public void setComponentType(String componentType){
    	this.componentType=componentType;
    }

    public List<EnumInfo> getEnumConstants(){
    	return enumConstants;
    }

    public void setEnumConstants(List<EnumInfo> c){
    	this.enumConstants=c;
    }

	public List<MethodInfo> getDeclaredMethods(){
		return declaredMethods;
	}

	public void setDeclaredMethods(List<MethodInfo> m){
		this.declaredMethods=m;
	}

	public boolean isProxy(){
		return bIsProxy;
	}

	public void setIsProxy(boolean b){
		this.bIsProxy=b;
	}

	public boolean isEnum(){
		return bIsEnum;
	}

	public void setIsEnum(boolean b){
		this.bIsEnum=b;
	}

	public boolean isInterface(){
		return bIsInterface;
	}

	public void setIsInterface(boolean b){
		this.bIsInterface=b;
	}

	public boolean isPackage(){
		return bIsPackage;
	}

	public void setIsPackage(boolean b){
		this.bIsPackage=b;
	}

	public long getSerialVersionUID(){
		return serialVersionUID;
	}
	
	public void setSerialVersionUID(long l){
		this.serialVersionUID=l;
	}
}
