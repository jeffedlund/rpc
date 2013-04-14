package jcpp.lang.model;

import javax.xml.bind.annotation.*;
import java.util.*;

public class JCPPClassBuilder extends JCPPBuilder{

	protected JCPPClassBuilder(){
	}

    public static JCPPClassBuilder create(){
        return new JCPPClassBuilder();
    }

    public JCPPClassBuilder setJavaClass(JavaClass javaClass){
        super.setJavaClass(javaClass);
        return this;
    }

    public JCPPClass build(){
        JCPPClass jcppClass=new JCPPClass();
        CPPClass cppClass=jcppClass.getClazz();

		Set<String> includes=new HashSet<String>();
		Set<String> namespaces=new HashSet<String>();

        fillCPPClass(cppClass,includes,namespaces);

    	cppClass.getIncludes().addAll(includes);
    	cppClass.getNamespaces().addAll(namespaces);

        return jcppClass;
	}
}