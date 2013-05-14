#include "JCharArrayReader.h"
#include "JClass.h"
#include "JIOException.h"
#include "JIndexOutOfBoundsException.h"
#include "JSystem.h"

namespace jcpp{
    namespace io{
        class JCharArrayReaderClass : public JClass{
            public:
                JCharArrayReaderClass(){
                    this->canonicalName="java.io.CharArrayReader";
                    this->name="java.io.CharArrayReader";
                    this->simpleName="CharArrayReader";
                }

                JClass* getSuperclass(){
                    return JReader::getClazz();
                }
        };

        static JClass* clazz;

        JClass* JCharArrayReader::getClazz(){
            if (clazz==NULL){
                clazz=new JCharArrayReaderClass();
            }
            return clazz;
        }

        JCharArrayReader::JCharArrayReader(jchar buf[],jint pos,jint length):JReader(getClazz()){
            this->buf = buf;
            this->pos = pos;
            this->count = pos + length;
            this->markedPos = pos;
        }

        void JCharArrayReader::ensureOpen(){
            lock->lock();
            if (buf == NULL){
                lock->unlock();
                throw new JIOException("Stream closed");
            }
        }

        jint JCharArrayReader::read(){
            ensureOpen();
            lock->lock();
            jint i;
            if (pos >= count){
                i=-1;
            }else{
                i=buf[pos++];
            }
            lock->unlock();
            return i;
        }

        jint JCharArrayReader::read(jchar b[], jint off, jint len){
            ensureOpen();
            if ((off < 0) || (len < 0) || ((off + len) < 0)) {
                throw new JIndexOutOfBoundsException();
            } else if (len == 0) {
                return 0;
            }

            lock->lock();
            if (pos >= count) {
                lock->unlock();
                return -1;
            }
            if (pos + len > count) {
                len = count - pos;
            }
            if (len <= 0) {
                lock->unlock();
                return 0;
            }
            JSystem::arraycopy(buf, pos, b, off, len);
            pos += len;
            lock->unlock();
            return len;
        }

        jlong JCharArrayReader::skip(jlong n){
            ensureOpen();
            lock->lock();
            if (pos + n > count) {
                n = count - pos;
            }
            if (n < 0) {
                lock->unlock();
                return 0;
            }
            pos += n;
            lock->unlock();
            return n;
        }

        jbool JCharArrayReader::ready(){
            ensureOpen();
            lock->lock();
            jbool b=(count - pos) > 0;
            lock->unlock();
            return b;
        }

        jbool JCharArrayReader::markSupported(){
            return true;
        }

        void JCharArrayReader::mark(jint){
            ensureOpen();
            lock->lock();
            markedPos = pos;
            lock->unlock();
        }

        void JCharArrayReader::reset(){
            ensureOpen();
            lock->lock();
            pos = markedPos;
            lock->unlock();
        }

        void JCharArrayReader::close(){
            delete[] buf;
            buf=NULL;
        }

        JCharArrayReader::~JCharArrayReader(){
            if (buf!=NULL){
                delete[] buf;
            }
        }
    }
}
