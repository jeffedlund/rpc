#include "JWriteAbortedException.h"
#include "JClass.h"

namespace jcpp{
    namespace io{
        class JWriteAbortedExceptionClass : public JClass{
            protected:
                static JObject* getDetail(JObject* object){
                    JWriteAbortedException* o=(JWriteAbortedException*)object;
                    return o->getDetail();
                }

                static void setDetail(JObject* obj,JObject* value){
                    JWriteAbortedException* b=(JWriteAbortedException*)obj;
                    b->setDetail((JException*)value);
                }

            public:
                JWriteAbortedExceptionClass(){
                    this->canonicalName="java.io.WriteAbortedException";
                    this->name="java.io.WriteAbortedException";
                    this->simpleName="WriteAbortedException";
                    this->serialVersionUID=-3326426625597282442ULL;
                    addField(new JField("detail",JException::getClazz(),this,getDetail,setDetail));
                }

                JClass* getSuperclass(){
                    return JObjectStreamException::getClazz();
                }

                JObject* newInstance(){
                    return new JWriteAbortedException();
                }
        };

        static JClass* clazz;

        JClass* JWriteAbortedException::getClazz(){
            if (clazz==NULL){
                clazz=new JWriteAbortedExceptionClass();
            }
            return clazz;
        }

        JWriteAbortedException::JWriteAbortedException(string message,JException* ex):JObjectStreamException(getClazz()){
            this->message=new JString(message);
            this->detail=ex;
        }

        JWriteAbortedException::JWriteAbortedException():JObjectStreamException(getClazz()){
            this->detail=NULL;
        }

        JThrowable * JWriteAbortedException::getCause(){
            return getDetail();
        }

        JException* JWriteAbortedException::getDetail(){
            return detail;
        }

        void JWriteAbortedException::setDetail(JException* e){
            if (detail!=NULL){
                delete detail;
            }
            this->detail=e;
        }

        JWriteAbortedException::~JWriteAbortedException(){
            if (detail!=NULL){
                delete detail;
            }
        }
    }
}

//        
