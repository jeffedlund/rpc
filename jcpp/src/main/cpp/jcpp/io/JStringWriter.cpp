#include "JStringWriter.h"
#include "JClass.h"

namespace jcpp{
    namespace io{
        class JStringWriterClass : public JClass{
            public:
                JStringWriterClass(){
                    this->canonicalName="java.io.StringWriter";
                    this->name="java.io.StringWriter";
                    this->simpleName="StringWriter";
                }

                JClass* getSuperclass(){
                    return JWriter::getClazz();
                }

                JObject* newInstance(){
                    return new JStringWriter();
                }
        };

        static JClass* clazz;

        JClass* JStringWriter::getClazz(){
            if (clazz==NULL){
                clazz=new JStringWriterClass();
            }
            return clazz;
        }

        JStringWriter::JStringWriter():JWriter(getClazz()){
            this->buf=new JStringBuffer();
            this->lock=buf;
        }

        void JStringWriter::write(jint c){
            buf->append((jint)c);
        }

        void JStringWriter::write(jchar buf[],jint off,jint len){
            this->buf->append(buf,off,len);
        }

        void JStringWriter::write(JString* str){
            buf->append((JString*)str);
        }

        void JStringWriter::write(JString str){
            buf->append((JString)str);
        }

        void JStringWriter::write(JString* str,jint off,jint len){
            buf->append(dynamic_cast<JCharSequence*>(str),off,len);
        }

        void JStringWriter::write(JString str,jint off,jint len){
            buf->append((JString)str,off,len);
        }

        JStringWriter* JStringWriter::append(JCharSequence* csq){
            if (csq==NULL){
                write("null");
            }else{
                write(csq->toString());
            }
            return this;
        }

        JStringWriter* JStringWriter::append(JCharSequence* csq,jint start,jint end){
            buf->append(csq,start,end);
            return this;
        }

        JStringWriter* JStringWriter::append(jchar c){
            buf->append((jchar)c);
            return this;
        }

        JString JStringWriter::toString(){
            return buf->toString();
        }

        JStringBuffer* JStringWriter::getBuffer(){
            return buf;
        }

        void JStringWriter::flush(){
        }

        void JStringWriter::close(){
        }

        JStringWriter::~JStringWriter(){
            delete buf;
        }
    }
}
