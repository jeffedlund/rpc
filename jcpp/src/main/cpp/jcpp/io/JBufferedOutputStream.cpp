#include "JBufferedOutputStream.h"
#include "Object.h"
#include "JNullPointerException.h"
#include "JIndexOutOfBoundsException.h"
#include "Collections.h"
#include "JIOException.h"
#include "JInstantiationException.h"
#include "JEOFException.h"
#include "JClassLoader.h"
using namespace jcpp::util;

namespace jcpp{
    namespace io{
        class JBufferedOutputStreamClass : public JClass{
        public:
            JBufferedOutputStreamClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.io.BufferedOutputStream";
                name="java.io.BufferedOutputStream";
                simpleName="BufferedOutputStream";
            }

            JClass* getSuperclass(){
                return JFilterOutputStream::getClazz();
            }
        };

        static JClass* clazz;

        JClass* JBufferedOutputStream::getClazz(){
            if (clazz==NULL){
                clazz=new JBufferedOutputStreamClass();
            }
            return clazz;
        }

        JBufferedOutputStream::JBufferedOutputStream(JOutputStream* out,jint size):JFilterOutputStream(out,getClazz()){
            count=0;
            buf=new vector<jbyte>();
            length=size;
        }

        void JBufferedOutputStream::flushBuffer(){
            if (count > 0) {
                out->write(&((*buf)[0]), 0, count);
                count = 0;
            }
        }

        void JBufferedOutputStream::write(jint b){
            if (count >= length) {
                flushBuffer();
            }
            buf->push_back((jbyte)b);
            count++;
        }

        void JBufferedOutputStream::write(jbyte b[], jint off, jint len){
            if (len >= length) {
                flushBuffer();
                out->write(b, off, len);
                return;
            }
            if (len > length - count) {
                flushBuffer();
            }
            arraycopy(b, off, buf, count, len);
            count += len;
        }

        void JBufferedOutputStream::flush(){
            flushBuffer();
            out->flush();
        }

        JBufferedOutputStream::~JBufferedOutputStream() {
            delete buf;
        }
    }
}


