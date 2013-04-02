#include "JThrowable.h"
#include "JClass.h"
#include "Collections.h"
#include "JString.h"

namespace jcpp{
    namespace lang{
        static JObject* staticGetDetailMessage(JObject* object){
            JThrowable* th=(JThrowable*)object;
            return th->getMessage();
        }

        static void staticSetDetailMessage(JObject* object,JObject* value){
            JThrowable* th=(JThrowable*)object;
            th->setMessage((JString*)value);
        }

        static JObject* staticGetCause(JObject* object){
            JThrowable* th=(JThrowable*)object;
            return th->getCause();
        }

        static void staticSetCause(JObject* object,JObject* value){
            JThrowable* th=(JThrowable*)object;
            th->setCause((JThrowable*)value);
        }

        static JObject* staticGetStackTrace(JObject* object){
            JThrowable* th=(JThrowable*)object;
            return th->getStackTrace();
        }

        static void staticSetStackTrace(JObject* object,JObject* value){
            JThrowable* th=(JThrowable*)object;
            th->setStackTrace((JPrimitiveArray*)value);
        }

        class JThrowableClass : public JClass{
        public :
            JThrowableClass():JClass(){
                this->canonicalName="java.lang.Throwable";
                this->name="java.lang.Throwable";
                this->simpleName="Throwable";
                this->serialVersionUID=-3042686055658047285ULL;
                this->addField(new JField("detailMessage",JString::getClazz(),this,staticGetDetailMessage,staticSetDetailMessage));
                this->addField(new JField("cause",this,this,staticGetCause,staticSetCause));
                this->addField(new JField("stackTrace",JPrimitiveArray::getClazz(JStackTraceElement::getClazz()),this,staticGetStackTrace,staticSetStackTrace));
                this->addInterface(JSerializable::getClazz());
            }

            JClass* getSuperclass(){
                return JObject::getClazz();
            }

            JObject* newInstance(){
                return new JThrowable();
            }
        };


        static JClass* clazz;

        JClass* JThrowable::getClazz(){
            if (clazz==NULL){
                clazz=new JThrowableClass();
            }
            return clazz;
        }

        JThrowable::JThrowable(JClass* _class):JObject(_class){
            this->message=NULL;
            this->cause=NULL;
            this->stackTrace=NULL;
        }

        JThrowable::JThrowable():JObject(getClazz()){
            this->message=NULL;
            this->cause=NULL;
            this->stackTrace=NULL;
        }

        JThrowable::JThrowable(string message):JObject(getClazz()){
            this->message = new JString(message);
            this->cause=NULL;
            this->stackTrace=NULL;
        }

        JThrowable::JThrowable(JString* message):JObject(getClazz()){
            this->message = message;
            this->cause=NULL;
            this->stackTrace=NULL;
        }

        JThrowable::JThrowable(string message, JThrowable *cause):JObject(getClazz()){
            this->message = new JString(message);
            this->cause = cause;
            this->stackTrace=NULL;
        }

        JThrowable::JThrowable(JString* message, JThrowable *cause):JObject(getClazz()){
            this->message = message;
            this->cause = cause;
            this->stackTrace=NULL;
        }

        bool JThrowable::equals(JObject* o){
            if (!getClazz()->isAssignableFrom(o->getClass())){
                return false;
            }
            JThrowable* other=dynamic_cast<JThrowable*>(o);
            bool eq=true;
            if (other->message!=NULL && message!=NULL){
                eq=(*other->message)==(*message);
            }else{
                eq=other->message==NULL && message==NULL;
            }
            if (!eq){
                return false;
            }
            if (other->cause!=NULL && cause!=NULL){
                eq=(*other->cause)==(*cause);
            }else{
                eq=other->cause==NULL && cause==NULL;
            }
            if (!eq){
                return false;
            }
            if (other->stackTrace!=NULL && stackTrace!=NULL){
                eq=(*other->stackTrace)==(*stackTrace);
            }else{
                eq=other->stackTrace==NULL && stackTrace==NULL;
            }
            return eq;
        }

        JThrowable *JThrowable::getCause() {
            return cause;
        }

        void JThrowable::setCause(JThrowable* cause) {
            this->cause=cause;
        }

        void JThrowable::setMessage(JString* message){
            this->message = message;
        }

        JString* JThrowable::getMessage(){
            return this->message;
        }

        JPrimitiveArray* JThrowable::getStackTrace(){
            return stackTrace;
        }

        void JThrowable::setStackTrace(JPrimitiveArray* stackTrace){
            this->stackTrace=stackTrace;
        }

        void JThrowable::printStackTrace(ostream* os){
            string str=toString()+"\r\n";
            os->write(str.c_str(),str.size());
            if (stackTrace!=NULL){
                for (int i=0;i<stackTrace->size();i++){
                    JStackTraceElement* s=(JStackTraceElement*)stackTrace->get(i);
                    str="\tat "+s->toString()+"\r\n";
                    os->write(str.c_str(),str.size());
                }
                if (getCause()!=NULL){
                    str="Caused by:\r\n";
                    os->write(str.c_str(),str.size());
                    getCause()->printStackTrace(os);
                }
            }
            os->flush();
        }

        string JThrowable::toString(){
            return getClass()->getName()+":"+(message!=NULL?message->getString():"");
        }

        JThrowable::~JThrowable(){
            delete stackTrace;
            delete cause;
            delete message;
        }
    }
}

