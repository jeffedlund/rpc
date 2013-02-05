#include "JVoid.h"
#include "JInstantiationException.h"
using namespace std;

class JVoidClass : public JClass{
  public:
    JVoidClass(){
        this->canonicalName="java.lang.Void";
        this->name="java.lang.Void";
        this->simpleName="Void";
        this->bIsPrimitive=false;
    }

    JClass* getSuperclass(){
        return JObject::getClazz();
    }

    JObject* newInstance(){
        throw new JInstantiationException("cannot instantiate object of class "+getName());
    }
};

static JClass* clazz;

JClass* JVoid::getClazz(){
    if (clazz==NULL){
        clazz=new JVoidClass();
    }
    return clazz;
}

