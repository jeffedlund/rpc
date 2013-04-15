package jcpp.lang.model;

import javax.xml.bind.annotation.*;
import java.util.*;

public abstract class JCPPBuilder{
    protected JavaClass javaClass;
    protected NameResolver nameResolver;

	protected JCPPBuilder(){
        this.nameResolver=NameResolver.getDefault();
	}

    public JCPPBuilder setJavaClass(JavaClass javaClass){
        this.javaClass=javaClass;
        return this;
    }

    public JCPPBuilder setNameResolver(NameResolver nameResolver){
        this.nameResolver=nameResolver;
        return this;
    }

    protected void fillCPPClass(CPPClass cppClass,Set<String> includes,Set<String> namespaces){
        //TODO introduce INamespaceResovler{string resolve(string)}
    	int i=javaClass.getName().lastIndexOf(".");
    	if (i>0){
    		cppClass.setNamespace(nameResolver.resolvePackage(javaClass.getName().substring(0,i)));
    	}else{
    		cppClass.setNamespace("");
    	}

    	cppClass.setCanonicalName(javaClass.getCanonicalName());
    	cppClass.setSimpleName(javaClass.getSimpleName());
    	cppClass.setClassName(nameResolver.resolveClassName(javaClass.getSimpleName()));
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
			String tmp1=nameResolver.resolvePackage(s.substring(0,i));
			String tmp2=nameResolver.resolveClassName(s.substring(i+1,s.length()));
			namespaces.add(tmp1);
			includes.add(nameResolver.resolveInclude(tmp2));
			return tmp2;
		}else{
            return nameResolver.resolveClassName(s);
        }
	}
}