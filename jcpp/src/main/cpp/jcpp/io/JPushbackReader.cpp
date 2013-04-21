#include "JPushbackReader.h"
#include "JClass.h"
#include "JIllegalArgumentException.h"
#include "JIOException.h"
#include "JIndexOutOfBoundsException.h"
#include "JSystem.h"

namespace jcpp{
    namespace io{
        class JPushbackReaderClass : public JClass{
            public:
                JPushbackReaderClass(){
                    this->canonicalName="java.io.PushbackReader";
                    this->name="java.io.PushbackReader";
                    this->simpleName="PushbackReader";
                }

                JClass* getSuperclass(){
                    return JFilterReader::getClazz();
                }
        };

        static JClass* clazz;

        JClass* JPushbackReader::getClazz(){
            if (clazz==NULL){
                clazz=new JPushbackReaderClass();
            }
            return clazz;
        }

        JPushbackReader::JPushbackReader(JReader* in,jint size):JFilterReader(getClazz(),in){
            if (size <= 0) {
                throw new JIllegalArgumentException("size <= 0");
            }
            this->buf = new jchar[size];
            this->pos = size;
            this->length=size;
        }

        void JPushbackReader::ensureOpen(){
            if (buf == NULL){
                throw new JIOException("Stream closed");
            }
        }

        jint JPushbackReader::read(){
            ensureOpen();
            lock->lock();
            jint i;
            if (pos < length){
                i=buf[pos++];
            }else{
                i=JReader::read();
            }
            lock->unlock();
            return i;
        }

        jint JPushbackReader::read(jchar cbuf[], jint off, jint len){
            ensureOpen();
            if (len <= 0) {
                if (len < 0) {
                    throw new JIndexOutOfBoundsException();
                } else if ((off < 0)) {
                    throw new JIndexOutOfBoundsException();
                }
                return 0;
            }
            lock->lock();
            jint avail = length - pos;
            if (avail > 0) {
                if (len < avail){
                    avail = len;
                }
                JSystem::arraycopy(buf, pos, cbuf, off, avail);
                pos += avail;
                off += avail;
                len -= avail;
            }
            if (len > 0) {
                len = JFilterReader::read(cbuf, off, len);
                if (len == -1) {
                    lock->unlock();
                    return (avail == 0) ? -1 : avail;
                }
                lock->unlock();
                return avail + len;
            }
            lock->unlock();
            return avail;
        }

        void JPushbackReader::unread(jint c){
            ensureOpen();
            lock->lock();
            if (pos == 0){
                lock->unlock();
                throw new JIOException("Pushback buffer overflow");
            }
            buf[--pos] = (jchar) c;
            lock->unlock();
        }

        void  JPushbackReader::unread(jchar cbuf[], jint off, jint len){
            ensureOpen();
            lock->lock();
            if (len > pos){
                lock->unlock();
                throw new JIOException("Pushback buffer overflow");
            }
            pos -= len;
            JSystem::arraycopy(cbuf, off, buf, pos, len);
            lock->unlock();
        }

        jbool JPushbackReader::ready(){
            ensureOpen();
            lock->lock();
            jbool b=(pos < length) || JReader::ready();
            lock->unlock();
            return b;
        }

        void  JPushbackReader::mark(jint){
            throw new JIOException("mark/reset not supported");
        }

        void  JPushbackReader::reset(){
            throw new JIOException("mark/reset not supported");
        }

        jbool JPushbackReader::markSupported(){
            return false;
        }

        void  JPushbackReader::close(){
            JFilterReader::close();
            if (buf!=NULL){
                delete[] buf;
            }
            buf=NULL;
        }

        jlong JPushbackReader::skip(jlong n){
            ensureOpen();
            lock->lock();
            jint avail = length - pos;
            if (avail > 0) {
                if (n <= avail) {
                    pos += n;
                    lock->unlock();
                    return n;
                } else {
                    pos = length;
                    n -= avail;
                }
            }
            jlong l=avail + JReader::skip(n);
            lock->unlock();
            return l;
        }

        JPushbackReader::~JPushbackReader(){
            if (buf!=NULL){
                delete[] buf;
            }
        }
    }
}
