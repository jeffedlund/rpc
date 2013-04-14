package jcpp.lang.model;

import java.util.*;
import java.io.*;
import freemarker.template.*;
import freemarker.cache.*;

public class JCPPInterfaceExporter extends JCPPExporter{
	private Template hTemplate;
	private Template cppTemplate;
	private Template hProxyTemplate;
	private Template cppProxyTemplate;
	private JCPPInterface jcppInterface;

	protected JCPPInterfaceExporter(){
	}

	public static JCPPInterfaceExporter create(){
		return new JCPPInterfaceExporter();
	}

	public JCPPInterfaceExporter setOutput(File output){
		super.setOutput(output);
		return this;
	}

	public JCPPInterface getJCPPInterface(){
		return jcppInterface;
	}

	public JCPPInterfaceExporter setJCPPInterface(JCPPInterface jcppInterface){
		this.jcppInterface=jcppInterface;
		return this;
	}

	public void export() throws Exception{
		init();
    	hTemplate = cfg.getTemplate("jcpp/lang/model/hinterface.ftl");
    	cppTemplate = cfg.getTemplate("jcpp/lang/model/cppinterface.ftl");
    	hProxyTemplate = cfg.getTemplate("jcpp/lang/model/hproxyinterface.ftl");
    	cppProxyTemplate = cfg.getTemplate("jcpp/lang/model/cppproxyinterface.ftl");

    	CPPClass inter=jcppInterface.getInterface();

    	//generating h files
    	export(inter.getHFilePath(),inter,hTemplate);

      	//generating cpp files
      	export(inter.getCPPFilePath(),inter,cppTemplate);

      	CPPClass proxyInterface=jcppInterface.getProxyInterface();

      	//generating h files
      	export(proxyInterface.getHFilePath(),proxyInterface,hProxyTemplate);

      	//generating cpp files
      	export(proxyInterface.getCPPFilePath(),proxyInterface,cppProxyTemplate);
	}

	public static void main(String[] argv) throws Exception{
		JavaClass jc=JavaClass.from(new FileInputStream(new File("javaclass.xml")));
  		JCPPInterface jcppi=JCPPInterfaceBuilder.create().setJavaClass(jc).build();
  		JCPPInterfaceExporter.create().setOutput(new File(".")).setJCPPInterface(jcppi).export();
  		jcppi.write(new FileOutputStream(new File("jcppi.xml")));
	}
}