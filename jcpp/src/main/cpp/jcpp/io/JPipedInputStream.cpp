#include "JPipedInputStream.h"
#include "JClass.h"
#include "JIllegalArgumentException.h"
#include "JSystem.h"
#include "JIOException.h"
#include "JNullPointerException.h"
#include "JIndexOutOfBoundsException.h"
#include "JPipedOutputStream.h"

namespace jcpp{
    namespace io{
        class JPipedInputStreamClass : public JClass{
            public:
                JPipedInputStreamClass(){
                    this->canonicalName="java.io.PipedInputStream";
                    this->name="java.io.PipedInputStream";
                    this->simpleName="PipedInputStream";
                }

                JClass* getSuperclass(){
                    return JInputStream::getClazz();
                }

                JObject* newInstance(){
                    return new JPipedInputStream();
                }
        };

        static JClass* clazz;

        JClass* JPipedInputStream::getClazz(){
            if (clazz==NULL){
                clazz=new JPipedInputStreamClass();
            }
            return clazz;
        }

        JPipedInputStream::JPipedInputStream(JPipedOutputStream* src,jint pipeSize):JInputStream(getClazz()){
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

        JPipedInputStream::JPipedInputStream(jint pipeSize):JInputStream(getClazz()){
            closedByWriter=false;
            closedByReader=false;
            connected=false;
            buffer=NULL;
            length=0;
            in=-1;
            out=0;
            initPipe(pipeSize);
        }

        void JPipedInputStream::initPipe(jint pipeSize){
            if (pipeSize <= 0) {
                throw new JIllegalArgumentException("Pipe Size <= 0");
            }
            buffer = new jbyte[pipeSize];
            length=pipeSize;
        }

        void JPipedInputStream::connect(JPipedOutputStream* src){
            src->connect(this);
        }

        jint JPipedInputStream::peek(){
            if (!connected) {//TODO isConnected
                throw new JIOException("Pipe not connected");
            } else if (closedByReader) {
                throw new JIOException("Pipe closed");
            }
            lock();
            while (in < 0) {
                if (closedByWriter) {
                    unlock();
                    return -1;
                }
                notifyAll();
                wait(1000);
            }
            jint ret = buffer[out] & 0xFF;
            unlock();
            return ret;
        }

        void JPipedInputStream::receive(jint b){
            checkStateForReceive();
            lock();
            if (in == out){
                awaitSpace();
            }
            if (in < 0) {
                in = 0;
                out = 0;
            }
            buffer[in++] = (jbyte)(b & 0xFF);
            if (in >= length) {
                in = 0;
            }
            unlock();
        }

        void JPipedInputStream::receive(jbyte b[],jint off,jint len){
            checkStateForReceive();
            lock();
            jint bytesToTransfer = len;
            while (bytesToTransfer > 0) {
                if (in == out){
                    awaitSpace();
                }
                jint nextTransferAmount = 0;
                if (out < in) {
                    nextTransferAmount = length - in;
                } else if (in < out) {
                    if (in == -1) {
                        in = out = 0;
                        nextTransferAmount = length - in;
                    } else {
                        nextTransferAmount = out - in;
                    }
                }
                if (nextTransferAmount > bytesToTransfer){
                    nextTransferAmount = bytesToTransfer;
                }
                assert(nextTransferAmount > 0);
                JSystem::arraycopy(b, off, buffer, in, nextTransferAmount);
                bytesToTransfer -= nextTransferAmount;
                off += nextTransferAmount;
                in += nextTransferAmount;
                if (in >= length) {
                    in = 0;
                }
            }
            unlock();
        }

        void JPipedInputStream::checkStateForReceive(){
            if (!connected) {//TODO isConnected
                throw new JIOException("Pipe not connected");
            } else if (closedByWriter || closedByReader) {//TODO isXXX
                throw new JIOException("Pipe closed");
            }
        }

        void JPipedInputStream::awaitSpace(){
            while (in == out) {
                checkStateForReceive();
                notifyAll();
                wait(1000);
            }
        }

        void JPipedInputStream::receivedLast(){
            lock();
            closedByWriter = true;
            notifyAll();
            unlock();
        }

        jint JPipedInputStream::read(){
            if (!connected) {
                throw new JIOException("Pipe not connected");
            } else if (closedByReader) {
                throw new JIOException("Pipe closed");
            }
            lock();
            while (in < 0) {
                if (closedByWriter) {
                    unlock();
                    return -1;
                }
                notifyAll();
                wait(1000);
            }
            jint ret = buffer[out++] & 0xFF;
            if (out >= length) {
                out = 0;
            }
            if (in == out) {
                in = -1;
            }
            unlock();
            return ret;
        }

        jint JPipedInputStream::read(jbyte b[],jint off,jint len){
            if (b == NULL) {
                throw new JNullPointerException();
            } else if (off < 0 || len < 0) {
                throw new JIndexOutOfBoundsException();
            } else if (len == 0) {
                return 0;
            }
            jint c = read();
            if (c < 0) {
                return -1;
            }
            b[off] = (jbyte) c;
            jint rlen = 1;
            lock();
            while ((in >= 0) && (len > 1)) {
                jint available;
                if (in > out) {
                    available = ((length - out) < (in - out) ? length - out : in-out);
                } else {
                    available = length - out;
                }

                if (available > (len - 1)) {
                    available = len - 1;
                }
                JSystem::arraycopy(buffer, out, b, off + rlen, available);
                out += available;
                rlen += available;
                len -= available;
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

        jint JPipedInputStream::available(){
            lock();
            jint i;
            if(in < 0){
                i=0;
            }else if(in == out){
                i=length;
            }else if (in > out){
                i=in - out;
            }else{
                i=in + length - out;
            }
            unlock();
            return i;
        }

        void JPipedInputStream::close(){
            lock();
            closedByReader = true;
            in = -1;
            unlock();
        }

        JPipedInputStream::~JPipedInputStream(){
            delete[] buffer;
        }
    }
}
