#ifndef JSTRING_H
#define JSTRING_H

#include "JObject.h"
#include "JComparable.h"
#include "JCPP.h"
#include "JCloneable.h"
using namespace std;

//TODO implement more method + charsequence
namespace jcpp{
    namespace lang{
        //TODO implement JCharSequence
        class JCPP_LIBRARY_EXPORT JString : public JObject, public JComparable, public JCloneable{
            string str;

        public:
            struct POINTER_COMPARATOR{//TODO better way?
                bool operator()(JString* e1, JString* e2){
                    if (e1->getString()<e2->getString()){
                        return true;
                    }
                    return false;
                }
            };
            static JString* intern(JString s);
            static jint hashCode(JString s);
            static jint compare(JString s1,JString s2);
            static JString valueOf(JObject* obj);
            JString();
            JString(string str);
            JString(JString* str);
            JString(const char* c);
            JString(jchar* c,jint offset,jint length);
            JString(vector<jbyte>* bytes);
            JString(vector<jchar>* chars);
            JString(const JString& str);
            JString(jchar c);
            virtual JClass* getClass();
            static JClass* getClazz();
            jint length();
            jbool isEmpty();
            jchar charAt(jint index);
            jbool operator<(const JString& other) const;
            JString& operator+(string& s);
            JString& operator+(string s);
            JString& operator+(JString& s);
            JString& operator+(JString s);
            JString& operator+(const char* s);
            JString& operator+=(string& s);
            JString& operator+=(JString s);
            JString& operator+=(const char* s);
            JString& operator=(string& s);
            JString& operator=(JString s);
            JString& operator=(const char* s);
            jbool operator==(string s);
            jbool operator==(string& s);
            jbool operator==(JString s);
            jbool operator==(const char*);
            JString& operator<<(JString s);
            JString& operator<<(jbyte l);
            JString& operator<<(jchar l);
            JString& operator<<(char l);
            JString& operator<<(jdouble l);
            JString& operator<<(jfloat l);
            JString& operator<<(jint l);
            JString& operator<<(jlong l);
            JString& operator<<(jshort l);
            string getString();
            void getChars(jint srcBegin, jint srcEnd, jchar dst[], jint dstBegin);
            JString replace(jchar oldchar,jchar newchar);
            JString substring(jint start,jint end);
            void setString(string str);
            virtual jint compareTo(JObject* o);
            virtual JString* clone();
            virtual jbool equals(JObject* other);
            virtual jint hashCode();
            virtual JString toString();
            virtual ~JString();
        };
        JCPP_LIBRARY_EXPORT JString operator+(string s,jcpp::lang::JString str);
        JCPP_LIBRARY_EXPORT JString operator+(const char* s,jcpp::lang::JString str);
        JCPP_LIBRARY_EXPORT ostream& operator<<(ostream& os,jcpp::lang::JString o);
    }
}
#endif // JSTRING_H
