#include "JLineNumberReader.h"
#include "JClass.h"
#include "JIllegalArgumentException.h"

namespace jcpp{
    namespace io{
        class JLineNumberReaderClass : public JClass{
            public:
                JLineNumberReaderClass(){
                    this->canonicalName="java.io.LineNumberReader";
                    this->name="java.io.LineNumberReader";
                    this->simpleName="LineNumberReader";
                }

                JClass* getSuperclass(){
                    return JBufferedReader::getClazz();
                }
        };

        static JClass* clazz;

        JClass* JLineNumberReader::getClazz(){
            if (clazz==NULL){
                clazz=new JLineNumberReaderClass();
            }
            return clazz;
        }

        JLineNumberReader::JLineNumberReader(JReader* in,jint sz):JBufferedReader(getClazz(),in,sz){
            lineNumber=0;
            markedLineNumber=0;
            skipLF=false;
            markedSkipLF=false;
            skipBuffer=NULL;
            length=0;
        }

        JLineNumberReader::JLineNumberReader(JReader* in):JBufferedReader(getClazz(),in){
            lineNumber=0;
            markedLineNumber=0;
            skipLF=false;
            markedSkipLF=false;
            skipBuffer=NULL;
            length=0;
        }

        void JLineNumberReader::setLineNumber(jint lineNumber){
            this->lineNumber=lineNumber;
        }

        jint JLineNumberReader::getLineNumber(){
            return lineNumber;
        }

        jint JLineNumberReader::read(){
            lock->lock();
            jint c = JBufferedReader::read();
            if (skipLF) {
                if (c == '\n'){
                    c = JBufferedReader::read();
                }
                skipLF = false;
            }
            switch (c) {
                case '\r':
                    skipLF = true;
                case '\n':
                    lineNumber++;
                    lock->unlock();
                    return '\n';
            }
            lock->unlock();
            return c;
        }

        jint JLineNumberReader::read(jchar cbuf[], jint off, jint len){
            lock->lock();
            jint n = JBufferedReader::read(cbuf, off, len);
            for (jint i = off; i < off + n; i++) {
                jint c = cbuf[i];
                if (skipLF) {
                    skipLF = false;
                    if (c == '\n'){
                        continue;
                    }
                }
                switch (c) {
                    case '\r':
                        skipLF = true;
                    case '\n':
                        lineNumber++;
                        break;
                }
            }
            lock->unlock();
            return n;
        }

        JString* JLineNumberReader::readLine(){
            lock->lock();
            JString* l = JBufferedReader::readLine(skipLF);
            skipLF = false;
            if (l->length()>0){
                lineNumber++;
            }
            lock->unlock();
            return l;
        }

        jlong JLineNumberReader::skip(jlong n){
            if (n < 0){
                throw new JIllegalArgumentException("skip() value is negative");
            }
            jint nn = (n < 8192 ? n : 8192);
            lock->lock();
            if (skipBuffer == NULL || length < nn){
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

        void JLineNumberReader::mark(jint m){
            lock->lock();
            JBufferedReader::mark(m);
            markedLineNumber = lineNumber;
            markedSkipLF = skipLF;
            lock->unlock();
        }

        void JLineNumberReader::reset(){
            lock->lock();
            JBufferedReader::reset();
            lineNumber = markedLineNumber;
            skipLF = markedSkipLF;
            lock->unlock();
        }

        JLineNumberReader::~JLineNumberReader(){
            delete[] skipBuffer;
        }
    }
}
