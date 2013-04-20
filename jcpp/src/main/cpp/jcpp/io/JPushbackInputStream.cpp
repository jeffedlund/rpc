#include "JPushbackInputStream.h"
#include "JClass.h"
#include "JIllegalArgumentException.h"
#include "JIOException.h"
#include "JNullPointerException.h"
#include "JIndexOutOfBoundsException.h"
#include "JSystem.h"
#include "JInteger.h"

namespace jcpp{
    namespace io{
        class JPushbackInputStreamClass : public JClass{
            public:
                JPushbackInputStreamClass(){
                    this->canonicalName="java.io.PushbackInputStream";
                    this->name="java.io.PushbackInputStream";
                    this->simpleName="PushbackInputStream";
                }

                JClass* getSuperclass(){
                    return JFilterInputStream::getClazz();
                }
        };

        static JClass* clazz;

        JClass* JPushbackInputStream::getClazz(){
            if (clazz==NULL){
                clazz=new JPushbackInputStreamClass();
            }
            return clazz;
        }

        JPushbackInputStream::JPushbackInputStream(JInputStream* in,jint size):JFilterInputStream(in,getClazz()){
            if (size <= 0) {
                throw new JIllegalArgumentException("size <= 0");
            }
            this->buf = new jbyte[size];
            this->length=size;
            this->pos = size;
        }

        void JPushbackInputStream::ensureOpen(){
            if (in == NULL){
                throw new JIOException("Stream closed");
            }
        }

        jint JPushbackInputStream::read(){
            ensureOpen();
            if (pos < length) {
                return buf[pos++] & 0xff;
            }
            return JFilterInputStream::read();
        }

        jint JPushbackInputStream::read(jbyte b[], jint off, jint len){
            ensureOpen();
            if (b == NULL) {
                throw new JNullPointerException();
            } else if (off < 0 || len < 0) {
                throw new JIndexOutOfBoundsException();
            } else if (len == 0) {
                return 0;
            }

            jint avail = length - pos;
            if (avail > 0) {
                if (len < avail) {
                    avail = len;
                }
                JSystem::arraycopy(buf, pos, b, off, avail);
                pos += avail;
                off += avail;
                len -= avail;
            }
            if (len > 0) {
                len = JFilterInputStream::read(b, off, len);
                if (len == -1) {
                    return avail == 0 ? -1 : avail;
                }
                return avail + len;
            }
            return avail;
        }

        void  JPushbackInputStream::unread(jint b){
            ensureOpen();
            if (pos == 0) {
                throw new JIOException("Push back buffer is full");
            }
            buf[--pos] = (jbyte)b;
        }

        void  JPushbackInputStream::unread(jbyte b[],jint off,jint len){
            ensureOpen();
            if (len > pos) {
                throw new JIOException("Push back buffer is full");
            }
            pos -= len;
            JSystem::arraycopy(b, off, buf, pos, len);
        }

        jint JPushbackInputStream::available(){
            ensureOpen();
            jint n = length - pos;
            jint avail = JFilterInputStream::available();
            return n > (JInteger::MAX_VALUE - avail) ? JInteger::MAX_VALUE : n + avail;
        }

        jlong JPushbackInputStream::skip(jlong n){
            ensureOpen();
            if (n <= 0) {
                return 0;
            }
            jlong pskip = length - pos;
            if (pskip > 0) {
                if (n < pskip) {
                    pskip = n;
                }
                pos += pskip;
                n -= pskip;
            }
            if (n > 0) {
                pskip += JFilterInputStream::skip(n);
            }
            return pskip;
        }

        jbool JPushbackInputStream::markSupported(){
            return false;
        }

        void  JPushbackInputStream::mark(jint){
        }

        void  JPushbackInputStream::reset(){
            throw new JIOException("mark/reset not supported");
        }

        void  JPushbackInputStream::close(){
            lock();
            if (in == NULL){
                unlock();
                return;
            }
            in->close();
            in = NULL;
            buf = NULL;
            unlock();
        }

        JPushbackInputStream::~JPushbackInputStream(){
            delete[] buf;
        }
    }
}
