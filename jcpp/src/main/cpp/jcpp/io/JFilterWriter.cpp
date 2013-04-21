#include "JFilterWriter.h"
#include "JClass.h"

namespace jcpp{
    namespace io{
        class JFilterWriterClass : public JClass{
            public:
                JFilterWriterClass(){
                    this->canonicalName="java.io.FilterWriter";
                    this->name="java.io.FilterWriter";
                    this->simpleName="FilterWriter";
                }

                JClass* getSuperclass(){
                    return JWriter::getClazz();
                }
        };

        static JClass* clazz;

        JClass* JFilterWriter::getClazz(){
            if (clazz==NULL){
                clazz=new JFilterWriterClass();
            }
            return clazz;
        }

        JFilterWriter::JFilterWriter(JClass* _class,JWriter* out):JWriter(_class,out){
            this->out=out;
        }

        void JFilterWriter::write(jint c){
            out->write(c);
        }

        void  JFilterWriter::write(jchar cbuf[], jint off, jint len){
            out->write(cbuf,off,len);
        }

        void  JFilterWriter::write(JString* str, jint off, jint len){
            out->write(str,off,len);
        }

        void  JFilterWriter::flush(){
            out->flush();
        }

        void  JFilterWriter::close(){
            out->close();
        }

        JFilterWriter::~JFilterWriter(){
            delete out;
        }
    }
}
