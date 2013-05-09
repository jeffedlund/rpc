#include "JFileWriter.h"
#include "JClass.h"
#include "JFileOutputStream.h"

namespace jcpp{
    namespace io{
        class JFileWriterClass : public JClass{
            public:
                JFileWriterClass(){
                    this->canonicalName="java.io.FileWriter";
                    this->name="java.io.FileWriter";
                    this->simpleName="FileWriter";
                }

                JClass* getSuperclass(){
                    return JOutputStreamWriter::getClazz();
                }

        };

        static JClass* clazz;

        JClass* JFileWriter::getClazz(){
            if (clazz==NULL){
                clazz=new JFileWriterClass();
            }
            return clazz;
        }

        JFileWriter::JFileWriter(JString filename,jbool append):JOutputStreamWriter(getClazz(),new JFileOutputStream(filename,append)){
        }

        JFileWriter::JFileWriter(JFile* f,jbool append):JOutputStreamWriter(getClazz(),new JFileOutputStream(f,append)){
        }

        JFileWriter::~JFileWriter(){
        }
    }
}
