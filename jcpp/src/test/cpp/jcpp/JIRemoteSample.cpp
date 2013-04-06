#include "JIRemoteSample.h"
#include <sstream>
#include "JField.h"

namespace jcpp{

    static JObject* invokeGetSampleObject(JObject* object,vector<JObject*>*){
        JIRemoteSample* r=dynamic_cast<JIRemoteSample*>(object);
        return r->getSampleObject();
    }

    static JObject* invokeGetRemoteSample(JObject* object,vector<JObject*>*){
        JIRemoteSample* r=dynamic_cast<JIRemoteSample*>(object);
        return dynamic_cast<JObject*>(r->getRemoteSample());
    }

    class JIRemoteSampleClass : public JClass{
      public:
        JIRemoteSampleClass(){
            this->canonicalName="IRemoteSample";
            this->name="IRemoteSample";
            this->simpleName="IRemoteSample";
            this->bIsInterface=true;
        }

        virtual void fillDeclaredMethods(){
            vector<JClass*>* param=new vector<JClass*>();
            addMethod(new JMethod("getSampleObject",this,JSampleObject::getClazz(),param,invokeGetSampleObject));

            param=new vector<JClass*>();
            addMethod(new JMethod("getRemoteSample",this,JIRemoteSample::getClazz(),param,invokeGetRemoteSample));
        }

        JClass* getSuperclass(){
            return JInterface::getClazz();
        }
    };

    static JClass* clazz;

    JClass* JIRemoteSample::getClazz(){
        if (clazz==NULL){
            clazz=new JIRemoteSampleClass();
        }
        return clazz;
    }

    JIRemoteSample::~JIRemoteSample(){
    }
}

