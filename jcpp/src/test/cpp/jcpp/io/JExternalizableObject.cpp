#include "JExternalizableObject.h"
#include <sstream>
#include "JField.h"

namespace jcpp{
    namespace io{
        class JBool1Field : public JField{
        public:
            JBool1Field(JClass* p):JField("bool1",JPrimitiveBoolean::getClazz(), p){
            }

            JObject* get(JObject *object){
                JExternalizableObject* ExternalizableObject=(JExternalizableObject*)object;
                return ExternalizableObject->getBool1();
            }

            void set(JObject *object, JObject *value){
                JExternalizableObject* ExternalizableObject=(JExternalizableObject*)object;
                ExternalizableObject->setBool1((JPrimitiveBoolean*)value);
            }
        };

        class JByte1Field : public JField{
        public:
            JByte1Field(JClass* p):JField("byte1",JPrimitiveByte::getClazz(), p){
            }

            JObject* get(JObject *object){
                JExternalizableObject* ExternalizableObject=(JExternalizableObject*)object;
                return ExternalizableObject->getByte1();
            }

            void set(JObject *object, JObject *value){
                JExternalizableObject* ExternalizableObject=(JExternalizableObject*)object;
                ExternalizableObject->setByte1((JPrimitiveByte*)value);
            }
        };

        class JChar1Field : public JField{
        public:
            JChar1Field(JClass* p):JField("c1",JPrimitiveChar::getClazz(), p){
            }

            JObject* get(JObject *object){
                JExternalizableObject* ExternalizableObject=(JExternalizableObject*)object;
                return ExternalizableObject->getC1();
            }

            void set(JObject *object, JObject *value){
                JExternalizableObject* ExternalizableObject=(JExternalizableObject*)object;
                ExternalizableObject->setC1((JPrimitiveChar*)value);
            }
        };

        class JDouble1Field : public JField{
        public:
            JDouble1Field(JClass* p):JField("d1",JPrimitiveDouble::getClazz(), p){
            }

            JObject* get(JObject *object){
                JExternalizableObject* ExternalizableObject=(JExternalizableObject*)object;
                return ExternalizableObject->getD1();
            }

            void set(JObject *object, JObject *value){
                JExternalizableObject* ExternalizableObject=(JExternalizableObject*)object;
                ExternalizableObject->setD1((JPrimitiveDouble*)value);
            }
        };

        class JFloat1Field : public JField{
        public:
            JFloat1Field(JClass* p):JField("f1",JPrimitiveFloat::getClazz(), p){
            }

            JObject* get(JObject *object){
                JExternalizableObject* ExternalizableObject=(JExternalizableObject*)object;
                return ExternalizableObject->getF1();
            }

            void set(JObject *object, JObject *value){
                JExternalizableObject* ExternalizableObject=(JExternalizableObject*)object;
                ExternalizableObject->setF1((JPrimitiveFloat*)value);
            }
        };

        class JLong1Field : public JField{
        public:
            JLong1Field(JClass* p):JField("l1",JPrimitiveLong::getClazz(), p){
            }

            JObject* get(JObject *object){
                JExternalizableObject* ExternalizableObject=(JExternalizableObject*)object;
                return ExternalizableObject->getL1();
            }

            void set(JObject *object, JObject *value){
                JExternalizableObject* ExternalizableObject=(JExternalizableObject*)object;
                ExternalizableObject->setL1((JPrimitiveLong*)value);
            }
        };

        class JShort1Field : public JField{
        public:
            JShort1Field(JClass* p):JField("s1",JPrimitiveShort::getClazz(), p){
            }

            JObject* get(JObject *object){
                JExternalizableObject* ExternalizableObject=(JExternalizableObject*)object;
                return ExternalizableObject->getS1();
            }

            void set(JObject *object, JObject *value){
                JExternalizableObject* ExternalizableObject=(JExternalizableObject*)object;
                ExternalizableObject->setS1((JPrimitiveShort*)value);
            }
        };

        class JInt1Field : public JField{
        public:
            JInt1Field(JClass* p):JField("i1",JPrimitiveInt::getClazz(), p){
            }

            JObject* get(JObject *object){
                JExternalizableObject* ExternalizableObject=(JExternalizableObject*)object;
                return ExternalizableObject->getI1();
            }

            void set(JObject *object, JObject *value){
                JExternalizableObject* ExternalizableObject=(JExternalizableObject*)object;
                ExternalizableObject->setI1((JPrimitiveInt*)value);
            }
        };

        class JExternalizableObjectClass : public JClass{
          public:
            JExternalizableObjectClass(){
                this->canonicalName="jcpp.io.ExternalizableObject";
                this->name="jcpp.io.ExternalizableObject";
                this->simpleName="ExternalizableObject";
                this->serialVersionUID=40;
                addField(new JBool1Field(this));
                addField(new JByte1Field(this));
                addField(new JChar1Field(this));
                addField(new JDouble1Field(this));
                addField(new JFloat1Field(this));
                addField(new JLong1Field(this));
                addField(new JShort1Field(this));
                addField(new JInt1Field(this));
                addInterface(JExternalizable::getClazz());
            }

            JClass* getSuperclass(){
                return JObject::getClazz();
            }

            JObject* newInstance(){
                return new JExternalizableObject();
            }
        };

        static JClass* clazz;

        JClass* JExternalizableObject::getClazz(){
            if (clazz==NULL){
                clazz=new JExternalizableObjectClass();
            }
            return clazz;
        }

        JExternalizableObject::JExternalizableObject():JObject(getClazz()){
            bool1=NULL;
            byte1=NULL;
            c1=NULL;
            d1=NULL;
            f1=NULL;
            l1=NULL;
            s1=NULL;
            i1=NULL;
        }

        bool JExternalizableObject::equals(JObject* other){
            if (getClass()!=other->getClass()){
                return false;
            }
            JExternalizableObject* s=dynamic_cast<JExternalizableObject*>(other);
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

        JPrimitiveBoolean* JExternalizableObject::getBool1(){
            return bool1;
        }

        void JExternalizableObject::setBool1(JPrimitiveBoolean* bool1){
            this->bool1=bool1;
        }

        JPrimitiveByte* JExternalizableObject::getByte1(){
            return byte1;
        }

        void JExternalizableObject::setByte1(JPrimitiveByte* byte1){
            this->byte1=byte1;
        }

        JPrimitiveChar* JExternalizableObject::getC1(){
            return c1;
        }

        void JExternalizableObject::setC1(JPrimitiveChar* c1){
            this->c1=c1;
        }

        JPrimitiveDouble* JExternalizableObject::getD1(){
            return d1;
        }

        void JExternalizableObject::setD1(JPrimitiveDouble* d1){
            this->d1=d1;
        }

        JPrimitiveFloat* JExternalizableObject::getF1(){
            return f1;
        }

        void JExternalizableObject::setF1(JPrimitiveFloat* f1){
            this->f1=f1;
        }

        JPrimitiveLong* JExternalizableObject::getL1(){
            return l1;
        }

        void JExternalizableObject::setL1(JPrimitiveLong* l1){
            this->l1=l1;
        }

        JPrimitiveShort* JExternalizableObject::getS1(){
            return s1;
        }

        void JExternalizableObject::setS1(JPrimitiveShort* s1){
            this->s1=s1;
        }

        JPrimitiveInt* JExternalizableObject::getI1(){
            return i1;
        }

        void JExternalizableObject::setI1(JPrimitiveInt* i1){
            this->i1=i1;
        }

        JString JExternalizableObject::toString(){
            JString ss;
            ss<<"bool1="<<(bool1!=NULL?bool1->toString():"")<<"\r\n";
            ss<<"byte1="<<(byte1!=NULL?byte1->toString():"")<<"\r\n";
            ss<<"c1="<<(c1!=NULL?c1->toString():"NULL")<<"\r\n";
            ss<<"d1="<<(d1!=NULL?d1->toString():"NULL")<<"\r\n";
            ss<<"f1="<<(f1!=NULL?f1->toString():"NULL")<<"\r\n";
            ss<<"l1="<<(l1!=NULL?l1->toString():"NULL")<<"\r\n";
            ss<<"s1="<<(s1!=NULL?s1->toString():"NULL")<<"\r\n";
            ss<<"i1="<<(i1!=NULL?i1->toString():"NULL")<<"\r\n";
            return ss;
        }

        void JExternalizableObject::writeExternal(JObjectOutput* out){
            out->writeBoolean(bool1);
            out->writeByte(byte1);
            out->writeChar(c1);
            out->writeDouble(d1);
            out->writeFloat(f1);
            out->writeLong(l1);
            out->writeShort(s1);
            out->writeInt(i1);
        }

        void JExternalizableObject::readExternal(JObjectInput* in){
            bool1=in->readPrimitiveBool();
            byte1=in->readPrimitiveByte();
            c1=in->readPrimitiveChar();
            d1=in->readPrimitiveDouble();
            f1=in->readPrimitiveFloat();
            l1=in->readPrimitiveLong();
            s1=in->readPrimitiveShort();
            i1=in->readPrimitiveInt();
        }

        JExternalizableObject::~JExternalizableObject(){
            delete bool1;
            delete byte1;
            delete c1;
            delete d1;
            delete f1;
            delete l1;
            delete s1;
            delete i1;
        }
    }
}
