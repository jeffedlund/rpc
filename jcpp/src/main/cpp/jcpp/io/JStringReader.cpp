#include "JStringReader.h"
#include "JClass.h"
#include "JIndexOutOfBoundsException.h"
#include "JSystem.h"
#include "JIllegalArgumentException.h"

namespace jcpp{
    namespace io{
        class JStringReaderClass : public JClass{
            public:
                JStringReaderClass(){
                    this->canonicalName="java.io.StringReader";
                    this->name="java.io.StringReader";
                    this->simpleName="StringReader";
                }

                JClass* getSuperclass(){
                    return JReader::getClazz();
                }
        };

        static JClass* clazz;

        JClass* JStringReader::getClazz(){
            if (clazz==NULL){
                clazz=new JStringReaderClass();
            }
            return clazz;
        }

        JStringReader::JStringReader(JString str):JReader(getClazz()){
            this->str=str;
            this->length=str.length();
            next=0;
            imark=0;
        }

        jint JStringReader::read(){
            lock->lock();
            if (next >= length){
                lock->unlock();
                return -1;
            }
            jint i=(jint)str.charAt(next++);
            lock->unlock();
            return i;
        }

        jint JStringReader::read(jchar cbuf[], jint off, jint len){
            if ((off < 0) || (len < 0) || ((off + len) < 0)) {
                throw new JIndexOutOfBoundsException();
            } else if (len == 0) {
                return 0;
            }
            lock->lock();
            if (next >= length){
                lock->unlock();
                return -1;
            }
            jint n = (length - next < len ? length-next : len);
            JSystem::arraycopy(str,next,cbuf,off,n);
            next += n;
            lock->unlock();
            return n;
        }

        jlong JStringReader::skip(jlong ns){
            lock->lock();
            if (next >= length){
                lock->unlock();
                return 0;
            }
            jlong n = (length - next < ns ? length-next : ns);
            n = (-next > n ? -next : n);
            next += n;
            lock->unlock();
            return n;
        }

        jbool JStringReader::ready(){
            return true;
        }

        jbool JStringReader::markSupported(){
            return true;
        }

        void  JStringReader::mark(jint m){
            if (m < 0){
                throw new JIllegalArgumentException("Read-ahead limit < 0");
            }
            lock->lock();
            imark = next;
            lock->unlock();
        }

        void JStringReader::reset(){
            lock->lock();
            next = imark;
            lock->unlock();
        }

        void JStringReader::close(){
            str="";
        }

        JStringReader::~JStringReader(){
        }
    }
}
