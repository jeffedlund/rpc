#include "JOutputStream.h"
#include "JIndexOutOfBoundsException.h"
#include "JNullPointerException.h"
#include "Collections.h"
#include "JInstantiationException.h"
using namespace jcpp::util;

namespace jcpp{
    namespace io{
        class JOutputStreamClass : public JClass{
        public:
            JOutputStreamClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.io.OutputStream";
                name="java.io.OutputStream";
                simpleName="OutputStream";
            }

            JClass* getSuperclass(){
                return JObject::getClazz();
            }
        };

        static JClass* clazz;

        JClass* JOutputStream::getClazz(){
            if (clazz==NULL){
                clazz=new JOutputStreamClass();
            }
            return clazz;
        }

        JOutputStream::JOutputStream():JObject(getClazz()){
        }

        JOutputStream::JOutputStream(JClass* _class):JObject(_class){
        }

        void JOutputStream::write(jbyte b[], int off, int len){
            if (b == 0) {
                throw new JNullPointerException();
            } else {
                jint length = len;
                if ((off < 0) || (off > length) || (len < 0) || ((off + len) > length) || ((off + len) < 0)) {
                    throw new JIndexOutOfBoundsException();
                } else if (len == 0) {
                    return;
                }
                for (int i = 0 ; i < len ; i++) {
                    write(b[off + i]);
                }
            }
        }

        JOutputStream::~JOutputStream(){
        }
    }
}
