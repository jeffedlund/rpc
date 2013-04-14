package jcpp.lang.model;

import javax.xml.bind.annotation.*;
import java.util.*;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class CPPClass{
    @XmlElement
    private String ifndef;
    @XmlElementWrapper
    @XmlElement
    private List<String> includes;
    @XmlElementWrapper
    @XmlElement
    private List<String> namespaces;
    @XmlElement
    private String namespace;
    @XmlElement
    private String canonicalName;
    @XmlElement
    private String simpleName;
    @XmlElement
    private String className;
    @XmlElement
    private String name;
    @XmlElement
    private String parent;
    @XmlElementWrapper
    @XmlElement
    private List<String> interfaces;
    @XmlElementWrapper
    @XmlElement
    private List<CPPField> fields;
    @XmlElementWrapper
    @XmlElement
    private List<CPPMethod> methods;
    @XmlElement
    private long serialVersionUID;

    public CPPClass(){
        includes=new ArrayList<String>();
        namespaces=new ArrayList<String>();
        interfaces=new ArrayList<String>();
        fields=new ArrayList<CPPField>();
        methods=new ArrayList<CPPMethod>();
    }

    public String getIfndef(){
        return ifndef;
    }

    public void setIfndef(String s){
        this.ifndef=s;
    }

    public List<String> getIncludes(){
        return includes;
    }

    public void setIncludes(List<String> i){
        this.includes=i;
    }

    public List<String> getNamespaces(){
        return namespaces;
    }

    public void setNamespaces(List<String> i){
        this.namespaces=i;
    }

    public String getNamespace(){
        return namespace;
    }

    public void setNamespace(String n){
        this.namespace=n;
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

    public String getClassName(){
        return className;
    }

    public void setClassName(String className){
        this.className=className;
    }

    public String getName(){
        return name;
    }

    public void setName(String n){
        this.name=n;
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

    public List<CPPField> getFields(){
        return fields;
    }

    public void setFields(List<CPPField> f){
        this.fields=f;
    }

    public List<CPPMethod> getMethods(){
        return methods;
    }

    public void setMethods(List<CPPMethod> m){
        this.methods=m;
    }

    public long getSerialVersionUID(){
        return serialVersionUID;
    }

    public void setSerialVersionUID(long serialVersionUID){
        this.serialVersionUID=serialVersionUID;
    }

    public String getHFilePath(){
        return namespace.replace('.','/')+'/'+className+".h";
    }

    public String getCPPFilePath(){
        return namespace.replace('.','/')+'/'+className+".cpp";
    }

    public Map<String,Object> getTemplateInput(){
        HashMap<String,Object> m=new HashMap<String,Object>();
        m.put("ifndef",ifndef);
        m.put("includes",includes);
        m.put("namespaces",namespaces);

        List<String> l=new ArrayList();
        StringTokenizer tks=new StringTokenizer(namespace,".");
        while (tks.hasMoreElements()){
            l.add((String)tks.nextElement());
        }
        m.put("namespace",l);
        m.put("namespacesize",l);
        m.put("canonicalName",canonicalName);
        m.put("simpleName",simpleName);
        m.put("className",className);
        m.put("name",name);
        m.put("parent",parent);
        m.put("interfaces",interfaces);
        m.put("fields",fields);
        m.put("methods",methods);
        m.put("serialVersionUID",serialVersionUID);
        return m;
    }
}
