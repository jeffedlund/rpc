#include "JSerializable.h"
#include "JInstantiationException.h"

class JSerializableClass : public JClass{
public:
    JSerializableClass():JClass(JClassLoader::getBootClassLoader()){
        canonicalName="java.io.Serializable";
        name="java.io.Serializable";
        simpleName="Serializable";
        serialVersionUID=0;
        bIsInterface=true;
    }

    JClass* getSuperclass(){
        return JInterface::getClazz();
    }

    JObject* newInstance(){
        throw new JInstantiationException("cannot instantiate object of class "+getName());
    }
};

static JClass* clazz;

JClass* JSerializable::getClazz(){
    if (clazz==NULL){
        clazz=new JSerializableClass();
    }
    return clazz;
}

JSerializable::JSerializable():JInterface(){
}
