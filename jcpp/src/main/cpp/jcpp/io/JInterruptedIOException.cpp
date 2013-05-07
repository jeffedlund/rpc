#include "JInterruptedIOException.h"
#include "JClass.h"

namespace jcpp{
    namespace io{
        class JInterruptedIOExceptionClass : public JClass{
            protected:
                static JObject* getByteTransferred(JObject* object){
                    JInterruptedIOException* o=(JInterruptedIOException*)object;
                    return o->bytesTransferred;
                }

                static void setByteTransferred(JObject* obj,JObject* value){
                    JInterruptedIOException* b=(JInterruptedIOException*)obj;
                    delete b->bytesTransferred;
                    b->bytesTransferred=(JPrimitiveInt*)value;
                }

            public:
                JInterruptedIOExceptionClass(){
                    this->canonicalName="java.io.InterruptedIOException";
                    this->name="java.io.InterruptedIOException";
                    this->simpleName="InterruptedIOException";
                    this->serialVersionUID=4020568460727500567ULL;
                    addField(new JField("bytesTransferred",JPrimitiveInt::getClazz(),this,getByteTransferred,setByteTransferred));
                }

                JClass* getSuperclass(){
                    return JIOException::getClazz();
                }

                JObject* newInstance(){
                    return new JInterruptedIOException();
                }
        };

        static JClass* clazz;

        JClass* JInterruptedIOException::getClazz(){
            if (clazz==NULL){
                clazz=new JInterruptedIOExceptionClass();
            }
            return clazz;
        }

        JInterruptedIOException::JInterruptedIOException():JIOException(getClazz()){
            bytesTransferred=new JPrimitiveInt();
        }

        jint JInterruptedIOException::getBytesTransferred(){
            return bytesTransferred->get();
        }

        void JInterruptedIOException::setBytesTransferred(jint bt){
            bytesTransferred->set(bt);
        }

        JInterruptedIOException::~JInterruptedIOException(){
            delete bytesTransferred;
        }
    }
}
