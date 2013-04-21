#include "JFilterReader.h"
#include "JClass.h"

namespace jcpp{
    namespace io{
        class JFilterReaderClass : public JClass{
            public:
                JFilterReaderClass(){
                    this->canonicalName="java.io.FilterReader";
                    this->name="java.io.FilterReader";
                    this->simpleName="FilterReader";
                }

                JClass* getSuperclass(){
                    return JReader::getClazz();
                }
        };

        static JClass* clazz;

        JClass* JFilterReader::getClazz(){
            if (clazz==NULL){
                clazz=new JFilterReaderClass();
            }
            return clazz;
        }

        JFilterReader::JFilterReader(JClass* _class,JReader* in):JReader(_class,in){
            this->in=in;
        }

        jint JFilterReader::read(){
            return in->read();
        }

        jint JFilterReader::read(jchar cbuf[], jint off, jint len){
            return in->read(cbuf,off,len);
        }

        jlong JFilterReader::skip(jlong n){
            return in->skip(n);
        }

        jbool JFilterReader::ready(){
            return in->ready();
        }

        jbool JFilterReader::markSupported(){
            return in->markSupported();
        }

        void  JFilterReader::mark(jint m){
            in->mark(m);
        }

        void  JFilterReader::reset(){
            in->reset();
        }

        void  JFilterReader::close(){
            in->close();
        }

        JFilterReader::~JFilterReader(){
            delete in;
        }
    }
}
