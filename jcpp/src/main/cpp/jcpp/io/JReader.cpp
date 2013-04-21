#include "JReader.h"
#include "JClass.h"
#include "JIllegalArgumentException.h"
#include "JIOException.h"

namespace jcpp{
    namespace io{
        class JReaderClass : public JClass{
            public:
                JReaderClass(){
                    this->canonicalName="java.io.Reader";
                    this->name="java.io.Reader";
                    this->simpleName="Reader";
                    addInterface(JReadable::getClazz());
                    addInterface(JCloseable::getClazz());
                }

                JClass* getSuperclass(){
                    return JObject::getClazz();
                }
        };

        static JClass* clazz;

        JClass* JReader::getClazz(){
            if (clazz==NULL){
                clazz=new JReaderClass();
            }
            return clazz;
        }

        JReader::JReader(JClass* _class):JObject(_class){
            lock=this;
            skipBuffer=NULL;
            length=0;
        }

        JReader::JReader(JClass* _class,JObject* lock):JObject(_class){
            this->lock=lock;
            skipBuffer=NULL;
            length=0;
        }

        jint JReader::read(){
            jchar* cb = new jchar[1];
            jint r;
            if (read(cb, 0, 1) == -1){
                r=-1;
            }else{
                r=cb[0];
            }
            delete[] cb;
            return r;
        }

        jlong JReader::skip(jlong n){
            if (n < 0){
                throw new JIllegalArgumentException("skip value is negative");
            }
            jint nn = (n < 8192 ? n : 8192);
            lock->lock();
            if ((skipBuffer == NULL) || (length < nn)){
                if (skipBuffer!=NULL){
                    delete[] skipBuffer;
                }
                skipBuffer = new jchar[nn];
                length=nn;
            }
            jlong r = n;
            while (r > 0) {
                jint nc = read(skipBuffer, 0, (r < nn ? r : nn));
                if (nc == -1){
                    break;
                }
                r -= nc;
            }
            lock->unlock();
            return n - r;
        }

        jbool JReader::ready(){
            return false;
        }

        jbool JReader::markSupported(){
            return false;
        }

        void  JReader::mark(jint){
            throw new JIOException("mark() not supported");
        }

        void JReader::reset(){
            throw new JIOException("reset() not supported");
        }

        JReader::~JReader(){
            if (lock!=this){
                delete lock;
            }
            if (skipBuffer!=NULL){
                delete[] skipBuffer;
            }
        }
    }
}
