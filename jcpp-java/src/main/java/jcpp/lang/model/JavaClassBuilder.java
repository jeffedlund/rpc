package jcpp.lang.model;

import javax.xml.bind.annotation.*;
import javax.xml.bind.*;
import java.util.*;
import java.io.*;
import java.lang.reflect.*;
import javassist.*;

public class JavaClassBuilder{
	private String className;

	protected JavaClassBuilder(){
	}

	public static JavaClassBuilder create(){
		return new JavaClassBuilder();
	}

	public JavaClassBuilder setClassName(String className){
		this.className=className;
		return this;
	}

	public JavaClass build() throws Exception{
		ClassPool classPool=new ClassPool(true);
		CtClass ctClass=classPool.getCtClass(className);
		Class clazz=Class.forName(className);

		JavaClass javaClass=new JavaClass();
		javaClass.setCanonicalName(clazz.getCanonicalName());
		javaClass.setSimpleName(clazz.getSimpleName());
		javaClass.setName(clazz.getName());
		if (clazz.getSuperclass()!=null){
			javaClass.setParent(clazz.getSuperclass().getName());
		}else if (clazz.isInterface()){
			javaClass.setParent("java.lang.Interface");//TODO dans constant
		}
		javaClass.setIsInterface(clazz.isInterface());

		long uid=0;
		try{
			Field f=clazz.getDeclaredField("serialVersionUID");
			f.setAccessible(true);
			uid=f.getLong(null);
		}catch(Exception e){
			e.printStackTrace();
		}
		javaClass.setSerialVersionUID(uid);

		for (Class ci : clazz.getInterfaces()){
			javaClass.getInterfaces().add(ci.getName());
		}

		for (Method m : clazz.getMethods()){
			if (m.getDeclaringClass().equals(clazz)){
				JavaMethod jm=new JavaMethod();
				jm.setName(m.getName());
				jm.setReturnType(m.getReturnType().getName());
				for (Class pc : m.getParameterTypes()){
					jm.getParameterType().add(pc.getName());
				}
				javaClass.getMethods().add(jm);
			}
		}

		/*
    private List<String> imports;
    private List<JavaField> fields;
		*/

		return javaClass;
	}

	public static void main(String[] argv) throws Exception{
		JavaClassBuilder javaClassBuilder=JavaClassBuilder.create().setClassName(argv[0]);
		JavaClass jc=javaClassBuilder.build();
		JCPPClass jcppi=JCPPClassBuilder.create().setJavaClass(jc).build();
  		JCPPClassExporter.create().setOutput(new File(argv[1])).setJCPPClass(jcppi).export();
  		jcppi.write(new FileOutputStream(new File(argv[0]+".xml")));
	}
}
