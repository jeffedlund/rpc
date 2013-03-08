#include "JInputStream.h"
#include "Object.h"
#include "JNullPointerException.h"
#include "JIndexOutOfBoundsException.h"
#include "Collections.h"
#include "JIOException.h"
#include "JInstantiationException.h"
#include "JEOFException.h"
using namespace jcpp::util;

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
            this->skipBuffer=NULL;
        }

        JInputStream::JInputStream(JClass* _class):JObject(_class){
            this->skipBuffer=NULL;
        }

        void JInputStream::readFully(jbyte b[], jint off, jint len) {
            if (len < 0){
                throw new JIndexOutOfBoundsException;
            }
            int n = 0;
            while (n < len) {
                jint count = read(b, off + n, len - n);
                if (count < 0){
                    throw new JEOFException;
                }
                n += count;
            }
        }

        jint JInputStream::read(jbyte b[], int off, int len) {
            if (b == NULL) {
                throw new JNullPointerException();
            }else if (len == 0) {
                return 0;
            }

            for (int i=0;i<len;i++){//better handling
                b[off+i]=read();
            }
            return len;
        }

        jlong JInputStream::skip(jlong n){
            jlong remaining = n;
            int nr;
            if (skipBuffer == NULL){
                skipBuffer = new jbyte[SKIP_BUFFER_SIZE];
            }

            if (n <= 0) {
                return 0;
            }

            while (remaining > 0) {
                nr = read(skipBuffer, 0,(SKIP_BUFFER_SIZE<remaining ? SKIP_BUFFER_SIZE : remaining));
                if (nr < 0) {
                    break;
                }
                remaining -= nr;
            }

            return n - remaining;
        }

        void JInputStream::mark(int){
        }

        void JInputStream::reset(){
        }

        bool JInputStream::markSupported(){
            return false;
        }

        JInputStream::~JInputStream() {
            delete skipBuffer;
        }
    }
}