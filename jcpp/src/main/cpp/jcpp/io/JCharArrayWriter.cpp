#include "JCharArrayWriter.h"
#include "JClass.h"
#include "JSystem.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class JCharArrayWriterClass : public JClass{
            public:
                JCharArrayWriterClass(){
                    this->canonicalName="java.io.CharArrayWriter";
                    this->name="java.io.CharArrayWriter";
                    this->simpleName="CharArrayWriter";
                }

                JClass* getSuperclass(){
                    return JWriter::getClazz();
                }

                JObject* newInstance(){
                    return new JCharArrayWriter();
                }
        };

        static JClass* clazz;

        JClass* JCharArrayWriter::getClazz(){
            if (clazz==NULL){
                clazz=new JCharArrayWriterClass();
            }
            return clazz;
        }

        JCharArrayWriter::JCharArrayWriter():JWriter(getClazz()){
            buf=new vector<jchar>();
        }

        void JCharArrayWriter::write(jint c){
            lock->lock();
            buf->push_back((jchar)c);
            lock->unlock();
        }

        void JCharArrayWriter::write(jchar c[], jint offset, jint len){
            lock->lock();
            JSystem::arraycopy(c,offset,buf,len);
            lock->unlock();
        }

        void JCharArrayWriter::write(JString* str, jint offset, jint len){
            lock->lock();
            JSystem::arraycopy(str,offset,buf,len);
            lock->unlock();
        }

        void JCharArrayWriter::writeTo(JWriter* out){
            lock->lock();
            out->write(buf->data(),0,buf->size());
            lock->unlock();
        }

        JCharArrayWriter* JCharArrayWriter::append(JCharSequence* csq){
            return append(csq,0,csq->length());
        }

        JCharArrayWriter* JCharArrayWriter::append(JCharSequence* csq,jint offset,jint len){
            JCharSequence* tmp=csq->subSequence(offset,len);
            JString s=tmp->toString();
            delete tmp;
            write(&s,0,s.length());
            return this;
        }

        JCharArrayWriter* JCharArrayWriter::append(jchar c){
            write(c);
            return this;
        }

        void JCharArrayWriter::reset(){
            lock->lock();
            buf->clear();
            lock->unlock();
        }

        vector<jchar>* JCharArrayWriter::toCharArray(){
            lock->lock();
            vector<jchar>* v=new vector<jchar>(buf->begin(),buf->end());
            lock->unlock();
            return v;
        }

        jint JCharArrayWriter::size(){
            lock->lock();
            jint i=buf->size();
            lock->unlock();
            return i;
        }

        JString JCharArrayWriter::toString(){
            lock->lock();
            JString s=JString(buf);
            lock->unlock();
            return s;
        }

        void JCharArrayWriter::flush(){
        }

        void JCharArrayWriter::close(){
        }

        JCharArrayWriter::~JCharArrayWriter(){
            delete buf;
        }
    }
}
