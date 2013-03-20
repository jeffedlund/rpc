#ifndef JSTRING_H
#define JSTRING_H

#include "JObject.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JString : public JObject{
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
            JString();
            JString(string str);
            JString(JString* str);
            static JClass* getClazz();
            bool operator<(JString &other);
            string getString();
            void setString(string str);
            virtual JString* clone();
            virtual bool equals(JObject* other);
            virtual jint hashCode();
            virtual string toString();
            virtual ~JString();
        };
    }
}
#endif // JSTRING_H
