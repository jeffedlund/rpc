#include "JPipedReader.h"
#include "JClass.h"
#include "JIllegalArgumentException.h"
#include "JIOException.h"
#include "JIndexOutOfBoundsException.h"

namespace jcpp{
    namespace io{
        class JPipedReaderClass : public JClass{
            public:
                JPipedReaderClass(){
                    this->canonicalName="java.io.PipedReader";
                    this->name="java.io.PipedReader";
                    this->simpleName="PipedReader";
                }

                JClass* getSuperclass(){
                    return JReader::getClazz();
                }

            JObject* newInstance(){
                return new JPipedReader();
            }
        };

        static JClass* clazz;

        JClass* JPipedReader::getClazz(){
            if (clazz==NULL){
                clazz=new JPipedReaderClass();
            }
            return clazz;
        }

        JPipedReader::JPipedReader(JPipedWriter* src, jint pipeSize):JReader(getClazz()){
            closedByWriter=false;
            closedByReader=false;
            connected=false;
            buffer=NULL;
            length=0;
            in=-1;
            out=0;
            initPipe(pipeSize);
            connect(src);
        }

        JPipedReader::JPipedReader(jint pipeSize):JReader(getClazz()){
            closedByWriter=false;
            closedByReader=false;
            connected=false;
            buffer=NULL;
            length=0;
            in=-1;
            out=0;
            initPipe(pipeSize);
        }

        void JPipedReader::initPipe(jint pipeSize){
            if (pipeSize <= 0) {
                throw new JIllegalArgumentException("Pipe size <= 0");
            }
            buffer = new jchar[pipeSize];
            length=pipeSize;
        }

        void  JPipedReader::connect(JPipedWriter* src){
            src->connect(this);
        }

        void JPipedReader::receive(jint c){
            JObject::lock();
            if (!connected){
                unlock();
                throw new JIOException("Pipe not connected");
            }else if (closedByWriter || closedByReader){
                unlock();
                throw new JIOException("Pipe closed");
            }

            while (in == out) {
                notifyAll();
                wait(1000);
            }
            if (in < 0) {
                in = 0;
                out = 0;
            }
            buffer[in++] = (jchar) c;
            if (in >= length) {
                in = 0;
            }
            unlock();
        }

        void JPipedReader::receive(jchar c[],jint off,jint len){
            JObject::lock();
            while (--len >= 0) {
                receive(c[off++]);
            }
            unlock();
        }

        void JPipedReader::receivedLast(){
            JObject::lock();
            closedByWriter = true;
            notifyAll();
            unlock();
        }

        jint JPipedReader::read(){
            JObject::lock();
            if (!connected) {
                unlock();
                throw new JIOException("Pipe not connected");
            } else if (closedByReader) {
                unlock();
                throw new JIOException("Pipe closed");
            }

            while (in < 0) {
                if (closedByWriter) {
                    unlock();
                    return -1;
                }
                notifyAll();
                wait(1000);
            }
            jint ret = buffer[out++];
            if (out >= length) {
                out = 0;
            }
            if (in == out) {
                in = -1;
            }
            unlock();
            return ret;
        }

        jint JPipedReader::read(jchar cbuf[], jint off, jint len){
            JObject::lock();
            if (!connected) {
                unlock();
                throw new JIOException("Pipe not connected");
            } else if (closedByReader) {
                unlock();
                throw new JIOException("Pipe closed");
            }

            if ((off < 0) || (len < 0) || ((off + len) < 0)) {
                unlock();
                throw new JIndexOutOfBoundsException();
            } else if (len == 0) {
                unlock();
                return 0;
            }

            jint c = read();
            if (c < 0) {
                unlock();
                return -1;
            }
            cbuf[off] =  (jchar)c;
            jint rlen = 1;
            while ((in >= 0) && (--len > 0)) {
                cbuf[off + rlen] = buffer[out++];
                rlen++;
                if (out >= length) {
                    out = 0;
                }
                if (in == out) {
                    in = -1;
                }
            }
            unlock();
            return rlen;
        }

        jbool JPipedReader::ready(){
            JObject::lock();
            if (!connected) {
                unlock();
                throw new JIOException("Pipe not connected");
            } else if (closedByReader) {
                unlock();
                throw new JIOException("Pipe closed");
            }
            if (in < 0) {
                unlock();
                return false;
            } else {
                unlock();
                return true;
            }
        }

        void JPipedReader::close(){
            JObject::lock();
            in = -1;
            closedByReader = true;
            unlock();
        }

        JPipedReader::~JPipedReader(){
            delete[] buffer;
        }
    }
}
