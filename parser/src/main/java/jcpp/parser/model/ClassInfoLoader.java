package jcpp.parser.model;

import javax.xml.bind.*;
import javax.xml.bind.annotation.*;
import java.util.*;
import java.io.*;

@XmlRootElement
public class ClassInfoLoader{
	@XmlElementWrapper
	@XmlElement
	private List<ClassInfo> classInfos;
	@XmlElementWrapper
	@XmlElement
	private List<PackageInfo> packageInfos;

	public ClassInfoLoader(){
		this.classInfos=new ArrayList<ClassInfo>();
		this.packageInfos=new ArrayList<PackageInfo>();
	}

	public List<ClassInfo> getClassInfos(){
		return classInfos;
	}

	public void setClassInfos(List<ClassInfo> c){
		this.classInfos=c;
	}

	public List<PackageInfo> getPackageInfos(){
		return packageInfos;
	}

	public void setPackageInfos(List<PackageInfo> p){
		this.packageInfos=p;
	}
}
/*
public class ClassInfoLoader{
	private ClassLoader classLoader;
	private Map<String,ClassInfo> classInfos;
	private JAXBContext context;
	private Unmarshaller unmarshaller;

	public ClassInfoLoader(ClassLoader classLoader) throws Exception{
		this.classLoader=classLoader;
		classInfos=new HashMap<String,ClassInfo>();
		context=JAXBContext.newInstance(ClassInfo.class);
		unmarshaller=context.createUnmarshaller();
	}

	public ClassInfo loadClassInfo(String name) throws Exception{
		ClassInfo ci=classInfos.get(name);
		if (ci==null){
			String str=name.replace('.','\\')+".info";
			InputStream in=classLoader.getResourceAsStream(str);
			if (in==null){
				throw new Exception("could not find descriptor for class "+name+". File not found : "+str);
			}
			ci=(ClassInfo)unmarshaller.unmarshal(in);
			classInfos.put(name,ci);
			in.close();
		}
		return ci;
	}
}

*/