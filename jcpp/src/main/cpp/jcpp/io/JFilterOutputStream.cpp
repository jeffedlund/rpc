#include "JFilterOutputStream.h"
#include "JIndexOutOfBoundsException.h"
#include "JNullPointerException.h"
#include "Collections.h"
#include "JInstantiationException.h"
#include "JClassLoader.h"
using namespace jcpp::util;

namespace jcpp{
    namespace io{
        class JFilterOutputStreamClass : public JClass{
        public:
            JFilterOutputStreamClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.io.FilterOutputStream";
                name="java.io.FilterOutputStream";
                simpleName="FilterOutputStream";
            }

            JClass* getSuperclass(){
                return JOutputStream::getClazz();
            }
        };

        static JClass* clazz;

        JClass* JFilterOutputStream::getClazz(){
            if (clazz==NULL){
                clazz=new JFilterOutputStreamClass();
            }
            return clazz;
        }

        JFilterOutputStream::JFilterOutputStream(JOutputStream* out,JClass* _class):JOutputStream(_class){
            this->out=out;
        }

        void JFilterOutputStream::write(jbyte b[], jint off, jint len){
            for (jint i=0;i<len;i++){
                out->write(b[off+i]);
            }
        }

        void JFilterOutputStream::write(jint b){
            out->write(b);
        }

        void JFilterOutputStream::flush(){
            out->flush();
        }

        void JFilterOutputStream::close(){
            out->close();
        }

        JFilterOutputStream::~JFilterOutputStream(){
            delete out;
        }
    }
}

