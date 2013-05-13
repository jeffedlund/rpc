#include "JBufferedWriter.h"
#include "JClass.h"
#include "JIOException.h"
#include "JSystem.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class JBufferedWriterClass : public JClass{
            public:
                JBufferedWriterClass(){
                    this->canonicalName="java.io.BufferedWriter";
                    this->name="java.io.BufferedWriter";
                    this->simpleName="BufferedWriter";
                }

                JClass* getSuperclass(){
                    return JWriter::getClazz();
                }
        };

        static JClass* clazz;

        JClass* JBufferedWriter::getClazz(){
            if (clazz==NULL){
                clazz=new JBufferedWriterClass();
            }
            return clazz;
        }

        JBufferedWriter::JBufferedWriter(JWriter* out,jint size):JWriter(getClazz(),out){
            this->out=out;
            this->cb=new jchar[size];
            this->size=size;
            nChars=size;
            nextChar=0;
            lineSeparator=new JString("/r/n");//TODO fetch from system.property(line.separator)
        }

        void JBufferedWriter::ensureOpen(){
            if (out==NULL){
                throw new JIOException("stream closed");
            }
        }

        void JBufferedWriter::flushBuffer(){
            lock->lock();
            if (out!=NULL){
                if (nextChar != 0){
                    out->write(cb, 0, nextChar);
                    nextChar = 0;
                }
                lock->unlock();
            }else{
                lock->unlock();
                ensureOpen();
            }
        }

        void  JBufferedWriter::write(jint c){
            lock->lock();
            if (out!=NULL){
                if (nextChar >= nChars){
                    flushBuffer();
                }
                cb[nextChar++] = (jchar) c;
                lock->unlock();
            }else{
                lock->unlock();
                ensureOpen();
            }
        }

        void  JBufferedWriter::write(jchar cbuf[], jint off, jint len){
            lock->lock();
            if (out!=NULL){
                if (len > 0) {
                    if (len >= nChars) {
                        flushBuffer();
                        out->write(cbuf, off, len);
                    }else{
                        jint b = off, t = off + len;
                        while (b < t) {
                            jint d = (nChars - nextChar < t - b ? nChars - nextChar : t - b);
                            JSystem::arraycopy(cbuf, b, cb, nextChar, d);
                            b += d;
                            nextChar += d;
                            if (nextChar >= nChars){
                                flushBuffer();
                            }
                        }
                    }
                }
                lock->unlock();
            }else{
                lock->unlock();
                ensureOpen();
            }
        }

        void  JBufferedWriter::write(JString* str, jint off, jint len){
            lock->lock();
            if (out!=NULL){
                if (len > 0) {
                    if (len >= nChars) {
                        flushBuffer();
                        out->write(str, off, len);
                    }else{
                        jint b = off, t = off + len;
                        while (b < t) {
                            jint d = (nChars - nextChar < t - b ? nChars - nextChar : t - b);
                            JSystem::arraycopy(str, b, cb, nextChar, d);
                            b += d;
                            nextChar += d;
                            if (nextChar >= nChars){
                                flushBuffer();
                            }
                        }
                    }
                }
                lock->unlock();
            }else{
                lock->unlock();
                ensureOpen();
            }
        }

        void  JBufferedWriter::newLine(){
            JWriter::write(lineSeparator);
        }

        void  JBufferedWriter::flush(){
            lock->lock();
            flushBuffer();//TOOD bug can throw exception
            lock->unlock();
        }

        void  JBufferedWriter::close(){
            lock->lock();
            if (out!=NULL){
                flushBuffer();
                delete out;
                out=NULL;
            }
            lock->unlock();
        }

        JBufferedWriter::~JBufferedWriter(){
            if (out!=NULL){
                delete out;
            }
            delete[] cb;
        }
    }
}
