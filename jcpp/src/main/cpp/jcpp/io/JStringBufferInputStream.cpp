#include "JStringBufferInputStream.h"
#include "JClass.h"

namespace jcpp{
    namespace io{
        class JStringBufferInputStreamClass : public JClass{
            public:
                JStringBufferInputStreamClass(){
                    this->canonicalName="java.io.StringBufferInputStream";
                    this->name="java.io.StringBufferInputStream";
                    this->simpleName="StringBufferInputStream";
                }

                JClass* getSuperclass(){
                    return JInputStream::getClazz();
                }
        };

        static JClass* clazz;

        JClass* JStringBufferInputStream::getClazz(){
            if (clazz==NULL){
                clazz=new JStringBufferInputStreamClass();
            }
            return clazz;
        }

        JStringBufferInputStream::JStringBufferInputStream(string s):JInputStream(getClazz()){
            this->buffer=s;
            this->count=s.length();
            this->pos=0;
        }

        jint JStringBufferInputStream::read(){
            lock();
            jint i=(pos < count) ? (buffer.at(pos++) & 0xFF) : -1;
            unlock();
            return i;
        }

        jint JStringBufferInputStream::read(jbyte b[], jint off, jint len){
            lock();
            if (pos >= count) {
                unlock();
                return -1;
            }
            if (pos + len > count) {
                len = count - pos;
            }
            if (len <= 0) {
                unlock();
                return 0;
            }
            string  s = buffer;
            jint cnt = len;
            while (--cnt >= 0) {
                b[off++] = (jbyte)s.at(pos++);
            }
            unlock();
            return len;
        }

        jlong JStringBufferInputStream::skip(jlong n){
            lock();
            if (n < 0) {
                unlock();
                return 0;
            }
            if (n > count - pos) {
                n = count - pos;
            }
            pos += n;
            unlock();
            return n;
        }

        jint JStringBufferInputStream::available(){
            lock();
            jint i=count - pos;
            unlock();
            return i;
        }

        void JStringBufferInputStream::reset(){
            lock();
            pos=0;
            unlock();
        }

        JStringBufferInputStream::~JStringBufferInputStream(){
        }
    }
}
