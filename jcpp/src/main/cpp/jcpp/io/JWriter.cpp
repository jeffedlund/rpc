#include "JWriter.h"
#include "JClass.h"

namespace jcpp{
    namespace io{
        class JWriterClass : public JClass{
            public:
                JWriterClass(){
                    this->canonicalName="java.io.Writer";
                    this->name="java.io.Writer";
                    this->simpleName="Writer";
                    addInterface(JAppendable::getClazz());
                    addInterface(JCloseable::getClazz());
                    addInterface(JFlushable::getClazz());
                }

                JClass* getSuperclass(){
                    return JObject::getClazz();
                }
        };

        static JClass* clazz;

        JClass* JWriter::getClazz(){
            if (clazz==NULL){
                clazz=new JWriterClass();
            }
            return clazz;
        }

        JWriter::JWriter(JClass* _class):JObject(_class){
            writeBuffer=new jchar[1024];
            lock=this;
        }

        JWriter::JWriter(JClass* _class,JObject* lock):JObject(_class){
            writeBuffer=new jchar[1024];
            this->lock=lock;
        }

        void  JWriter::write(jint c){
            lock->lock();
            writeBuffer[0]=(jchar)c;
            write(writeBuffer,0,1);
            lock->unlock();
        }

        void  JWriter::write(JString* str){
            write(str,0,str->length());
        }

        void  JWriter::write(JString* str,jint off,jint len){
            lock->lock();
            jchar* cbuf;
            if (len <= 1024) {
               cbuf = writeBuffer;
            } else {
               cbuf = new jchar[len];
            }
            str->getChars(off, (off + len), cbuf, 0);
            write(cbuf, 0, len);
            if (len>1024) {
                delete[] cbuf;
            }
            lock->unlock();
        }

        void  JWriter::write(JString str){
            write(str,0,str.length());
        }

        void  JWriter::write(JString str,jint off,jint len){
            lock->lock();
            jchar* cbuf;
            if (len <= 1024) {
               cbuf = writeBuffer;
            } else {
               cbuf = new jchar[len];
            }
            for (jint i=0;i<len;i++){
                cbuf[i]=(jchar)str.charAt(off+i);
            }
            write(cbuf, 0, len);
            if (len>1024) {
                delete[] cbuf;
            }
            lock->unlock();
        }

        JWriter * JWriter::append(JCharSequence* csq){
            if (csq==NULL){
                write(JString::intern("null"));
            }else{
                write(csq->toString());
            }
            return this;
        }

        JWriter * JWriter::append(JCharSequence* csq, jint start, jint end){
            JCharSequence* cs = (csq==NULL ? dynamic_cast<JCharSequence*>(JString::intern("null")) : csq);
            write(cs->subSequence(start,end)->toString());
            return this;
        }

        JWriter * JWriter::append(jchar c){
            write(c);
            return this;
        }

        JWriter::~JWriter(){
            delete[] writeBuffer;
        }
    }
}
