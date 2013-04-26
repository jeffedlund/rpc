#include "JInputStreamReader.h"
#include "JClass.h"

namespace jcpp{
    namespace io{
        class JInputStreamReaderClass : public JClass{
            public:
                JInputStreamReaderClass(){
                    this->canonicalName="java.io.InputStreamReader";
                    this->name="java.io.InputStreamReader";
                    this->simpleName="InputStreamReader";
                }

                JClass* getSuperclass(){
                    return JReader::getClazz();
                }
        };

        static JClass* clazz;

        JClass* JInputStreamReader::getClazz(){
            if (clazz==NULL){
                clazz=new JInputStreamReaderClass();
            }
            return clazz;
        }

        JInputStreamReader::JInputStreamReader(JClass* _class,JInputStream* in):JReader(_class,in){
            this->in=in;
        }

        //TODO review encoding
        JInputStreamReader::JInputStreamReader(JInputStream* in):JReader(getClazz(),in){
            this->in=in;
        }

        jint JInputStreamReader::read(){
            return in->read();
        }

        jint JInputStreamReader::read(jchar[],jint , jint){
            return -1;//TODO
        }

        jbool JInputStreamReader::ready(){
            return false;//TODO
        }

        void JInputStreamReader::close(){
            in->close();
        }

        JInputStreamReader::~JInputStreamReader(){
            delete in;
        }
    }
}
