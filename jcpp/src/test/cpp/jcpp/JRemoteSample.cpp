#include "JRemoteSample.h"
#include <sstream>
#include "JField.h"

namespace jcpp{
    class JRemoteSampleClass : public JClass{
      public:
        JRemoteSampleClass(){
            this->canonicalName="RemoteSample";
            this->name="RemoteObject";
            this->simpleName="RemoteObject";
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
        return o;
    }

    JIRemoteSample* JRemoteSample::getRemoteSample(){
        return this;
    }

    JRemoteSample::~JRemoteSample(){
    }
}

