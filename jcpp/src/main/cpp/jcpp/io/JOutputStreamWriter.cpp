#include "JOutputStreamWriter.h"
#include "JClass.h"

namespace jcpp{
    namespace io{
        class JOutputStreamWriterClass : public JClass{
            public:
                JOutputStreamWriterClass(){
                    this->canonicalName="java.io.OutputStreamWriter";
                    this->name="java.io.OutputStreamWriter";
                    this->simpleName="OutputStreamWriter";
                }

                JClass* getSuperclass(){
                    return JWriter::getClazz();
                }
        };

        static JClass* clazz;

        JClass* JOutputStreamWriter::getClazz(){
            if (clazz==NULL){
                clazz=new JOutputStreamWriterClass();
            }
            return clazz;
        }

        JOutputStreamWriter::JOutputStreamWriter(JClass* _class,JOutputStream* out):JWriter(_class){
            this->out=out;
        }

        JOutputStreamWriter::JOutputStreamWriter(JOutputStream* out):JWriter(getClazz()){
            this->out=out;
        }

        void JOutputStreamWriter::write(jchar c[],jint offset,jint length){
            jbyte b[length];
            for (jint i=0;i<length;i++){
                b[i]=(jbyte)c[offset+i];//TODO introduce encoding
            }
            out->write(b,0,length);
        }

        void JOutputStreamWriter::flush(){
            out->flush();
        }

        void JOutputStreamWriter::close(){
            out->close();
        }

        JOutputStreamWriter::~JOutputStreamWriter(){
            delete out;
        }
    }
}
