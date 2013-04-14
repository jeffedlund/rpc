package jcpp.lang.model;

import java.util.*;
import java.io.*;
import freemarker.template.*;
import freemarker.cache.*;

public class JCPPClassExporter extends JCPPExporter{
	private Template hTemplate;
	private Template cppTemplate;
	private JCPPClass jcppClass;

	protected JCPPClassExporter(){
	}

	public static JCPPClassExporter create(){
		return new JCPPClassExporter();
	}

	public JCPPClassExporter setOutput(File output){
		super.setOutput(output);
		return this;
	}

	public JCPPClass getJCPPClass(){
		return jcppClass;
	}

	public JCPPClassExporter setJCPPClass(JCPPClass jcppClass){
		this.jcppClass=jcppClass;
		return this;
	}

	public void export() throws Exception{
		init();
    	hTemplate = cfg.getTemplate("jcpp/lang/model/hclass.ftl");
    	cppTemplate = cfg.getTemplate("jcpp/lang/model/cppclass.ftl");

    	CPPClass clazz=jcppClass.getClazz();

    	//generating h files
    	export(clazz.getHFilePath(),clazz,hTemplate);

      	//generating cpp files
      	export(clazz.getCPPFilePath(),clazz,cppTemplate);
	}

	public static void main(String[] argv) throws Exception{
		JavaClass jc=JavaClass.from(new FileInputStream(new File("javaclassbean.xml")));
  		JCPPClass jcppi=JCPPClassBuilder.create().setJavaClass(jc).build();
  		JCPPClassExporter.create().setOutput(new File(".")).setJCPPClass(jcppi).export();
  		jcppi.write(new FileOutputStream(new File("jcppibean.xml")));
	}
}