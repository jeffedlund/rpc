#include "JByteArrayOutputStream.h"
#include "JClass.h"

namespace jcpp{
    namespace io{
        class JByteArrayOutputStreamClass : public JClass{
            public:
                JByteArrayOutputStreamClass(){
                    this->canonicalName="java.io.ByteArrayOutputStream";
                    this->name="java.io.ByteArrayOutputStream";
                    this->simpleName="ByteArrayOutputStream";
                }

                JClass* getSuperclass(){
                    return JOutputStream::getClazz();
                }
        };

        static JClass* clazz;

        JClass* JByteArrayOutputStream::getClazz(){
            if (clazz==NULL){
                clazz=new JByteArrayOutputStreamClass();
            }
            return clazz;
        }

        JByteArrayOutputStream::JByteArrayOutputStream():JOutputStream(getClazz()){
            buf=new vector<jbyte>();
        }

        void  JByteArrayOutputStream::write(jint b){
            lock();
            buf->push_back((jbyte)b);
            unlock();
        }

        void  JByteArrayOutputStream::write(jbyte b[], jint off, jint l){
            lock();
            for (jint i=0;i<l;i++){
                buf->push_back(b[i+off]);
            }
            unlock();
        }

        void  JByteArrayOutputStream::writeTo(JOutputStream* out){
            lock();
            out->write(buf->data(),0,buf->size());
            unlock();
        }

        void  JByteArrayOutputStream::reset(){
            lock();
            buf->clear();
            unlock();
        }

        vector<jbyte>* JByteArrayOutputStream::toByteArray(){
            lock();
            vector<jbyte>* v=new vector<jbyte>(buf->begin(),buf->end());
            unlock();
            return v;
        }

        jint JByteArrayOutputStream::size(){
            lock();
            jint i=buf->size();
            unlock();
            return i;
        }

        JString JByteArrayOutputStream::toString(){
            lock();
            JString str(buf);//TODO test
            unlock();
            return str;
        }

        void  JByteArrayOutputStream::close(){
        }

        JByteArrayOutputStream::~JByteArrayOutputStream(){
            delete buf;
        }
    }
}
