package jcpp.parser.model;

import javax.xml.bind.annotation.*;
import java.util.*;

@XmlRootElement
public class ClassInfo{
	@XmlElement
	private String name;
	@XmlElement
	private String canonicalName;
	@XmlElement
    private String simpleName;
    @XmlElement
    private String componentType;
    @XmlElementWrapper
    @XmlElement
    private List<EnumInfo> enumConstants;
    @XmlElementWrapper
    @XmlElement
    private List<FieldInfo> fields;
    @XmlElementWrapper
    @XmlElement
    private List<FieldInfo> declaredFields;
    @XmlElementWrapper
    @XmlElement
    private List<MethodInfo> methods;
    @XmlElementWrapper
    @XmlElement
    private List<MethodInfo> declaredMethods;
    @XmlElementWrapper
    @XmlElement
    private List<String> interfaces;
    @XmlElement
    private boolean bIsArray;
    @XmlElement
    private boolean bIsProxy;
    @XmlElement
    private boolean bIsEnum;
    @XmlElement
    private boolean bIsInterface;
    @XmlElement
    private boolean bIsPrimitive;
    @XmlElement
    private boolean bIsPackage;
    @XmlElement
    private long serialVersionUID;

    public ClassInfo(){
    	enumConstants=new ArrayList<EnumInfo>();
    	fields=new ArrayList<FieldInfo>();
    	declaredFields=new ArrayList<FieldInfo>();
    	methods=new ArrayList<MethodInfo>();
    	declaredMethods=new ArrayList<MethodInfo>();
    	interfaces=new ArrayList<String>();
    }

	public String getName(){
		return name;
	}

	public void setName(String name){
		this.name=name;
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

	public List<FieldInfo> getFields(){
		return fields;
	}

	public void setFields(List<FieldInfo> f){
		this.fields=f;
	}

	public List<FieldInfo> getDeclaredFields(){
		return declaredFields;
	}

	public void setDeclaredFields(List<FieldInfo> f){
		this.declaredFields=f;
	}

	public List<MethodInfo> getMethods(){
		return methods;
	}

	public void setMethods(List<MethodInfo> m){
		this.methods=m;
	}

	public List<MethodInfo> getDeclaredMethods(){
		return declaredMethods;
	}

	public void setDeclaredMethods(List<MethodInfo> m){
		this.declaredMethods=m;
	}

    public List<String> getInterfaces(){
    	return interfaces;
    }

    public void setInterfaces(List<String> i){
    	this.interfaces=i;
    }

	public boolean isArray(){
		return bIsArray;
	}

	public void setIsArray(boolean b){
		this.bIsArray=b;
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

	public boolean isPrimitive(){
		return bIsPrimitive;
	}

	public void setIsPrimitive(boolean b){
		this.bIsPrimitive=b;
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
