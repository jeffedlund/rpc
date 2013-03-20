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

        JString::JString(): JObject(getClazz()){
        }

        JString::JString(string str): JObject(getClazz()){
            this->str=str;
        }

        JString::JString(JString* str): JObject(getClazz()){
            this->str=str->str.c_str();
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

        void JString::setString(string str) {
            this->str = str;
        }

        JString* JString::clone(){
            JString* jstr=new JString();
            jstr->str=str.c_str();
            return jstr;
        }

        string JString::toString(){
            return str;
        }
    }
}
