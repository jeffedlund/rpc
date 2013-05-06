#include "JSequenceInputStream.h"
#include "JClass.h"

namespace jcpp{
    namespace io{
        class JSequenceInputStreamClass : public JClass{
            public:
                JSequenceInputStreamClass(){
                    this->canonicalName="java.io.SequenceInputStream";
                    this->name="java.io.SequenceInputStream";
                    this->simpleName="SequenceInputStream";
                }

                JClass* getSuperclass(){
                    return JInputStream::getClazz();
                }
        };

        static JClass* clazz;

        JClass* JSequenceInputStream::getClazz(){
            if (clazz==NULL){
                clazz=new JSequenceInputStreamClass();
            }
            return clazz;
        }

        JSequenceInputStream::JSequenceInputStream(JEnumeration* e):JInputStream(getClazz()){
            this->e=e;
            nextStream();
        }

        JSequenceInputStream::JSequenceInputStream(JInputStream* s1,JInputStream* s2){
            vec=new JVector();
            vec->addElement(s1);
            vec->addElement(s2);
            e=vec->elements();
            nextStream();
        }

        void JSequenceInputStream::nextStream(){
            if (in != NULL) {
                in->close();
            }
            if (e->hasMoreElements()) {
                in = (JInputStream*) e->nextElement();
                if (in == NULL){
                    throw new JNullPointerException();
                }
            }else{
                in = NULL;
            }
        }

        void  JSequenceInputStream::close(){
            do {
                nextStream();
            } while (in != NULL);
        }

        jint JSequenceInputStream::read(jbyte b[], jint off, jint len){
            if (in == NULL) {
                return -1;
            } else if (b == NULL) {
                throw new JNullPointerException();
            } else if (off < 0 || len < 0 ) {
                throw new JIndexOutOfBoundsException();
            } else if (len == 0) {
                return 0;
            }
            jint n = in->read(b, off, len);
            if (n <= 0) {
                nextStream();
                return read(b, off, len);
            }
            return n;
        }

        jint JSequenceInputStream::read(){
            if (in == NULL) {
                return -1;
            }
            jint c = in->read();
            if (c == -1) {
                nextStream();
                return read();
            }
            return c;
        }

        jint JSequenceInputStream::available(){
            if(in == NULL) {
                return 0;
            }
            return in->available();
        }

        JSequenceInputStream::~JSequenceInputStream(){
            if (vec!=NULL){
                delete vec;//TODO delete JVector deletes its content? do we want that?
            }
            delete this->e;
        }
    }
}
