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
            ~JString();
        };
    }
}
#endif // JSTRING_H
