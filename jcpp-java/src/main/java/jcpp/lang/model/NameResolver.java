package jcpp.lang.model;

import javax.xml.bind.annotation.*;
import java.util.*;

public class NameResolver{
    protected Map<String,String> classMapping;

    private static NameResolver defaultNameResolver=new NameResolver();
    public static NameResolver getDefault(){
        return defaultNameResolver;
    }

    public NameResolver(){
        classMapping=new HashMap<String,String>();
        initMapping();
    }

    protected void initMapping(){
        classMapping.put("boolean","JPrimitiveBoolean");
        classMapping.put("byte","JPrimitiveByte");
        classMapping.put("char","JPrimitiveChar");
        classMapping.put("double","JPrimitiveDouble");
        classMapping.put("float","JPrimitiveFloat");
        classMapping.put("int","JPrimitiveInt");
        classMapping.put("long","JPrimitiveLong");
        classMapping.put("short","JPrimitiveShort");
        classMapping.put("void","void");
    }

    public String resolvePackage(String name){
        if (name.startsWith("java.")){
            name="jcpp"+name.substring(4,name.length());
        }
        name=name.replaceAll("\\.","::");
        return name;
    }

    public String resolveClassName(String name){
        String tmp=classMapping.get(name);
        if (tmp!=null){
            return tmp;
        }
        name="J"+name;
        return name;
    }

    public String resolveInclude(String name){
        name="\""+name+".h\"";
        return name;
    }
}