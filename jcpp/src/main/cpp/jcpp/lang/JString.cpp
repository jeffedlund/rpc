#include "JString.h"
#include "JClass.h"
#include "JSerializable.h"
#include "Collections.h"
#include "QString"
#include <algorithm>
#include "JObject.h"
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

        static map<JString,JString*>* internStrings=NULL;

        JString* JString::intern(JString s){
            getClazz()->lock();
            if (internStrings==NULL){
                internStrings=new map<JString,JString*>();
            }
            JString* js=getFromMap(internStrings,s);
            if (js==NULL){
                js=new JString(s);
                internStrings->insert(pair<JString,JString*>(s,js));
            }
            getClazz()->unlock();
            return js;
        }

        jint JString::hashCode(JString s){
            jint h=0;//TODO cache it
            for (jint i=0;i<s.length();i++){
                h=31*h+(jint)s.charAt(i);
            }
            return h;
        }

        jint JString::compare(JString s1,JString s2){
            jint len1 = s1.length();
            jint len2 = s2.length();
            jint lim = (len1<len2?len1:len2);

            jint k = 0;
            while (k < lim) {
                jchar c1 = s1.charAt(k);
                jchar c2 = s1.charAt(k);
                if (c1 != c2) {
                    return c1 - c2;
                }
                k++;
            }
            return len1 - len2;
        }

        JString JString::valueOf(JObject* obj){
            return (obj==NULL ? "null" : obj->toString());
        }

        JString::JString(): JObject(false){
        }

        JString::JString(string str): JObject(false){
            this->str=str;
        }

        JString::JString(JString* str): JObject(false){
            this->str=string(str->str);
        }

        JString::JString(const char* c): JObject(false){
            this->str=string(c);
        }

        JString::JString(jchar* c,jint offset,jint length):JObject(false){
            this->str=string("");//TODO encoding
            for (jint i=offset;i<length;i++){
                str.push_back(c[i]);
            }
        }

        JString::JString(vector<jbyte>* bytes):JObject(false){
            this->str=string(bytes->begin(),bytes->end());//TODO encoding + test
        }

        JString::JString(vector<jchar>* chars):JObject(false){
            this->str=string(chars->begin(),chars->end());//TODO encoding + test
        }

        JString::JString(const JString& s):JObject(false){
            this->str=string(s.str);
        }

        JString::JString(jchar c):JObject(false){
            this->str=string();
            str.push_back(c);
        }

        JClass* JString::getClass(){
            return JString::getClazz();
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

        bool JString::operator<(const JString &other) const{
            return str<other.str;
        }

        JString& JString::operator+(string& s){
            this->str+=s;
            return *this;
        }

        JString& JString::operator+(string s){
            this->str+=s;
            return *this;
        }

        JString& JString::operator+(JString& s){
            this->str+=s.getString();
            return *this;
        }

        JString& JString::operator+(JString s){
            this->str+=s.getString();
            return *this;
        }

        JString& JString::operator+(const char* s){
            this->str+=s;
            return *this;
        }

        JString& JString::operator+=(string& s){
            this->str+=s;
            return *this;
        }

        JString& JString::operator+=(JString s){
            this->str+=s.getString();
            return *this;
        }

        JString& JString::operator+=(const char* s){
            this->str+=s;
            return *this;
        }

        JString& JString::operator=(string& s){
            this->str=s;
            return *this;
        }

        JString& JString::operator=(JString s){
            this->str=s.getString();
            return *this;
        }

        JString& JString::operator=(const char* s){
            this->str=string(s);
            return *this;
        }

        jbool JString::operator==(string s){
            return str==s;
        }

        jbool JString::operator==(string& s){
            return str==s;
        }

        jbool JString::operator==(const char* c){
            return str==string(c);
        }

        jbool JString::operator==(JString s){
            return str==s.str;
        }

        JString& JString::operator<<(JString s){
            str+=s.str;
            return *this;
        }

        JString& JString::operator<<(jbyte l){
            stringstream ss;
            ss<<str<<l;
            str=ss.str();
            return *this;
        }

        JString& JString::operator<<(jchar l){
            stringstream ss;
            ss<<str<<l;
            str=ss.str();
            return *this;
        }

        JString& JString::operator<<(char l){
            stringstream ss;
            ss<<str<<l;
            str=ss.str();
            return *this;
        }

        JString& JString::operator<<(jdouble l){
            stringstream ss;
            ss<<str<<l;
            str=ss.str();
            return *this;
        }

        JString& JString::operator<<(jfloat l){
            stringstream ss;
            ss<<str<<l;
            str=ss.str();
            return *this;
        }

        JString& JString::operator<<(jint l){
            stringstream ss;
            ss<<str<<l;
            str=ss.str();
            return *this;
        }

        JString& JString::operator<<(jlong l){
            stringstream ss;
            ss<<str<<l;
            str=ss.str();
            return *this;
        }

        JString& JString::operator<<(jshort l){
            stringstream ss;
            ss<<str<<l;
            str=ss.str();
            return *this;
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

        JString JString::replace(jchar oldchar,jchar newchar){
            string s=this->str;
            std::replace(s.begin(),s.end(),oldchar,newchar);
            return JString(s);
        }

        JString JString::substring(jint start,jint end){
            return JString(this->str.substr(start,end));//TODO
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

        JString JString::toString(){
            return JString(str);
        }
    }
}

JString jcpp::lang::operator+(string s,jcpp::lang::JString str) {
    str.setString(s+str.getString());
    return str;
}

JString jcpp::lang::operator+(const char* s,jcpp::lang::JString str) {
    str.setString(s+str.getString());
    return str;
}

ostream& jcpp::lang::operator<<(ostream& os,jcpp::lang::JString o) {
    os<<o.getString();
    return os;
}
