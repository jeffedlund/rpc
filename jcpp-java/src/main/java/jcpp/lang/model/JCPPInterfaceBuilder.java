package jcpp.lang.model;

import javax.xml.bind.annotation.*;
import java.util.*;

public class JCPPInterfaceBuilder extends JCPPBuilder{

	protected JCPPInterfaceBuilder(){
	}

    public static JCPPInterfaceBuilder create(){
        return new JCPPInterfaceBuilder();
    }

    public JCPPInterfaceBuilder setJavaClass(JavaClass javaClass){
        super.setJavaClass(javaClass);
        return this;
    }

    public JCPPInterface build(){
        JCPPInterface jcppInterface=new JCPPInterface();
        CPPClass cppClass=jcppInterface.getInterface();

		Set<String> includes=new HashSet<String>();
		Set<String> namespaces=new HashSet<String>();

        fillCPPClass(cppClass,includes,namespaces);

    	cppClass.getIncludes().addAll(includes);
    	cppClass.getNamespaces().addAll(namespaces);

    	CPPClass proxyInterface=jcppInterface.getProxyInterface();
    	proxyInterface.getIncludes().add("\"JProxy.h\"");//TODO factoriser
		proxyInterface.getNamespaces().add("jcpp::lang::reflect");//TODO factoriser

		proxyInterface.setIfndef(cppClass.getClassName().toUpperCase()+"PROXY_H");
		proxyInterface.setNamespace(cppClass.getNamespace());
		proxyInterface.setCanonicalName(cppClass.getCanonicalName()+"Proxy");
		proxyInterface.setSimpleName(cppClass.getSimpleName()+"Proxy");
		proxyInterface.setClassName(cppClass.getClassName()+"Proxy");
		proxyInterface.setName(cppClass.getName()+"Proxy");
		proxyInterface.setParent("JProxy");
		proxyInterface.getInterfaces().add(cppClass.getClassName());
		proxyInterface.getMethods().addAll(cppClass.getMethods());

        return jcppInterface;
	}
}