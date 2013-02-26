#ifndef JSTRING_H
#define JSTRING_H

#include "JObject.h"
using namespace std;

//TODO implement necessary operators to be able to put it in a std::map as a key
namespace jcpp{
    namespace lang{
        class JString : public JObject{
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
            JString();
            JString(string str);
            JString(JString* str);
            bool operator==(JObject &other);
            bool operator<(JObject &other);
            static JClass* getClazz();
            string getString();
            void setString(string str);
            virtual JString* clone();
            string toString();
            virtual ~JString();
        };
    }
}
#endif // JSTRING_H
