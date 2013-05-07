#include "JByteArrayInputStream.h"
#include "JClass.h"
#include "JNullPointerException.h"
#include "JIndexOutOfBoundsException.h"
#include "JSystem.h"

namespace jcpp{
    namespace io{
        class JByteArrayInputStreamClass : public JClass{
            public:
                JByteArrayInputStreamClass(){
                    this->canonicalName="java.io.ByteArrayInputStream";
                    this->name="java.io.ByteArrayInputStream";
                    this->simpleName="ByteArrayInputStream";
                }

                JClass* getSuperclass(){
                    return JInputStream::getClazz();
                }
        };

        static JClass* clazz;

        JClass* JByteArrayInputStream::getClazz(){
            if (clazz==NULL){
                clazz=new JByteArrayInputStreamClass();
            }
            return clazz;
        }

        JByteArrayInputStream::JByteArrayInputStream(jbyte buf[],jint offset,jint l):JInputStream(getClazz()){
            this->buf=buf;
            this->pos=offset;
            this->count=l;
            imark=offset;
        }

        JByteArrayInputStream::JByteArrayInputStream(jbyte buf[],jint l):JInputStream(getClazz()){
            this->buf=buf;
            this->pos=0;
            this->count=l;
            imark=0;
        }

        jint JByteArrayInputStream::read(){
            lock();
            jint i=(pos < count) ? (buf[pos++] & 0xff) : -1;
            unlock();
            return i;
        }

        jint JByteArrayInputStream::read(jbyte b[], jint off, jint len){
            if (b == NULL) {
                throw new JNullPointerException();
            } else if (off < 0 || len < 0) {
                throw new JIndexOutOfBoundsException();
            }

            lock();
            if (pos >= count) {
                unlock();
                return -1;
            }

            jint avail = count - pos;
            if (len > avail) {
                len = avail;
            }
            if (len <= 0) {
                return 0;
            }
            JSystem::arraycopy(buf, pos, b, off, len);
            pos += len;
            unlock();
            return len;
        }

        jlong JByteArrayInputStream::skip(jlong n){
            lock();
            jlong k = count - pos;
            if (n < k) {
                k = n < 0 ? 0 : n;
            }
            pos += k;
            unlock();
            return k;
        }

        jint JByteArrayInputStream::available(){
            lock();
            jint i=count - pos;
            unlock();
            return i;
        }

        jbool JByteArrayInputStream::markSupported(){
            return true;
        }

        void JByteArrayInputStream::mark(jint){
            lock();
            imark=pos;
            unlock();
        }

        void JByteArrayInputStream::reset(){
            lock();
            pos=imark;
            unlock();
        }

        void JByteArrayInputStream::close(){
        }

        JByteArrayInputStream::~JByteArrayInputStream(){
            delete[] this->buf;
        }
    }
}
