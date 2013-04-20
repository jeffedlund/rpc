#include "JStringBuffer.h"
#include "JClass.h"
#include "JObjectStreamField.h"
#include "JPrimitiveArray.h"
#include "JPrimitiveChar.h"
#include "JInteger.h"
#include "JBoolean.h"
#include "JObjectInputStream.h"
#include "JObjectOutputStream.h"

namespace jcpp{
    namespace lang{
        class JStringBufferClass : public JClass{
            protected:
                static JObject* staticGetserialPersistentFields(JObject*){
                    return JStringBuffer::getSerialPersistentFields();
                }

                static JObject* invokeWriteObject(JObject* object,vector<JObject*>* args){
                    JStringBuffer* b=(JStringBuffer*)object;
                    b->writeObject((JObjectOutputStream*)args->at(0));
                    return NULL;
                }

                static JObject* invokeReadObject(JObject* object,vector<JObject*>* args){
                    JStringBuffer* b=(JStringBuffer*)object;
                    b->readObject((JObjectInputStream*)args->at(0));
                    return NULL;
                }

            public:
                JStringBufferClass(){
                    this->canonicalName="java.lang.StringBuffer";
                    this->name="java.lang.StringBuffer";
                    this->simpleName="StringBuffer";
                    this->serialVersionUID=3388685877147921107ULL;
                    addInterface(JSerializable::getClazz());
                    addInterface(JCharSequence::getClazz());
                    addField(new JField("serialPersistentFields",JPrimitiveArray::getClazz(JObjectStreamField::getClazz()),this,staticGetserialPersistentFields,NULL));

                    vector<JClass*>* paramType=new vector<JClass*>();
                    paramType->push_back(JObjectInputStream::getClazz());
                    addMethod(new JMethod("readObject",this,JVoid::getClazz(),paramType,invokeReadObject));

                    paramType=new vector<JClass*>;
                    paramType->push_back(JObjectOutputStream::getClazz());
                    addMethod(new JMethod("writeObject",this,JVoid::getClazz(),paramType,invokeWriteObject));
                }

                JClass* getSuperclass(){
                    return JAbstractStringBuilder::getClazz();
                }

                JObject* newInstance(){
                    return new JStringBuffer();
                }
        };

        static JClass* clazz;

        JClass* JStringBuffer::getClazz(){
            if (clazz==NULL){
                clazz=new JStringBufferClass();
            }
            return clazz;
        }

        JStringBuffer::JStringBuffer():JAbstractStringBuilder(getClazz()){
        }

        JStringBuffer::JStringBuffer(JString* str):JAbstractStringBuilder(getClazz()){
            append(str);
        }

        JStringBuffer::JStringBuffer(string str):JAbstractStringBuilder(getClazz()){
            append(str);
        }

        JStringBuffer::JStringBuffer(JCharSequence* cs):JAbstractStringBuilder(getClazz()){
            append(cs);
        }

        jint JStringBuffer::length(){
            lock();
            jint i=JAbstractStringBuilder::length();
            unlock();
            return i;
        }

        jint JStringBuffer::capacity(){
            lock();
            jint i=JAbstractStringBuilder::capacity();
            unlock();
            return i;
        }

        void JStringBuffer::ensureCapacity(jint c){
            lock();
            JAbstractStringBuilder::ensureCapacity(c);
            unlock();
        }

        void JStringBuffer::trimToSize(){
            lock();
            JAbstractStringBuilder::trimToSize();
            unlock();
        }

        void JStringBuffer::setLength(jint l){
            lock();
            JAbstractStringBuilder::setLength(l);
            unlock();
        }

        jchar JStringBuffer::charAt(jint index){
            lock();
            jchar c=JAbstractStringBuilder::charAt(index);
            unlock();
            return c;
        }

        void JStringBuffer::getChars(jint srcBegin,jint srcEnd,jchar dst[],jint dstBegin){
            lock();
            JAbstractStringBuilder::getChars(srcBegin,srcEnd,dst,dstBegin);
            unlock();
        }

        void JStringBuffer::setCharAt(jint index,jchar c){
            lock();
            JAbstractStringBuilder::setCharAt(index,c);
            unlock();
        }

        JStringBuffer* JStringBuffer::append(JObject* o){
            lock();
            JAbstractStringBuilder::append(o);
            unlock();
            return this;
        }

        JStringBuffer* JStringBuffer::append(JString* o){
            lock();
            JAbstractStringBuilder::append(o);
            unlock();
            return this;
        }

        JStringBuffer* JStringBuffer::append(string str){
            lock();
            JAbstractStringBuilder::append(str);
            unlock();
            return this;
        }

        JStringBuffer* JStringBuffer::append(JStringBuffer* sb){
            lock();
            JAbstractStringBuilder::append(sb);
            unlock();
            return this;
        }

        JStringBuffer* JStringBuffer::append(JCharSequence* s){
            lock();
            JAbstractStringBuilder::append(s);
            unlock();
            return this;
        }

        JStringBuffer* JStringBuffer::append(JCharSequence* s,jint start,jint end){
            lock();
            JAbstractStringBuilder::append(s,start,end);
            unlock();
            return this;
        }

        JStringBuffer* JStringBuffer::append(jchar str[],jint offset,jint length){
            lock();
            JAbstractStringBuilder::append(str,offset,length);
            unlock();
            return this;
        }

        JStringBuffer* JStringBuffer::append(jbool b){
            lock();
            JAbstractStringBuilder::append(b);
            unlock();
            return this;
        }

        JStringBuffer* JStringBuffer::append(jchar c){
            lock();
            JAbstractStringBuilder::append(c);
            unlock();
            return this;
        }

        JStringBuffer* JStringBuffer::append(jint i){
            lock();
            JAbstractStringBuilder::append(i);
            unlock();
            return this;
        }

        JStringBuffer* JStringBuffer::append(jlong l){
            lock();
            JAbstractStringBuilder::append(l);
            unlock();
            return this;
        }

        JStringBuffer* JStringBuffer::append(jfloat f){
            lock();
            JAbstractStringBuilder::append(f);
            unlock();
            return this;
        }

        JStringBuffer* JStringBuffer::append(jdouble d){
            lock();
            JAbstractStringBuilder::append(d);
            unlock();
            return this;
        }

        JStringBuffer* JStringBuffer::append(string str,jint offset,jint length){
            lock();
            JAbstractStringBuilder::append(str,offset,length);
            unlock();
            return this;
        }

        JStringBuffer* JStringBuffer::deleteChar(jint start,jint end){
            lock();
            JAbstractStringBuilder::deleteChar(start,end);
            unlock();
            return this;
        }

        JStringBuffer* JStringBuffer::deleteCharAt(jint index){
            lock();
            JAbstractStringBuilder::deleteCharAt(index);
            unlock();
            return this;
        }

        JStringBuffer* JStringBuffer::replace(jint start,jint end,JString* str){
            lock();
            JAbstractStringBuilder::replace(start,end,str);
            unlock();
            return this;
        }

        JString* JStringBuffer::substring(jint start){
            lock();
            JString* str=JAbstractStringBuilder::substring(start);
            unlock();
            return str;
        }

        JCharSequence* JStringBuffer::subSequence(jint start,jint end){
            lock();
            JCharSequence* s=JAbstractStringBuilder::subSequence(start,end);
            unlock();
            return s;
        }

        JString* JStringBuffer::substring(jint start,jint end){
            lock();
            JString* str=JAbstractStringBuilder::substring(start,end);
            unlock();
            return str;
        }

        JStringBuffer* JStringBuffer::insert(jint index,jchar str[],jint offset,jint len){
            lock();
            JAbstractStringBuilder::insert(index,str,offset,len);
            unlock();
            return this;
        }

        JStringBuffer* JStringBuffer::insert(jint offset,JObject* o){
            lock();
            JAbstractStringBuilder::insert(offset,o);
            unlock();
            return this;
        }

        JStringBuffer* JStringBuffer::insert(jint offset,JString* str){
            lock();
            JAbstractStringBuilder::insert(offset,str);
            unlock();
            return this;
        }

        JStringBuffer* JStringBuffer::insert(jint offset,string str){
            lock();
            JAbstractStringBuilder::insert(offset,str);
            unlock();
            return this;
        }

        JStringBuffer* JStringBuffer::insert(jint offset,jchar str[],jint l){
            lock();
            JAbstractStringBuilder::insert(offset,str,l);
            unlock();
            return this;
        }

        JStringBuffer* JStringBuffer::insert(jint offset,JCharSequence* s){
            lock();
            JAbstractStringBuilder::insert(offset,s);
            unlock();
            return this;
        }

        JStringBuffer* JStringBuffer::insert(jint offset,JCharSequence* s,jint start,jint end){
            lock();
            JAbstractStringBuilder::insert(offset,s,start,end);
            unlock();
            return this;
        }

        JStringBuffer* JStringBuffer::insert(jint offset,jbool b){
            lock();
            JAbstractStringBuilder::insert(offset,b);
            unlock();
            return this;
        }

        JStringBuffer* JStringBuffer::insert(jint offset,jchar c){
            lock();
            JAbstractStringBuilder::insert(offset,c);
            unlock();
            return this;
        }

        JStringBuffer* JStringBuffer::insert(jint offset,jint i){
            lock();
            JAbstractStringBuilder::insert(offset,i);
            unlock();
            return this;
        }

        JStringBuffer* JStringBuffer::insert(jint offset,jlong l){
            lock();
            JAbstractStringBuilder::insert(offset,l);
            unlock();
            return this;
        }

        JStringBuffer* JStringBuffer::insert(jint offset,jfloat f){
            lock();
            JAbstractStringBuilder::insert(offset,f);
            unlock();
            return this;
        }

        JStringBuffer* JStringBuffer::insert(jint offset,jdouble d){
            lock();
            JAbstractStringBuilder::insert(offset,d);
            unlock();
            return this;
        }

        jint JStringBuffer::indexOf(JString* str){
            lock();
            jint i=JAbstractStringBuilder::indexOf(str);
            unlock();
            return i;
        }

        jint JStringBuffer::indexOf(JString* str,jint fromIndex){
            lock();
            jint i=JAbstractStringBuilder::indexOf(str,fromIndex);
            unlock();
            return i;
        }

        jint JStringBuffer::lastIndexOf(JString* str){
            lock();
            jint i=JAbstractStringBuilder::lastIndexOf(str);
            unlock();
            return i;
        }

        jint JStringBuffer::lastIndexOf(JString* str,jint fromIndex){
            lock();
            jint i=JAbstractStringBuilder::lastIndexOf(str,fromIndex);
            unlock();
            return i;
        }

        JStringBuffer* JStringBuffer::reverse(){
            lock();
            JAbstractStringBuilder::reverse();
            unlock();
            return this;
        }

        string JStringBuffer::toString(){
            lock();
            string str=JAbstractStringBuilder::toString();
            unlock();
            return str;
        }

        static JPrimitiveArray* serialPersistentFields;
        JPrimitiveArray* JStringBuffer::getSerialPersistentFields(){
            if (serialPersistentFields==NULL){
                serialPersistentFields=new JPrimitiveArray(JObjectStreamField::getClazz(),3);
                serialPersistentFields->set(0,new JObjectStreamField("value",JPrimitiveArray::getClazz(JPrimitiveChar::getClazz())));
                serialPersistentFields->set(1,new JObjectStreamField("count",JInteger::TYPE));
                serialPersistentFields->set(2,new JObjectStreamField("shared",JBoolean::TYPE));
            }
            return serialPersistentFields;
        }

        void JStringBuffer::writeObject(JObjectOutputStream* out){
            JObjectOutputStream::JPutField* fields = out->putFields();
            fields->put("value", getPrimitiveArray());
            fields->put("count", (jint)value.size());
            fields->put("shared", false);
            out->writeFields();
        }

        void JStringBuffer::readObject(JObjectInputStream* in){
            JObjectInputStream::JGetField* fields = in->readFields();
            setPrimitiveArray((JPrimitiveArray*)fields->get("value", (JObject*)NULL));
            fields->get("count", 0);
        }

        JStringBuffer::~JStringBuffer(){
        }
    }
}
