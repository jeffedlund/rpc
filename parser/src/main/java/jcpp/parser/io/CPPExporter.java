package jcpp.parser.io;

import javax.xml.bind.annotation.*;
import java.util.*;
import java.io.*;
import freemarker.template.*;
import freemarker.cache.*;
import jcpp.parser.model.*;

public class CPPExporter{
	private File dir;
	private Configuration cfg;
	private Template hTemplate;
	private Template cppTemplate;

    public CPPExporter(String d) throws Exception{
    	dir=new File(d);
    	cfg=new Configuration();
    	cfg.setTemplateLoader(new ClassTemplateLoader());
    	//cfg.setDirectoryForTemplateLoading(dir);
    	hTemplate = cfg.getTemplate("jcpp/parser/model/hclass.ftl");
    	cppTemplate = cfg.getTemplate("jcpp/parser/model/cppclass.ftl");
    }

    public void export(CPPClassInfo ci) throws Exception{
    	Map<String, Object> input = new HashMap<String, Object>();
      	input.put("class", ci);

	  	File  hFile = new File(dir,ci.getDirectory()+ci.getClassName()+".h");
	  	hFile.getParentFile().mkdirs();
		File cppFile = new File(dir,ci.getDirectory()+ci.getClassName()+".cpp");
      	cppFile.getParentFile().mkdirs();

      	FileWriter hFileWriter = new FileWriter(hFile);
      	FileWriter cppFileWriter = new FileWriter(cppFile);

      	hTemplate.process(input, hFileWriter);
      	cppTemplate.process(input, cppFileWriter);
      	hFileWriter.flush();
      	cppFileWriter.flush();
      }

      public static void main(String[] argv) throws Exception{
      		CPPExporter e=new CPPExporter(".");
      		CPPClassInfo ci=new CPPClassInfo();
      		ci.setIfndef("JMYCLASS");
      		ci.getIncludes().add("\"inc1.h\"");
      		ci.getIncludes().add("\"inc2.h\"");
      		ci.getIncludes().add("\"inc3.h\"");
      		ci.getUseNamespace().add("use_n1");
      		ci.getUseNamespace().add("use_n2");
      		ci.getUseNamespace().add("use_n3");
			
			ci.getNamespace().add("n1");
      		ci.getNamespace().add("n2");
      		ci.getNamespace().add("n3");

			ci.setCanonicalName("n1.n2.n3.JMyClass");
			ci.setName("n1.n2.n3.JMyClass");
			ci.setSimpleName("JMyClass");
      		ci.setClassName("JMyClass");
      		ci.setParentClass("JParentClass");

      		FieldInfo f1=new FieldInfo();
      		f1.setName("f1");
      		f1.setType("t1");
      		f1.setGetter("getF1");
      		f1.setSetter("setF1");
      		ci.getDeclaredFields().add(f1);
      		FieldInfo f2=new FieldInfo();
      		f2.setName("f2");
      		f2.setType("t2");
      		f2.setGetter("getF2");
      		f2.setSetter("setF2");
      		ci.getDeclaredFields().add(f2);
      		FieldInfo f3=new FieldInfo();
      		f3.setName("f3");
      		f3.setType("t3");
      		f3.setGetter("getF3");
      		f3.setSetter("setF3");
      		ci.getDeclaredFields().add(f3);

      		ci.getInterfaces().add("JI1");
      		ci.getInterfaces().add("JI2");
      		ci.getInterfaces().add("JI3");

      		MethodInfo m1=new MethodInfo();
      		m1.setName("m1");
      		m1.setReturnType("void");
      		m1.getParameterType().add("f1");
      		m1.getParameterType().add("f2");
      		ci.getDeclaredMethods().add(m1);
      		MethodInfo m2=new MethodInfo();
      		m2.setName("m2");
      		m2.setReturnType("f2");
      		m2.getParameterType().add("f1");
      		m2.getParameterType().add("f2");
      		ci.getDeclaredMethods().add(m2);
      		MethodInfo m3=new MethodInfo();
      		m3.setName("m3");
      		m3.setReturnType("f3");
      		m3.getParameterType().add("f1");
      		m3.getParameterType().add("f2");
      		ci.getDeclaredMethods().add(m3);

      		ci.setSerialVersionUID(11111);
      		e.export(ci);
      }
}