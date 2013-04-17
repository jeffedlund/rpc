#include "JString.h"
#include "JClass.h"
#include "JSerializable.h"
#include "Collections.h"
using namespace jcpp::io;
using namespace jcpp::util;

namespace jcpp{
    namespace lang{
        class JStringClass : public JClass{
        public:
          JStringClass(){
              this->canonicalName="java.lang.String";
              this->name="java.lang.String";
              this->simpleName="String";
              this->serialVersionUID=-6849794470754667710ULL;
              addInterface(JSerializable::getClazz());
              addInterface(JComparable::getClazz());
              addInterface(JCloneable::getClazz());
          }

          JClass* getSuperclass(){
              return JObject::getClazz();
          }

          JObject* newInstance(){
              return new JString();
          }
        };

        static JClass* clazz;

        JClass* JString::getClazz(){
            if (clazz==NULL){
                clazz=new JStringClass();
            }
            return clazz;
        }

        static map<string,JString*>* internStrings=NULL;

        JString* JString::intern(string s){
            getClazz()->lock();
            if (internStrings==NULL){
                internStrings=new map<string,JString*>();
            }
            JString* js=getFromMap(internStrings,s);
            if (js==NULL){
                js=new JString(s);
                internStrings->insert(pair<string,JString*>(s,js));
            }
            getClazz()->unlock();
            return js;
        }

        jint JString::hashCode(string s){
            jint h=0;//TODO cache it
            for (unsigned int i=0;i<s.size();i++){
                h=31*h+(jint)s.at(i);
            }
            return h;
        }

        jint JString::compare(string s1,string s2){
            jint len1 = s1.size();
            jint len2 = s2.size();
            jint lim = (len1<len2?len1:len2);

            jint k = 0;
            while (k < lim) {
                jchar c1 = s1.at(k);
                jchar c2 = s1.at(k);
                if (c1 != c2) {
                    return c1 - c2;
                }
                k++;
            }
            return len1 - len2;
        }

        string JString::valueOf(JObject* obj){
            return (obj==NULL ? "null" : obj->toString());
        }

        JString::JString(): JObject(getClazz()){
        }

        JString::JString(string str): JObject(getClazz()){
            this->str=str;
        }

        JString::JString(JString* str): JObject(getClazz()){
            this->str=str->str.c_str();
        }

        jint JString::length(){
            return str.size();
        }

        jbool JString::isEmpty(){
            return str.size()==0;
        }

        jchar JString::charAt(jint index){
            return (jchar)str.at(index);
        }

        bool JString::equals(JObject* other){
            if (other->getClass()==getClazz()){
                JString* s=dynamic_cast<JString*>(other);
                return (str==s->str);
            }
            return false;
        }

        bool JString::operator<(JString &other){
            return str<other.str;
        }

        JString::~JString() {
        }

        string JString::getString(){
            return str;
        }

        void JString::getChars(jint srcBegin, jint srcEnd, jchar dst[], jint dstBegin){
            for (jint i=0;i<srcEnd-srcBegin;i++){
                dst[dstBegin+i]=(jchar)str.at(srcBegin+i);
            }
        }

        void JString::setString(string str) {
            this->str = str;
        }

        jint JString::compareTo(JObject* o){
            JString* s=dynamic_cast<JString*>(o);
            return compare(str,s->str);
        }

        JString* JString::clone(){
            JString* jstr=new JString();
            jstr->str=str.c_str();
            return jstr;
        }

        jint JString::hashCode(){
            return hashCode(str);
        }

        string JString::toString(){
            return str;
        }
    }
}
