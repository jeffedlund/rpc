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

    static JObject* invokeCheckRemoteSample(JObject* object,vector<JObject*>* args){
        JIRemoteSample* r=dynamic_cast<JIRemoteSample*>(object);
        r->checkRemoteSample(dynamic_cast<JIRemoteSample*>(args->at(0)));
        return NULL;
    }

    static JObject* invokeCheckCalback(JObject* object,vector<JObject*>* args){
        JIRemoteSample* r=dynamic_cast<JIRemoteSample*>(object);
        r->checkCallback(dynamic_cast<JIRemoteSample*>(args->at(0)));
        return NULL;
    }

    class JIRemoteSampleClass : public JClass{
      public:
        JIRemoteSampleClass(){
            this->canonicalName="jcpp.IRemoteSample";
            this->name="jcpp.IRemoteSample";
            this->simpleName="IRemoteSample";
            this->bIsInterface=true;
        }

        virtual void fillDeclaredMethods(){
            vector<JClass*>* param=new vector<JClass*>();
            addMethod(new JMethod("getSampleObject",this,JSampleObject::getClazz(),param,invokeGetSampleObject));

            param=new vector<JClass*>();
            addMethod(new JMethod("getRemoteSample",this,JIRemoteSample::getClazz(),param,invokeGetRemoteSample));

            param=new vector<JClass*>();
            param->push_back(JIRemoteSample::getClazz());
            addMethod(new JMethod("checkRemoteSample",this,JIRemoteSample::getClazz(),param,invokeCheckRemoteSample));

            param=new vector<JClass*>();
            param->push_back(JIRemoteSample::getClazz());
            addMethod(new JMethod("checkCallback",this,JIRemoteSample::getClazz(),param,invokeCheckCalback));
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

