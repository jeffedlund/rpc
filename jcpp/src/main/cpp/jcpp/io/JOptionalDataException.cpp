#include "JOptionalDataException.h"

namespace jcpp{
    namespace io{
        class JOptionalDataExceptionClass : public JClass{
            static JObject* staticGetLength(JObject* object){
                JOptionalDataException* th=(JOptionalDataException*)object;
                return th->getPLength();
            }

            static void staticSetLength(JObject* object,JObject* value){
                JOptionalDataException* th=(JOptionalDataException*)object;
                th->setPLength((JPrimitiveInt*)value);
            }

            static JObject* staticGetEOF(JObject* object){
                JOptionalDataException* th=(JOptionalDataException*)object;
                return th->getPEOF();
            }

            static void staticSetEOF(JObject* object,JObject* value){
                JOptionalDataException* th=(JOptionalDataException*)object;
                th->setPEOF((JPrimitiveBoolean*)value);
            }

        public:
            JOptionalDataExceptionClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.io.OptionalDataException";
                name="java.io.OptionalDataException";
                simpleName="OptionalDataException";
                serialVersionUID=-8011121865681257820ULL;
                this->addField(new JField("length",JPrimitiveInt::getClazz(),this,staticGetLength,staticSetLength));
                this->addField(new JField("eof",JPrimitiveBoolean::getClazz(),this,staticGetEOF,staticSetEOF));
            }

            JClass* getSuperclass(){
                return JObjectStreamException::getClazz();
            }

            JObject* newInstance(){
                return new JOptionalDataException();
            }
        };

        static JClass* clazz;

        JClass* JOptionalDataException::getClazz(){
            if (clazz==NULL){
                clazz=new JOptionalDataExceptionClass();
            }
            return clazz;
        }

        JOptionalDataException::JOptionalDataException(JClass* _class):JObjectStreamException(_class){
            this->length=new JPrimitiveInt(0);
            this->eof=new JPrimitiveBoolean(false);
        }

        JOptionalDataException::JOptionalDataException():JObjectStreamException(getClazz()){
            this->length=new JPrimitiveInt(0);
            this->eof=new JPrimitiveBoolean(false);
        }

        JOptionalDataException::JOptionalDataException(string message) : JObjectStreamException(getClazz()){
            this->message=new JString(message);
            this->length=new JPrimitiveInt(0);
            this->eof=new JPrimitiveBoolean(false);
        }

        jint JOptionalDataException::getLength(){
            return length->get();
        }

        void JOptionalDataException::setLength(jint l){
            length->set(l);
        }

        JPrimitiveInt* JOptionalDataException::getPLength(){
            return length;
        }

        void JOptionalDataException::setPLength(JPrimitiveInt* l){
            delete this->length;
            this->length=l;
        }

        jbool JOptionalDataException::getEOF(){
            return eof->get();
        }

        void JOptionalDataException::setEOF(jbool eof){
            this->eof->set(eof);
        }

        JPrimitiveBoolean* JOptionalDataException::getPEOF(){
            return eof;
        }

        void JOptionalDataException::setPEOF(JPrimitiveBoolean* eof){
            delete this->eof;
            this->eof=eof;
        }

        JOptionalDataException::~JOptionalDataException(){
            delete length;
            delete eof;
        }
    }
}
