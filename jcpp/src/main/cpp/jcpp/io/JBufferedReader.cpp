#include "JBufferedReader.h"
#include "JClass.h"
#include "JIOException.h"
#include "JSystem.h"
#include "JIndexOutOfBoundsException.h"
#include "JStringBuffer.h"

namespace jcpp{
    namespace io{
        class JBufferedReaderClass : public JClass{
            public:
                JBufferedReaderClass(){
                    this->canonicalName="java.io.BufferedReader";
                    this->name="java.io.BufferedReader";
                    this->simpleName="BufferedReader";
                }

                JClass* getSuperclass(){
                    return JReader::getClazz();
                }
        };

        static JClass* clazz;

        JClass* JBufferedReader::getClazz(){
            if (clazz==NULL){
                clazz=new JBufferedReaderClass();
            }
            return clazz;
        }

        static jint INVALIDATED = -2;
        static jint UNMARKED = -1;

        JBufferedReader::JBufferedReader(JClass* _class,JReader* in,jint sz):JReader(_class,in){
            this->in=in;
            cb = new jchar[sz];
            length=sz;
            nextChar = 0;
            nChars = 0;
            markedChar = UNMARKED;
            readAheadLimit=0;
            skipLF=false;
            markedSkipLF=false;
        }

        JBufferedReader::JBufferedReader(JReader* in,jint sz):JReader(getClazz(),in){
            this->in=in;
            cb = new jchar[sz];
            length=sz;
            nextChar = 0;
            nChars = 0;
            markedChar = UNMARKED;
            readAheadLimit=0;
            skipLF=false;
            markedSkipLF=false;
        }

        void JBufferedReader::ensureOpen(){
            if (in == NULL){
                throw new JIOException("Stream closed");
            }
        }

        void JBufferedReader::fill(){
            jint dst;
            if (markedChar <= UNMARKED) {
                dst = 0;
            } else {
                jint delta = nextChar - markedChar;
                if (delta >= readAheadLimit) {
                    markedChar = INVALIDATED;
                    readAheadLimit = 0;
                    dst = 0;
                } else {
                    if (readAheadLimit <= length) {
                        JSystem::arraycopy(cb, markedChar, cb, 0, delta);
                        markedChar = 0;
                        dst = delta;
                    } else {
                        jchar* ncb = new jchar[readAheadLimit];
                        length=readAheadLimit;
                        JSystem::arraycopy(cb, markedChar, ncb, 0, delta);
                        if (cb!=NULL){
                            delete[] cb;
                        }
                        cb = ncb;
                        markedChar = 0;
                        dst = delta;
                    }
                    nextChar = nChars = delta;
                }
            }
            jint n;
            do {
                n = in->read(cb, dst, length - dst);
            } while (n == 0);
            if (n > 0) {
                nChars = dst + n;
                nextChar = dst;
            }
        }

        jint JBufferedReader::read(){
            ensureOpen();
            lock->lock();
            for (;;) {
                if (nextChar >= nChars) {
                    fill();
                    if (nextChar >= nChars){
                        lock->unlock();
                        return -1;
                    }
                }
                if (skipLF) {
                    skipLF = false;
                    if (cb[nextChar] == '\n') {
                        nextChar++;
                        continue;
                    }
                }
                lock->unlock();
                return cb[nextChar++];
            }
        }

        jint JBufferedReader::read1(jchar cbuf[], jint off,jint len){
            if (nextChar >= nChars) {
                if (len >= length && markedChar <= UNMARKED && !skipLF) {
                    return in->read(cbuf, off, len);
                }
                fill();
            }
            if (nextChar >= nChars){
                return -1;
            }
            if (skipLF) {
                skipLF = false;
                if (cb[nextChar] == '\n') {
                    nextChar++;
                    if (nextChar >= nChars){
                        fill();
                    }
                    if (nextChar >= nChars){
                        return -1;
                    }
                }
            }
            jint n = (len < nChars - nextChar ? len : nChars - nextChar);
            JSystem::arraycopy(cb, nextChar, cbuf, off, n);
            nextChar += n;
            return n;
        }

        jint JBufferedReader::read(jchar cbuf[], jint off,jint len){
            ensureOpen();
            if ((off < 0) || (len < 0) || ((off + len) < 0)) {
                throw new JIndexOutOfBoundsException();
            } else if (len == 0) {
                return 0;
            }

            lock->lock();
            jint n = read1(cbuf, off, len);
            if (n <= 0){
                lock->unlock();
                return n;
            }
            while ((n < len) && in->ready()) {
                jint n1 = read1(cbuf, off + n, len - n);
                if (n1 <= 0){
                    break;
                }
                n += n1;
            }
            lock->unlock();
            return n;
        }

        JString JBufferedReader::readLine(jbool ignoreLF){
            JStringBuffer* s = NULL;
            jint startChar=0;
            ensureOpen();

            lock->lock();
            jbool omitLF = ignoreLF || skipLF;

            for (;;) {
                if (nextChar >= nChars){
                    fill();
                }
                if (nextChar >= nChars) {
                    if (s != NULL && s->length() > 0){
                        lock->unlock();
                        return s->toString();
                    }else{
                        lock->unlock();
                        return JString("");//TODO should be NULL;
                    }
                }
                jbool eol = false;
                jchar c = 0;
                jint i;

                if (omitLF && (cb[nextChar] == '\n')){
                    nextChar++;
                }
                skipLF = false;
                omitLF = false;

                for (i = nextChar; i < nChars; i++) {
                    c = cb[i];
                    if ((c == '\n') || (c == '\r')) {
                        eol = true;
                        break;
                    }
                }

                startChar = nextChar;
                nextChar = i;

                if (eol) {
                    JString str;
                    if (s == NULL) {
                        str=JString(cb,startChar,i-startChar);
                    } else {
                        s->append(cb, startChar, i - startChar);
                        str = s->toString();
                    }
                    nextChar++;
                    if (c == '\r') {
                        skipLF = true;
                    }
                    lock->unlock();
                    return str;
                }

                if (s == NULL){
                     s = new JStringBuffer();
                }
                s->append(cb, startChar, i - startChar);
             }
        }

        JString JBufferedReader::readLine(){
            return readLine(false);
        }

        jlong JBufferedReader::skip(jlong n){
            ensureOpen();
            lock->lock();
            jlong r = n;
            while (r > 0) {
                if (nextChar >= nChars){
                    fill();
                }
                if (nextChar >= nChars){
                    break;
                }
                if (skipLF) {
                    skipLF = false;
                    if (cb[nextChar] == '\n') {
                        nextChar++;
                    }
                }
                jlong d = nChars - nextChar;
                if (r <= d) {
                    nextChar += r;
                    r = 0;
                    break;
                }else {
                    r -= d;
                    nextChar = nChars;
                }
            }
            lock->unlock();
            return n - r;
        }

        jbool JBufferedReader::ready(){
            ensureOpen();
            lock->lock();
            if (skipLF) {
                if (nextChar >= nChars && in->ready()) {
                    fill();
                }
                if (nextChar < nChars) {
                    if (cb[nextChar] == '\n'){
                        nextChar++;
                    }
                    skipLF = false;
                }
            }
            jbool b=(nextChar < nChars) || in->ready();
            lock->unlock();
            return b;
        }

        jbool JBufferedReader::markSupported(){
            return true;
        }

        void  JBufferedReader::mark(jint m){
            ensureOpen();
            lock->lock();
            this->readAheadLimit = m;
            markedChar = nextChar;
            markedSkipLF = skipLF;
            lock->unlock();
        }

        void JBufferedReader::reset(){
            ensureOpen();
            lock->lock();
            if (markedChar < 0){
                lock->unlock();
                throw new JIOException((markedChar == INVALIDATED) ? "Mark invalid" : "Stream not marked");
            }
            nextChar = markedChar;
            skipLF = markedSkipLF;
            lock->unlock();
        }

        void JBufferedReader::close(){
            lock->lock();
            if (in == NULL){
                lock->unlock();
                return;
            }
            in->close();
            in = NULL;
            cb = NULL;
            lock->unlock();
        }

        JBufferedReader::~JBufferedReader(){
            if (cb!=NULL){
                delete[] cb;
            }
            delete in;
        }
    }
}
