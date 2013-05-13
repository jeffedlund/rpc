#include "JAbstractStringBuilder.h"
#include "JClass.h"
#include "algorithm"
#include "sstream"
#include "JStringBuffer.h"
#include "JPrimitiveChar.h"

using namespace std;

namespace jcpp{
    namespace lang{
        class JAbstractStringBuilderClass : public JClass{
            public:
                JAbstractStringBuilderClass(){
                    this->canonicalName="java.lang.AbstractStringBuilder";
                    this->name="java.lang.AbstractStringBuilder";
                    this->simpleName="AbstractStringBuilder";
                    addInterface(JAppendable::getClazz());
                    addInterface(JCharSequence::getClazz());
                }

                JClass* getSuperclass(){
                    return JObject::getClazz();
                }
        };

        static JClass* clazz;

        JClass* JAbstractStringBuilder::getClazz(){
            if (clazz==NULL){
                clazz=new JAbstractStringBuilderClass();
            }
            return clazz;
        }

        JAbstractStringBuilder::JAbstractStringBuilder(JClass* _class):JObject(_class){
            pvalue=NULL;
        }

        JPrimitiveArray* JAbstractStringBuilder::getPrimitiveArray(){
            if (this->pvalue!=NULL){
                delete this->pvalue;
            }
            this->pvalue=JPrimitiveChar::toArray(value);
            return pvalue;
        }

        void JAbstractStringBuilder::setPrimitiveArray(JPrimitiveArray* a){
            value=JPrimitiveChar::fromArray(a);
            delete a;
        }

        jint JAbstractStringBuilder::length(){
            return value.length();
        }

        jint JAbstractStringBuilder::capacity(){
            return value.length()*2;//not extra...
        }

        void JAbstractStringBuilder::ensureCapacity(jint){
        }

        void JAbstractStringBuilder::trimToSize(){
        }

        void JAbstractStringBuilder::setLength(jint){
            //TODO do something, throw exception or implement
        }

        jchar JAbstractStringBuilder::charAt(jint index){
            return (jchar)value.charAt(index);
        }

        void JAbstractStringBuilder::getChars(jint srcBegin,jint srcEnd,jchar dst[],jint dstBegin){
            for (jint i=0;i<srcEnd-srcBegin;i++){
                dst[i+dstBegin]=value.charAt(i+srcBegin);
            }
        }

        void JAbstractStringBuilder::setCharAt(jint index,jchar c){
            value.setCharAt(index,c);
        }

        JAbstractStringBuilder* JAbstractStringBuilder::append(JObject* o){
            return append(JString::valueOf(o));
        }

        JAbstractStringBuilder* JAbstractStringBuilder::append(JString* o){
            return append(JString::valueOf(o));
        }

        JAbstractStringBuilder* JAbstractStringBuilder::append(JString str){
            value<<str;
            return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::append(JStringBuffer* sb){
            value<<sb->value;
            return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::append(JCharSequence* s){
            return append(s,0,s->length());
        }

        JAbstractStringBuilder* JAbstractStringBuilder::append(JCharSequence* s,jint start,jint end){
            for (jint i=0;i<end-start;i++){
                value<<s->charAt(start+i);
            }
            return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::append(jchar str[],jint offset,jint length){
            for (jint i=0;i<length;i++){
                value<<str[offset+i];
            }
            return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::append(JString str,jint offset,jint length){
            for (jint i=0;i<length;i++){
                value<<str.charAt(offset+i);
            }
            return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::append(jbool b){
            if (b){
                value<<"true";
            }else{
                value<<"false";
            }
            return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::append(jchar c){
            value<<c;
            return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::append(jint i){
            value<<i;
            return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::append(jlong l){
            value<<l;
            return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::append(jfloat f){
            value<<f;
            return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::append(jdouble d){
            value<<d;
            return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::deleteChar(jint start,jint end){
            value.deleteChar(start,end);
            return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::deleteCharAt(jint index){
            value.deleteChar(index,value.length());
            return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::replace(jint start,jint end,JString* str){
            JString s1=value.substring(start,end);
            JString s2=value.substring(end,value.length());
            value=s1+*str+s2;
            return this;
        }

        JString JAbstractStringBuilder::substring(jint start){
            return value.substring(start,value.length()-start);
        }

        JCharSequence* JAbstractStringBuilder::subSequence(jint start,jint end){
            JString* s=new JString(substring(start,end));
            return dynamic_cast<JCharSequence*>(s);
        }

        JString JAbstractStringBuilder::substring(jint start,jint end){
            return value.substring(start,end);
        }

        JAbstractStringBuilder* JAbstractStringBuilder::insert(jint index,jchar str[],jint offset,jint len){
            for (jint i=0;i<len;i++){
                value.insertChar(index+i,str[offset+i]);
            }
            return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::insert(jint offset,JObject* o){
            insert(offset,JString::valueOf(o));
            return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::insert(jint offset,JString* str){
            insert(offset,JString::valueOf(str));
            return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::insert(jint offset,JString str){
            for (int i=0;i<str.length();i++){
                value.insertChar(i+offset,str.charAt(i));
            }
            return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::insert(jint offset,jchar str[],jint l){
            for (jint i=0;i<l;i++){
                value.insertChar(i+offset,str[i]);
            }
            return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::insert(jint offset,JCharSequence* s){
            insert(offset,s,0,s->length());
            return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::insert(jint offset,JCharSequence* s,jint start,jint end){
            for (jint i=0;i<end-start;i++){
                value.insertChar(i+offset,s->charAt(i+start));
            }
            return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::insert(jint offset,jbool b){
            insert(offset,(b?"true":"false"));
            return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::insert(jint offset,jchar c){
            value.insertChar(offset,c);
            return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::insert(jint offset,jint i){
            insert(offset,JString()<<i);
            return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::insert(jint offset,jlong l){
            insert(offset,JString()<<l);
            return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::insert(jint offset,jfloat f){
            insert(offset,JString()<<f);
            return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::insert(jint offset,jdouble d){
            insert(offset,JString()<<d);
            return this;
        }

        jint JAbstractStringBuilder::indexOf(JString str){
            return indexOf(str,0);
        }

        jint JAbstractStringBuilder::indexOf(JString str,jint fromIndex){
            return value.indexOf(str,fromIndex);
        }

        jint JAbstractStringBuilder::lastIndexOf(JString str){
            return lastIndexOf(str,0);
        }

        jint JAbstractStringBuilder::lastIndexOf(JString str,jint fromIndex){
            return value.lastIndexOf(str,fromIndex);
        }

        JAbstractStringBuilder* JAbstractStringBuilder::reverse(){
            value=value.reverse();
            return this;
        }

        JString JAbstractStringBuilder::toString(){
            return value;
        }

        jbool JAbstractStringBuilder::equals(JObject *o){
            if (getClass()!=o->getClass()){
                return false;
            }
            return value.equals((dynamic_cast<JAbstractStringBuilder*>(o))->value);
        }

        JAbstractStringBuilder::~JAbstractStringBuilder(){
            if (pvalue!=NULL){
                delete pvalue;
            }
        }
    }
}
