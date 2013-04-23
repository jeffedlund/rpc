#include "JPipedWriter.h"
#include "JClass.h"
#include "JNullPointerException.h"
#include "JIOException.h"
#include "JIndexOutOfBoundsException.h"
#include "JPipedReader.h"

namespace jcpp{
    namespace io{
        class JPipedWriterClass : public JClass{
            public:
                JPipedWriterClass(){
                    this->canonicalName="java.io.PipedWriter";
                    this->name="java.io.PipedWriter";
                    this->simpleName="PipedWriter";
                }

                JClass* getSuperclass(){
                    return JWriter::getClazz();
                }

                JObject* newInstance(){
                    return new JPipedWriter();
                }
        };

        static JClass* clazz;

        JClass* JPipedWriter::getClazz(){
            if (clazz==NULL){
                clazz=new JPipedWriterClass();
            }
            return clazz;
        }

        JPipedWriter::JPipedWriter(JPipedReader* snk):JWriter(getClazz()){
            closed=false;
            connect(snk);
        }

        JPipedWriter::JPipedWriter():JWriter(getClazz()){
            closed=false;
        }

        void JPipedWriter::connect(JPipedReader* snk){
            JObject::lock();
            if (snk == NULL) {
                unlock();
                throw new JNullPointerException();
            } else if (sink != NULL || snk->connected) {
                unlock();
                throw new JIOException("Already connected");
            } else if (snk->closedByReader || closed) {
                unlock();
                throw new JIOException("Pipe closed");
            }

            this->sink = snk;
            snk->in = -1;
            snk->out = 0;
            snk->connected = true;
            unlock();
        }

        void JPipedWriter::write(jint c){
            if (sink == NULL) {
                throw new JIOException("Pipe not connected");
            }
            sink->receive(c);
        }

        void JPipedWriter::write(jchar cbuf[], jint off, jint len){
            if (sink == NULL) {
                throw new JIOException("Pipe not connected");
            } else if (off | len | (off + len)) {
                throw new JIndexOutOfBoundsException();
            }
            sink->receive(cbuf, off, len);
        }

        void JPipedWriter::flush(){
            JObject::lock();
            if (sink != NULL) {
                if (sink->closedByReader || closed) {
                    unlock();
                    throw new JIOException("Pipe closed");
                }
                ((JObject*)sink)->lock();
                sink->notifyAll();
                sink->unlock();
            }
        }

        void JPipedWriter::close(){
            JObject::lock();
            closed = true;
            if (sink != NULL) {
                sink->receivedLast();
            }
            unlock();
        }

        JPipedWriter::~JPipedWriter(){
            if (sink!=NULL){
                delete sink;
            }
        }
    }
}
