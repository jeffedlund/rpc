package jcpp.lang.model;

import java.util.*;
import java.io.*;
import freemarker.template.*;
import freemarker.cache.*;

public abstract class JCPPExporter{
	protected File output;
	protected Configuration cfg;

	protected JCPPExporter(){
	}

	public JCPPExporter setOutput(File output){
		this.output=output;
		return this;
	}

	protected void init() throws Exception{
		cfg=new Configuration();
    	cfg.setTemplateLoader(new ClassTemplateLoader());
	}

	protected void export(String path,CPPClass cppClass,Template template) throws Exception{
		File  file = new File(output,path);
	  	file.getParentFile().mkdirs();
	  	FileWriter fileWriter = new FileWriter(file);
      	template.process(cppClass.getTemplateInput(), fileWriter);
      	fileWriter.flush();
      	fileWriter.close();
	}
}