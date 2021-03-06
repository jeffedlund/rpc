#include "JRemoteSample.h"
#include <sstream>
#include "JField.h"

namespace jcpp{
    class JRemoteSampleClass : public JClass{
      public:
        JRemoteSampleClass(){
            this->canonicalName="jcpp.RemoteSample";
            this->name="jcpp.RemoteSample";
            this->simpleName="RemoteSample";
            addInterface(JIRemoteSample::getClazz());
        }

        JClass* getSuperclass(){
            return JObject::getClazz();
        }
    };

    static JClass* clazz;

    JClass* JRemoteSample::getClazz(){
        if (clazz==NULL){
            clazz=new JRemoteSampleClass();
        }
        return clazz;
    }

    JRemoteSample::JRemoteSample():JObject(getClazz()){
    }

    JSampleObject* JRemoteSample::getSampleObject(){
        JSampleObject* o=new JSampleObject();
        o->setBool1(new JPrimitiveBoolean(false));
        o->setByte1(new JPrimitiveByte(123));
        o->setC1(new JPrimitiveChar('c'));
        o->setD1(new JPrimitiveDouble(456));
        o->setF1(new JPrimitiveFloat(789));
        o->setL1(new JPrimitiveLong(124));
        o->setS1(new JPrimitiveShort(235));
        o->setI1(new JPrimitiveInt(345));
        o->setRemoteSample(this);
        return o;
    }

    JIRemoteSample* JRemoteSample::getRemoteSample(){
        return this;
    }

    void JRemoteSample::checkRemoteSample(JIRemoteSample* rs){
        assert(rs==this);
    }

    void JRemoteSample::checkCallback(JIRemoteSample* rs){
        cout<<"debut checkcallback\r\n";
        cout<<rs->getSampleObject();
        cout<<"\r\n";
        cout.flush();
    }

    JRemoteSample::~JRemoteSample(){
    }
}

