#include "JFilterInputStream.h"
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
        class JFilterInputStreamClass : public JClass{
        public:
            JFilterInputStreamClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.io.FilterInputStream";
                name="java.io.FilterInputStream";
                simpleName="FilterInputStream";
            }

            JClass* getSuperclass(){
                return JInputStream::getClazz();
            }

            JObject* newInstance(){
                throw new JInstantiationException("cannot instantiate object of instance "+getName());
            }
        };

        static JClass* clazz;

        JClass* JFilterInputStream::getClazz(){
            if (clazz==NULL){
                clazz=new JFilterInputStreamClass();
            }
            return clazz;
        }

        JFilterInputStream::JFilterInputStream(JInputStream* in,JClass* _class):JInputStream(_class){
            this->in=in;
        }

        void JFilterInputStream::readFully(jbyte b[], jint off, jint len) {
            in->readFully(b,off,len);
        }

        jint JFilterInputStream::read(jbyte b[], int off, int len) {
            return in->read(b,off,len);
        }

        jlong JFilterInputStream::skip(jlong n){
            return in->skip(n);
        }

        void JFilterInputStream::mark(jint m){
            in->mark(m);
        }

        jint JFilterInputStream::available(){
            return in->available();
        }

        bool JFilterInputStream::waitForReadyRead(int i){
            return in->waitForReadyRead(i);
        }

        jint JFilterInputStream::read(){
            return in->read();
        }

        jint JFilterInputStream::peek(){
            return in->peek();
        }

        void JFilterInputStream::reset(){
            in->reset();
        }

        bool JFilterInputStream::markSupported(){
            return in->markSupported();
        }

        void JFilterInputStream::close(){
            in->close();
        }

        JFilterInputStream::~JFilterInputStream() {
            delete in;
        }
    }
}
