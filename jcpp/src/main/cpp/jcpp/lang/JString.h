#ifndef JSTRING_H
#define JSTRING_H

#include "JObject.h"
#include "JComparable.h"
#include "JCPP.h"
#include "JCloneable.h"
#include "QString"
using namespace std;

//TODO implement more method + JCharSequence
namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JString : public JObject, public JComparable, public JCloneable{
            string str;//TODO use QString+encoding instead

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
            void setCharAt(jint index,jchar c);
            void deleteChar(jint start,jint end);
            void insertChar(jint index,jchar c);
            jint indexOf(JString str,jint from);
            jint lastIndexOf(JString str,jint from);
            JString reverse();
            JString& operator=(JString s);
            JString& operator=(const char* s);
            JString& operator+=(JString s);
            jbool operator<(JString other) const;
            jbool operator>(JString other);
            jbool operator!=(JString other);
            jbool operator<=(JString other);
            jbool operator>=(JString other);
            jbool operator==(JString other);
            jbool operator==(const char* c);
            JString operator+(JString s);
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
            virtual jbool equals(JString other);
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
