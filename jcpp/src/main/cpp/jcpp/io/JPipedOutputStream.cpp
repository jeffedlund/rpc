#include "JPipedOutputStream.h"
#include "JClass.h"
#include "JNullPointerException.h"
#include "JIOException.h"
#include "JIndexOutOfBoundsException.h"

namespace jcpp{
    namespace io{
        class JPipedOutputStreamClass : public JClass{
            public:
                JPipedOutputStreamClass(){
                    this->canonicalName="java.io.PipedOutputStream";
                    this->name="java.io.PipedOutputStream";
                    this->simpleName="PipedOutputStream";
                }

                JClass* getSuperclass(){
                    return JOutputStream::getClazz();
                }

                JObject* newInstance(){
                    return new JPipedOutputStream();
                }
        };

        static JClass* clazz;

        JClass* JPipedOutputStream::getClazz(){
            if (clazz==NULL){
                clazz=new JPipedOutputStreamClass();
            }
            return clazz;
        }

        JPipedOutputStream::JPipedOutputStream(JPipedInputStream* sink):JOutputStream(getClazz()){
            this->sink=sink;
        }

        JPipedOutputStream::JPipedOutputStream():JOutputStream(getClazz()){
            this->sink=NULL;
        }

        void JPipedOutputStream::connect(JPipedInputStream* sink){
            if (sink == NULL) {
                throw new JNullPointerException();
            } else if (sink != NULL || sink->connected) {
                throw new JIOException("Already connected");
            }
            lock();
            this->sink = sink;
            this->sink->in = -1;
            this->sink->out = 0;
            this->sink->connected = true;
            unlock();
        }

        void JPipedOutputStream::write(jint b){
            if (sink == NULL) {
                throw new JIOException("Pipe not connected");
            }
            sink->receive(b);
        }

        void JPipedOutputStream::write(jbyte b[], jint off, jint len){
            if (sink == NULL) {
                throw new JIOException("Pipe not connected");
            } else if (b == NULL) {
                throw new JNullPointerException();
            } else if ((off < 0) || (len < 0)) {
                throw new JIndexOutOfBoundsException();
            } else if (len == 0) {
                return;
            }
            sink->receive(b, off, len);
        }

        void JPipedOutputStream::flush(){
            lock();
            if (sink != NULL) {
                sink->lock();
                sink->notifyAll();
                sink->unlock();
            }
            unlock();
        }

        void JPipedOutputStream::close(){
            if (sink != NULL) {
                sink->receivedLast();
            }
        }

        JPipedOutputStream::~JPipedOutputStream(){
        }
    }
}
