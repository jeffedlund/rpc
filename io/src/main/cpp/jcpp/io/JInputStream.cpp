#include "JInputStream.h"
#include "Object.h"
#include "JNullPointerException.h"
#include "JIndexOutOfBoundsException.h"
#include "Collections.h"
#include "JIOException.h"
#include "JInstantiationException.h"

namespace jcpp{
    namespace io{
        class JInputStreamClass : public JClass{
        public:
            JInputStreamClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.io.InputStream";
                name="java.io.InputStream";
                simpleName="InputStream";
            }

            JClass* getSuperclass(){
                return JObject::getClazz();
            }

            JObject* newInstance(){
                throw new JInstantiationException("cannot instantiate object of instance "+getName());
            }
        };

        static JClass* clazz;

        JClass* JInputStream::getClazz(){
            if (clazz==NULL){
                clazz=new JInputStreamClass();
            }
            return clazz;
        }

        JInputStream::JInputStream():JObject(getClazz()){
        }

        JInputStream::JInputStream(JClass* _class):JObject(_class){
        }

        jint JInputStream::read(jbyte b[], int off, int len) {
            if (b == NULL) {
                throw new JNullPointerException();
            } /*TODO : look for all arrayLength call cause it seems bugged in some case
                else if (off < 0 || len < 0 || len > arrayLength(b) - off) {
                throw new JIndexOutOfBoundsException();
            } */else if (len == 0) {
                return 0;
            }

            jbyte c = read();
            if (c == -1) {
                return -1;
            }
            b[off] = c;

            int i = 1;
            try {
                for (; i < len ; i++) {
                    c = read();
                    if (c == -1) {
                        break;
                    }
                    b[off + i] = (jbyte)c;
                }
            } catch (JIOException* ee) {
            }
            return i;
        }

        JInputStream::~JInputStream() {
        }
    }
}
