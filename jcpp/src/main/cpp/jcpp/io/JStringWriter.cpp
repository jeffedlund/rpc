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
                    return NULL;//TODO new JStringWriter();
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
        }

        JStringWriter::~JStringWriter(){
        }
    }
}
