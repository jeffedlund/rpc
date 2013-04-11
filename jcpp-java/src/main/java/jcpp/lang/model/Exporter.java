package jcpp.lang.model;

import java.util.*;
import java.io.*;
import freemarker.template.*;
import freemarker.cache.*;

public class Exporter{
	private File output;
	private Configuration cfg;
	private Template hTemplate;
	private Template cppTemplate;
	private Template hProxyTemplate;
	private Template cppProxyTemplate;
	private CPPInterface cppInterface;

	public Exporter(){
	}

	public void setOutput(File output){
		this.output=output;
	}

	public CPPInterface getCPPInterface(){
		return cppInterface;
	}

	public void setCPPInterface(CPPInterface cppInterface){
		this.cppInterface=cppInterface;
	}

	public void export() throws Exception{
		cfg=new Configuration();
    	cfg.setTemplateLoader(new ClassTemplateLoader());
    	hTemplate = cfg.getTemplate("jcpp/lang/model/hinterface.ftl");
    	cppTemplate = cfg.getTemplate("jcpp/lang/model/cppinterface.ftl");
    	hProxyTemplate = cfg.getTemplate("jcpp/lang/model/hproxyinterface.ftl");
    	cppProxyTemplate = cfg.getTemplate("jcpp/lang/model/cppproxyinterface.ftl");

    	HCPPInterface hInterface=cppInterface.getHInterface();

    	//generating h files
    	File  hFile = new File(output,hInterface.getHFilePath());
	  	hFile.getParentFile().mkdirs();
	  	FileWriter hFileWriter = new FileWriter(hFile);
      	hTemplate.process(hInterface.getTemplateInput(), hFileWriter);
      	hFileWriter.flush();
      	hFileWriter.close();

      	//generating cpp files
		File  cppFile = new File(output,hInterface.getCPPFilePath());
	  	cppFile.getParentFile().mkdirs();
	  	FileWriter cppFileWriter = new FileWriter(cppFile);
      	cppTemplate.process(hInterface.getTemplateInput(), cppFileWriter);
      	cppFileWriter.flush();
      	cppFileWriter.close();

      	HCPPInterface proxyInterface=cppInterface.getProxyInterface();
      	//generating h files
    	File  hProxyFile = new File(output,proxyInterface.getHFilePath());
	  	hProxyFile.getParentFile().mkdirs();
	  	FileWriter hProxyFileWriter = new FileWriter(hProxyFile);
      	hProxyTemplate.process(proxyInterface.getTemplateInput(), hProxyFileWriter);
      	hProxyFileWriter.flush();
      	hProxyFileWriter.close();

      	//generating cpp files
		File  cppProxyFile = new File(output,proxyInterface.getCPPFilePath());
	  	cppProxyFile.getParentFile().mkdirs();
	  	FileWriter cppProxyFileWriter = new FileWriter(cppProxyFile);
      	cppProxyTemplate.process(proxyInterface.getTemplateInput(), cppProxyFileWriter);
      	cppProxyFileWriter.flush();
      	cppProxyFileWriter.close();
	}

	public static void main(String[] argv) throws Exception{
		JavaInterface ji=new JavaInterface();
		ji.setCanonicalName("n1.n2.n3.n4.MyInterface");
		ji.setSimpleName("MyInterface");
		ji.setName("n1.n2.n3.n4.MyInterface");
		ji.getImports().add("java.util.List");
		ji.getImports().add("java.util.ArrayList");
		ji.getImports().add("java.util.Collection");
		ji.getImports().add("n1.n2.n3.n4.n5.Toto");
		ji.setParent("p1.p2.p3.MyParent");
		ji.getInterfaces().add("i1.i2.i3.I1");
		ji.getInterfaces().add("i1.i2.i3.I2");
		
		JavaMethod jm=new JavaMethod();
		jm.setName("m1");
		jm.setReturnType("void");
  		jm.getParameterType().add("f1.f2.f3.P1");
  		jm.getParameterType().add("f1.f2.f3.P2");
  		ji.getMethods().add(jm);

  		jm=new JavaMethod();
		jm.setName("m2");
		jm.setReturnType("f1.f2.f3.R1");
  		jm.getParameterType().add("f1.f2.f3.P1");
  		jm.getParameterType().add("f1.f2.f3.P2");
  		ji.getMethods().add(jm);

  		CPPInterface cppi=new CPPInterface();
  		DefaultJCPPTransformer defaultJCPPTransformer=new DefaultJCPPTransformer();
  		defaultJCPPTransformer.tranform(ji,cppi);

  		Exporter exporter=new Exporter();
  		exporter.setOutput(new File("."));
  		exporter.setCPPInterface(cppi);
  		exporter.export();

	}
}