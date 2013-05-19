#include "JString.h"
#include "JClass.h"
#include "JSerializable.h"
#include "Collections.h"
#include "QString"
#include <algorithm>
#include "JObject.h"
#include "JBits.h"
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
                internStrings->insert(pair<JString,JString*>(*js,js));
            }
            getClazz()->unlock();
            return js;
        }

        jint JString::hashCode(JString s){
            jint h=0;
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
            char* cs=new char[length+1];
            for (jint i=0;i<length;i++){
                cs[i+offset]=(char)c[i];
            }
            cs[length] = '\0';
            this->str=string(cs);//TODO encoding + test
            delete cs;
        }

        JString::JString(vector<jbyte>* bytes):JObject(false){
            this->str=string(bytes->begin(),bytes->end());//TODO encoding + test
        }

        JString::JString(vector<jchar>* chars):JObject(false){
            jchar* jc=new jchar[chars->size()];//not extra
            for (unsigned int i=0;i<chars->size();i++){
                jc[i]=chars->at(i);
            }
            char* cs=new char[chars->size()+1];//TODO  encoding+test
            cs[chars->size()] = '\0';
            JBits::putCharFromJChar(cs,jc,0,chars->size());
            this->str=string(cs);
        }

        JString::JString(const JString& s):JObject(false){
            this->str=string(s.str);
        }

        JString::JString(jchar c):JObject(false){
            this->str=string();
            str.push_back(c);//TODO encoding + test
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

        void JString::setCharAt(jint index,jchar c){
            str.assign(index,c);
        }

        void JString::deleteChar(jint start,jint end){
            str.erase(str.begin()+start,str.begin()+end);
        }

        void JString::insertChar(jint index,jchar c){
            str.insert(index,1,c);
        }

        jint JString::indexOf(JString str){
            return this->str.find(str.str,0);
        }

        jint JString::indexOf(JString str,jint from){
            return this->str.find(str.str,from);
        }

        jint JString::lastIndexOf(JString str,jint from){
            return this->str.find_last_of(str.str,from);
        }

        JString JString::reverse(){
            string s=string(str);
            std::reverse(s.begin(),s.end());
            return JString(s);
        }

        JString& JString::operator=(JString s){
            str=s.str;
            return *this;
        }

        JString& JString::operator=(const char* s){
            str=string(s);
            return *this;
        }

        JString& JString::operator+=(JString s){
            str+=s.str;
            return *this;
        }

        jbool JString::operator<(JString other) const{
            return str<other.str;
        }

        jbool JString::operator>(JString other){
            return str>other.str;
        }

        jbool JString::operator!=(JString other){
            return str!=other.str;
        }

        jbool JString::operator<=(JString other){
            return str<=other.str;
        }

        jbool JString::operator>=(JString other){
            return str>=other.str;
        }

        jbool JString::operator==(JString other){
            return str==other.str;
        }

        jbool JString::operator==(const char* c){
            return str==string(c);
        }

        JString JString::operator+(JString s){
            JString ss=JString(str);
            ss<<s;
            return ss;
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

        bool JString::equals(JObject* other){
            if (other->getClass()==getClazz()){
                JString* s=dynamic_cast<JString*>(other);
                return (str==s->str);
            }
            return false;
        }

        jbool JString::equals(JString other){
            return str==other.str;
        }

        string JString::getString(){
            return str;
        }

        void JString::getChars(jint srcBegin, jint srcEnd, jchar dst[], jint dstBegin){
            string s=str.substr(srcBegin,srcEnd);
            const char* cs = s.c_str();//TODO encoding+test
            JBits::putJCharFromChar(dst,cs,dstBegin,srcEnd-srcBegin);
        }

        JString JString::replace(jchar oldchar,jchar newchar){
            string s=this->str;
            std::replace(s.begin(),s.end(),oldchar,newchar);
            return JString(s);
        }

        JString JString::substring(jint start){
            return JString(this->str.substr(start,str.size()));
        }

        JString JString::substring(jint start,jint end){
            return JString(this->str.substr(start,end));
        }

        void JString::setString(string str) {
            this->str = str;
        }

        jint JString::compareTo(JObject* o){
            JString* s=dynamic_cast<JString*>(o);
            return compare(str,s->str);
        }

        JString* JString::clone(){
            JString* jstr=new JString(this);
            return jstr;
        }

        jint JString::hashCode(){
            return hashCode(str);
        }

        JString JString::toString(){
            return JString(this);
        }

        JString::~JString(){
        }
    }
}

JString jcpp::lang::operator+(string s,jcpp::lang::JString str) {
    JString ss=JString(s);
    ss<<str;
    return ss;
}

JString jcpp::lang::operator+(const char* s,jcpp::lang::JString str) {
    JString ss=JString(s);
    ss<<str;
    return ss;
}

ostream& jcpp::lang::operator<<(ostream& os,jcpp::lang::JString o) {
    os<<o.getString();
    return os;
}
