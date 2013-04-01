#ifndef JSTRING_H
#define JSTRING_H

#include "JObject.h"
#include "JCPP.h"
#include "JComparable.h"
using namespace std;

//TODO implement more method + charsequence
namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JString : public JObject, public JComparable{
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
            static JString* intern(string s);
            static jint hashCode(string s);
            static jint compare(string s1,string s2);
            JString();
            JString(string str);
            JString(JString* str);
            static JClass* getClazz();
            jint length();
            jbool isEmpty();
            jchar charAt(jint index);
            jbool operator<(JString &other);
            string getString();
            void setString(string str);
            virtual jint compareTo(JObject* o);
            virtual JString* clone();
            virtual jbool equals(JObject* other);
            virtual jint hashCode();
            virtual string toString();
            virtual ~JString();
        };
    }
}
#endif // JSTRING_H
