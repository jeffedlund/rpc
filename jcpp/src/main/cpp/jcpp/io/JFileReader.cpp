#include "JFileReader.h"
#include "JClass.h"
#include "JFileInputStream.h"

namespace jcpp{
    namespace io{
        class JFileReaderClass : public JClass{
            public:
                JFileReaderClass(){
                    this->canonicalName="java.io.FileReader";
                    this->name="java.io.FileReader";
                    this->simpleName="FileReader";
                }

                JClass* getSuperclass(){
                    return JInputStreamReader::getClazz();
                }
        };

        static JClass* clazz;

        JClass* JFileReader::getClazz(){
            if (clazz==NULL){
                clazz=new JFileReaderClass();
            }
            return clazz;
        }

        JFileReader::JFileReader(string name):JInputStreamReader(getClazz(),new JFileInputStream(name)){
        }

        JFileReader::JFileReader(JFile* f):JInputStreamReader(getClazz(),new JFileInputStream(f)){
        }

        JFileReader::~JFileReader(){
        }
    }
}
