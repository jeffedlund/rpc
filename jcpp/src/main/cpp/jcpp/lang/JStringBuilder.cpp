#include "JStringBuilder.h"
#include "JClass.h"
#include "JVoid.h"

namespace jcpp{
    namespace lang{
        class JStringBuilderClass : public JClass{
            protected:
                static JObject* invokeWriteObject(JObject* object,vector<JObject*>* args){
                    JStringBuilder* b=(JStringBuilder*)object;
                    b->writeObject((JObjectOutputStream*)args->at(0));
                    return NULL;
                }

                static JObject* invokeReadObject(JObject* object,vector<JObject*>* args){
                    JStringBuilder* b=(JStringBuilder*)object;
                    b->readObject((JObjectInputStream*)args->at(0));
                    return NULL;
                }

            public:
                JStringBuilderClass(){
                    this->canonicalName="java.lang.StringBuilder";
                    this->name="java.lang.StringBuilder";
                    this->simpleName="StringBuilder";
                    this->serialVersionUID=4383685877147921099ULL;

                    addInterface(JSerializable::getClazz());
                    addInterface(JCharSequence::getClazz());

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
                    return new JStringBuilder();
                }
        };

        static JClass* clazz;

        JClass* JStringBuilder::getClazz(){
            if (clazz==NULL){
                clazz=new JStringBuilderClass();
            }
            return clazz;
        }

        JStringBuilder::JStringBuilder():JAbstractStringBuilder(getClazz()){
        }

        JStringBuilder::JStringBuilder(JString str):JAbstractStringBuilder(getClazz()){
            append(str);
        }

        JStringBuilder::JStringBuilder(JCharSequence* seq):JAbstractStringBuilder(getClazz()){
            JAbstractStringBuilder::append(seq);
        }

        JStringBuilder* JStringBuilder::append(JObject *o){
            JAbstractStringBuilder::append(o);
            return this;
        }

        JStringBuilder* JStringBuilder::append(JString *o){
            JAbstractStringBuilder::append(o);
            return this;
        }

        JStringBuilder* JStringBuilder::append(JString str){
            JAbstractStringBuilder::append(str);
            return this;
        }

        JStringBuilder* JStringBuilder::append(JStringBuffer* sb){
            JAbstractStringBuilder::append(sb);
            return this;
        }

        JStringBuilder* JStringBuilder::append(JCharSequence* sq){
            JAbstractStringBuilder::append(sq);
            return this;
        }

        JStringBuilder* JStringBuilder::append(JCharSequence* sq,jint start,jint end){
            JAbstractStringBuilder::append(sq,start,end);
            return this;
        }

        JStringBuilder* JStringBuilder::append(jchar str[],jint offset,jint len){
            JAbstractStringBuilder::append(str,offset,len);
            return this;
        }

        JStringBuilder* JStringBuilder::append(JString str,jint offset,jint len){
            JAbstractStringBuilder::append(str,offset,len);
            return this;
        }

        JStringBuilder* JStringBuilder::append(jbool b){
            JAbstractStringBuilder::append(b);
            return this;
        }

        JStringBuilder* JStringBuilder::append(jchar c){
            JAbstractStringBuilder::append(c);
            return this;
        }

        JStringBuilder* JStringBuilder::append(jint i){
            JAbstractStringBuilder::append(i);
            return this;
        }

        JStringBuilder* JStringBuilder::append(jlong l){
            JAbstractStringBuilder::append(l);
            return this;
        }

        JStringBuilder* JStringBuilder::append(jfloat f){
            JAbstractStringBuilder::append(f);
            return this;
        }

        JStringBuilder* JStringBuilder::append(jdouble d){
            JAbstractStringBuilder::append(d);
            return this;
        }

        JStringBuilder* JStringBuilder::deleteChar(jint start,jint end){
            JAbstractStringBuilder::deleteChar(start,end);
            return this;
        }

        JStringBuilder* JStringBuilder::deleteCharAt(jint index){
            JAbstractStringBuilder::deleteCharAt(index);
            return this;
        }

        JStringBuilder* JStringBuilder::replace(jint start,jint end,JString* str){
            JAbstractStringBuilder::replace(start,end,str);
            return this;
        }

        JStringBuilder* JStringBuilder::insert(jint index,jchar str[],jint offset,jint len){
            JAbstractStringBuilder::insert(index,str,offset,len);
            return this;
        }

        JStringBuilder* JStringBuilder::insert(jint offset,JObject* o){
            JAbstractStringBuilder::insert(offset,o);
            return this;
        }

        JStringBuilder* JStringBuilder::insert(jint offset,JString* str){
            JAbstractStringBuilder::insert(offset,str);
            return this;
        }

        JStringBuilder* JStringBuilder::insert(jint offset,JString str){
            JAbstractStringBuilder::insert(offset,str);
            return this;
        }

        JStringBuilder* JStringBuilder::insert(jint offset,jchar str[],jint l){
            JAbstractStringBuilder::insert(offset,str,l);
            return this;
        }

        JStringBuilder* JStringBuilder::insert(jint offset,JCharSequence* s){
            JAbstractStringBuilder::insert(offset,s);
            return this;
        }

        JStringBuilder* JStringBuilder::insert(jint offset,JCharSequence* s,jint start,jint end){
            JAbstractStringBuilder::insert(offset,s,start,end);
            return this;
        }

        JStringBuilder* JStringBuilder::insert(jint offset,jbool b){
            JAbstractStringBuilder::insert(offset,b);
            return this;
        }

        JStringBuilder* JStringBuilder::insert(jint offset,jchar c){
            JAbstractStringBuilder::insert(offset,c);
            return this;
        }

        JStringBuilder* JStringBuilder::insert(jint offset,jint i){
            JAbstractStringBuilder::insert(offset,i);
            return this;
        }

        JStringBuilder* JStringBuilder::insert(jint offset,jlong l){
            JAbstractStringBuilder::insert(offset,l);
            return this;
        }

        JStringBuilder* JStringBuilder::insert(jint offset,jfloat f){
            JAbstractStringBuilder::insert(offset,f);
            return this;
        }

        JStringBuilder* JStringBuilder::insert(jint offset,jdouble d){
            JAbstractStringBuilder::insert(offset,d);
            return this;
        }

        JStringBuilder* JStringBuilder::reverse(){
            JAbstractStringBuilder::reverse();
            return this;
        }

        void JStringBuilder::writeObject(JObjectOutputStream* out){
            out->defaultWriteObject();
            out->writeInt(value.length());
            out->writeObject(getPrimitiveArray());
        }

        void JStringBuilder::readObject(JObjectInputStream* in){
            in->defaultReadObject();
            in->readInt();
            JPrimitiveArray* a=(JPrimitiveArray*)in->readObject();
            setPrimitiveArray(a);
        }

        JStringBuilder::~JStringBuilder(){
        }
    }
}
