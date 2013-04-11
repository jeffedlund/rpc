package jcpp.lang.model;

import javax.xml.bind.annotation.*;
import java.util.*;

public class DefaultJCPPTransformer implements JCPPTransformer{

	public DefaultJCPPTransformer(){
	}

	public void tranform(JavaInterface ji, CPPInterface ci){
		Set<String> includes=new HashSet<String>();
		Set<String> namespaces=new HashSet<String>();

		HCPPInterface hInterface=ci.getHInterface();

    	int i=ji.getName().lastIndexOf(".");
    	if (i>0){
    		hInterface.setNamespace(ji.getName().substring(0,i));
    	}else{
    		hInterface.setNamespace("");
    	}

    	hInterface.setCanonicalName(ji.getCanonicalName());
    	hInterface.setSimpleName(ji.getSimpleName());
    	hInterface.setClassName("J"+ji.getSimpleName());
    	hInterface.setIfndef(hInterface.getClassName().toUpperCase()+"_H");
    	hInterface.setName(ji.getName());
    	hInterface.setParent(parseClassName(includes,namespaces, ji.getParent()));

		for (String im : ji.getImports()){
    		parseClassName(includes,namespaces,im);
    	}

    	for (String interf : ji.getInterfaces()){
    		interf=parseClassName(includes,namespaces,interf);
    		hInterface.getInterfaces().add(interf);
    	}

    	for (JavaMethod jm : ji.getMethods()){
    		CPPMethod method=new CPPMethod();
    		method.setName(jm.getName());
    		method.setReturnType(parseClassName(includes,namespaces,jm.getReturnType()));
    		for (String param : jm.getParameterType()){
    			method.getParameterType().add(parseClassName(includes, namespaces, param));
    		}
    		hInterface.getMethods().add(method);
    	}

    	hInterface.getIncludes().addAll(includes);
    	hInterface.getNamespaces().addAll(namespaces);

    	HCPPInterface proxyInterface=ci.getProxyInterface();
    	//TODO proxyInterface.getIncludes().add();
		//TODO namespaces;
		proxyInterface.setIfndef(hInterface.getClassName().toUpperCase()+"PROXY_H");
		proxyInterface.setNamespace(hInterface.getNamespace());
		proxyInterface.setCanonicalName(hInterface.getCanonicalName()+"Proxy");
		proxyInterface.setSimpleName(hInterface.getSimpleName()+"Proxy");
		proxyInterface.setClassName(hInterface.getClassName()+"Proxy");
		proxyInterface.setName(hInterface.getName()+"Proxy");
		proxyInterface.setParent("JProxy");
		proxyInterface.getInterfaces().add(hInterface.getClassName());
		proxyInterface.getMethods().addAll(hInterface.getMethods());
	}

	private String parseClassName(Set<String> includes,Set<String> namespaces,String s){
		int i=s.lastIndexOf(".");
		if (i>0){
			String tmp1=s.substring(0,i);
			String tmp2="J"+s.substring(i+1,s.length());
			namespaces.add(tmp1.replaceAll("\\.","::"));
			includes.add("\""+tmp2+".h\"");
			return tmp2;
		}
		return s;
	}
}