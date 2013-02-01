#include "JObject.h"
#include "JClass.h"
#include "JClassLoader.h"
#include <sstream>

class JObjectClass : public JClass{
    public:
        JObjectClass():JClass(){
            canonicalName="java.lang.Objet";
            name="java.lang.Object";
            simpleName="Object";
        }

        JClass* getSuperclass(){
            return NULL;
        }

        JObject* newInstance(){
            return new JObject();
        }
};

static JClass* clazz;

JClass* JObject::getClazz(){
    if (clazz==NULL){
        clazz=new JObjectClass();
    }
    return clazz;
}

JObject::JObject(){
    this->_class=JObject::getClazz();
}


JObject::JObject(JClass* _class){
    this->_class=_class;
}

JObject::JObject(bool root){
}

JClass* JObject::getClass(){
    return this->_class;
}

string JObject::toString(){
    stringstream ss;
    ss<<getClass()->getName();
    ss<<"@";
    ss<<(this);
    return ss.str();
}

JObject::~JObject(){
}
