package jcpp.lang.model;

import javax.xml.bind.annotation.*;
import java.util.*;

public abstract class JCPPBuilder{
    protected JavaClass javaClass;

	protected JCPPBuilder(){
	}

    public JCPPBuilder setJavaClass(JavaClass javaClass){
        this.javaClass=javaClass;
        return this;
    }


    protected void fillCPPClass(CPPClass cppClass,Set<String> includes,Set<String> namespaces){
        //TODO introduce INamespaceResovler{string resolve(string)}
    	int i=javaClass.getName().lastIndexOf(".");
    	if (i>0){
    		cppClass.setNamespace(javaClass.getName().substring(0,i));
    	}else{
    		cppClass.setNamespace("");
    	}

    	cppClass.setCanonicalName(javaClass.getCanonicalName());
    	cppClass.setSimpleName(javaClass.getSimpleName());
    	cppClass.setClassName("J"+javaClass.getSimpleName());
    	cppClass.setIfndef(cppClass.getClassName().toUpperCase()+"_H");
    	cppClass.setName(javaClass.getName());
    	cppClass.setParent(parseClassName(includes,namespaces, javaClass.getParent()));

		for (String im : javaClass.getImports()){
    		parseClassName(includes,namespaces,im);
    	}

    	for (String interf : javaClass.getInterfaces()){
    		interf=parseClassName(includes,namespaces,interf);
    		cppClass.getInterfaces().add(interf);
    	}

        for (JavaField jf : javaClass.getFields()){
            CPPField field=new CPPField();
            field.setName(jf.getName());
            field.setType(parseClassName(includes,namespaces,jf.getType()));
            field.setGetter(jf.getGetter());
            field.setSetter(jf.getSetter());
            cppClass.getFields().add(field);
        }

    	for (JavaMethod jm : javaClass.getMethods()){
    		CPPMethod method=new CPPMethod();
    		method.setName(jm.getName());
    		method.setReturnType(parseClassName(includes,namespaces,jm.getReturnType()));
    		for (String param : jm.getParameterType()){
    			method.getParameterType().add(parseClassName(includes, namespaces, param));
    		}
    		cppClass.getMethods().add(method);
    	}
	}

	protected String parseClassName(Set<String> includes,Set<String> namespaces,String s){
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