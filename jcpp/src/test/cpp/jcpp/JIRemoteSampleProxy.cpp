#include "JIRemoteSampleProxy.h"
#include "JSerializable.h"
#include "JInstantiationException.h"
#include "JVoid.h"
#include "JProxy.h"
using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{

    JIRemoteSampleProxy::JIRemoteSampleProxyClass::JIRemoteSampleProxyClass():JProxyClass(){
        this->canonicalName="jcpp.IRemoteSampleProxy";
        this->name="jcpp.IRemoteSampleProxy";
        this->simpleName="IRemoteSampleProxy";
        this->bIsProxy=true;
        addInterface(JIRemoteSample::getClazz());
    }

    JClass* JIRemoteSampleProxy::JIRemoteSampleProxyClass::getSuperclass(){
        return JProxy::getClazz();
    }

    JObject* JIRemoteSampleProxy::JIRemoteSampleProxyClass::newInstance(){
        return new JIRemoteSampleProxy();
    }

    static JClass* clazz;

    JClass* JIRemoteSampleProxy::getClazz(){
        if (clazz==NULL){
            clazz=new JIRemoteSampleProxyClass();
        }
        return clazz;
    }

    JIRemoteSampleProxy::JIRemoteSampleProxy():JProxy(getClazz()){
    }

    JSampleObject* JIRemoteSampleProxy::getSampleObject(){
        vector<JObject*> args;
        return (JSampleObject*)invoke("getSampleObject",&args);
    }

    JIRemoteSample* JIRemoteSampleProxy::getRemoteSample(){
        vector<JObject*> args;
        return (JIRemoteSample*)invoke("getRemoteSample",&args);
    }

    void JIRemoteSampleProxy::checkRemoteSample(JIRemoteSample* rs){
        vector<JObject*> args;
        args.push_back(dynamic_cast<JObject*>(rs));
        invoke("checkRemoteSample",&args);
    }

    void JIRemoteSampleProxy::checkCallback(JIRemoteSample* rs){
        vector<JObject*> args;
        args.push_back(dynamic_cast<JObject*>(rs));
        invoke("checkCallback",&args);
    }

    JIRemoteSampleProxy::~JIRemoteSampleProxy(){
    }
}
