#include "JSampleObject.h"
#include <sstream>
#include "JField.h"
#include "JIRemoteSample.h"

namespace jcpp{
    class JBool1Field : public JField{
    public:
        JBool1Field(JClass* p):JField("bool1",JPrimitiveBoolean::getClazz(),p){
        }

        JObject* get(JObject *object){
            JSampleObject* sampleObject=(JSampleObject*)object;
            return sampleObject->getBool1();
        }

        void set(JObject *object, JObject *value){
            JSampleObject* sampleObject=(JSampleObject*)object;
            sampleObject->setBool1((JPrimitiveBoolean*)value);
        }
    };

    class JByte1Field : public JField{
    public:
        JByte1Field(JClass* p):JField("byte1",JPrimitiveByte::getClazz(),p){
        }

        JObject* get(JObject *object){
            JSampleObject* sampleObject=(JSampleObject*)object;
            return sampleObject->getByte1();
        }

        void set(JObject *object, JObject *value){
            JSampleObject* sampleObject=(JSampleObject*)object;
            sampleObject->setByte1((JPrimitiveByte*)value);
        }
    };

    class JChar1Field : public JField{
    public:
        JChar1Field(JClass* p):JField("c1",JPrimitiveChar::getClazz(),p){
        }

        JObject* get(JObject *object){
            JSampleObject* sampleObject=(JSampleObject*)object;
            return sampleObject->getC1();
        }

        void set(JObject *object, JObject *value){
            JSampleObject* sampleObject=(JSampleObject*)object;
            sampleObject->setC1((JPrimitiveChar*)value);
        }
    };

    class JDouble1Field : public JField{
    public:
        JDouble1Field(JClass* p):JField("d1",JPrimitiveDouble::getClazz(),p){
        }

        JObject* get(JObject *object){
            JSampleObject* sampleObject=(JSampleObject*)object;
            return sampleObject->getD1();
        }

        void set(JObject *object, JObject *value){
            JSampleObject* sampleObject=(JSampleObject*)object;
            sampleObject->setD1((JPrimitiveDouble*)value);
        }
    };

    class JFloat1Field : public JField{
    public:
        JFloat1Field(JClass* p):JField("f1",JPrimitiveFloat::getClazz(),p){
        }

        JObject* get(JObject *object){
            JSampleObject* sampleObject=(JSampleObject*)object;
            return sampleObject->getF1();
        }

        void set(JObject *object, JObject *value){
            JSampleObject* sampleObject=(JSampleObject*)object;
            sampleObject->setF1((JPrimitiveFloat*)value);
        }
    };

    class JLong1Field : public JField{
    public:
        JLong1Field(JClass* p):JField("l1",JPrimitiveLong::getClazz(),p){
        }

        JObject* get(JObject *object){
            JSampleObject* sampleObject=(JSampleObject*)object;
            return sampleObject->getL1();
        }

        void set(JObject *object, JObject *value){
            JSampleObject* sampleObject=(JSampleObject*)object;
            sampleObject->setL1((JPrimitiveLong*)value);
        }
    };

    class JShort1Field : public JField{
    public:
        JShort1Field(JClass* p):JField("s1",JPrimitiveShort::getClazz(),p){
        }

        JObject* get(JObject *object){
            JSampleObject* sampleObject=(JSampleObject*)object;
            return sampleObject->getS1();
        }

        void set(JObject *object, JObject *value){
            JSampleObject* sampleObject=(JSampleObject*)object;
            sampleObject->setS1((JPrimitiveShort*)value);
        }
    };

    class JInt1Field : public JField{
    public:
        JInt1Field(JClass* p):JField("i1",JPrimitiveInt::getClazz(),p){
        }

        JObject* get(JObject *object){
            JSampleObject* sampleObject=(JSampleObject*)object;
            return sampleObject->getI1();
        }

        void set(JObject *object, JObject *value){
            JSampleObject* sampleObject=(JSampleObject*)object;
            sampleObject->setI1((JPrimitiveInt*)value);
        }
    };

    class JRSField : public JField{
    public:
        JRSField(JClass* p):JField("rs",JIRemoteSample::getClazz(),p){
        }

        JObject* get(JObject *object){
            JSampleObject* sampleObject=(JSampleObject*)object;
            JIRemoteSample* rs=sampleObject->getRemoteSample();
            if (rs==NULL){
                return NULL;
            }
            JObject* o=dynamic_cast<JObject*>(rs);
            return o;
        }

        void set(JObject *object, JObject *value){
            JSampleObject* sampleObject=(JSampleObject*)object;
            sampleObject->setRemoteSample((JIRemoteSample*)value);
        }
    };

    class JSampleObjectClass : public JClass{
      public:
        JSampleObjectClass(){
            this->canonicalName="SampleObject";
            this->name="SampleObject";
            this->simpleName="SampleObject";
            this->serialVersionUID=40;
            addField(new JBool1Field(this));
            addField(new JByte1Field(this));
            addField(new JChar1Field(this));
            addField(new JDouble1Field(this));
            addField(new JFloat1Field(this));
            addField(new JLong1Field(this));
            addField(new JShort1Field(this));
            addField(new JInt1Field(this));
            addField(new JRSField(this));
            addInterface(JSerializable::getClazz());
        }

        JClass* getSuperclass(){
            return JObject::getClazz();
        }

        JObject* newInstance(){
            return new JSampleObject();
        }
    };

    static JClass* clazz;

    JClass* JSampleObject::getClazz(){
        if (clazz==NULL){
            clazz=new JSampleObjectClass();
        }
        return clazz;
    }

    JSampleObject::JSampleObject():JObject(getClazz()){
        bool1=NULL;
        byte1=NULL;
        c1=NULL;
        d1=NULL;
        f1=NULL;
        l1=NULL;
        s1=NULL;
        i1=NULL;
        rs=NULL;
    }

    bool JSampleObject::equals(JObject* other){
        if (getClass()!=other->getClass()){
            return false;
        }
        JSampleObject* s=dynamic_cast<JSampleObject*>(other);
        if (*s->bool1==*bool1){
            if (*s->byte1==*byte1){
                if (*s->c1==*c1){
                    if (*s->d1==*d1){
                        if (*s->f1==*f1){
                            if (*s->i1==*i1){
                                if (*s->l1==*l1){
                                    if (*s->s1==*s1){
                                        return true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return false;
    }

    JPrimitiveBoolean* JSampleObject::getBool1(){
        return bool1;
    }

    void JSampleObject::setBool1(JPrimitiveBoolean* bool1){
        this->bool1=bool1;
    }

    JPrimitiveByte* JSampleObject::getByte1(){
        return byte1;
    }

    void JSampleObject::setByte1(JPrimitiveByte* byte1){
        this->byte1=byte1;
    }

    JPrimitiveChar* JSampleObject::getC1(){
        return c1;
    }

    void JSampleObject::setC1(JPrimitiveChar* c1){
        this->c1=c1;
    }

    JPrimitiveDouble* JSampleObject::getD1(){
        return d1;
    }

    void JSampleObject::setD1(JPrimitiveDouble* d1){
        this->d1=d1;
    }

    JPrimitiveFloat* JSampleObject::getF1(){
        return f1;
    }

    void JSampleObject::setF1(JPrimitiveFloat* f1){
        this->f1=f1;
    }

    JPrimitiveLong* JSampleObject::getL1(){
        return l1;
    }

    void JSampleObject::setL1(JPrimitiveLong* l1){
        this->l1=l1;
    }

    JPrimitiveShort* JSampleObject::getS1(){
        return s1;
    }

    void JSampleObject::setS1(JPrimitiveShort* s1){
        this->s1=s1;
    }

    JPrimitiveInt* JSampleObject::getI1(){
        return i1;
    }

    void JSampleObject::setI1(JPrimitiveInt* i1){
        this->i1=i1;
    }

    JIRemoteSample* JSampleObject::getRemoteSample(){
        return rs;
    }

    void JSampleObject::setRemoteSample(JIRemoteSample* rs){
        if (this->rs!=NULL){
            delete this->rs;
        }
        this->rs=rs;
    }

    string JSampleObject::toString(){
        stringstream ss;
        ss<<"bool1="<<(bool1!=NULL?bool1->toString():"")<<"\r\n";
        ss<<"byte1="<<(byte1!=NULL?byte1->toString():"")<<"\r\n";
        ss<<"c1="<<(c1!=NULL?c1->toString():"NULL")<<"\r\n";
        ss<<"d1="<<(d1!=NULL?d1->toString():"NULL")<<"\r\n";
        ss<<"f1="<<(f1!=NULL?f1->toString():"NULL")<<"\r\n";
        ss<<"l1="<<(l1!=NULL?l1->toString():"NULL")<<"\r\n";
        ss<<"s1="<<(s1!=NULL?s1->toString():"NULL")<<"\r\n";
        ss<<"i1="<<(i1!=NULL?i1->toString():"NULL")<<"\r\n";
        ss<<"rs="<<(rs!=NULL?((JObject*)rs)->toString():"NULL")<<"\r\n";
        return ss.str();
    }

    JSampleObject::~JSampleObject(){
        delete bool1;
        delete byte1;
        delete c1;
        delete d1;
        delete f1;
        delete l1;
        delete s1;
        delete i1;
        delete rs;
    }
}
