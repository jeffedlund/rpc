#ifndef JSTRING_H
#define JSTRING_H

#include "JObject.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JString : public JObject{
            string str;

        public:
            JString();
            JString(string str);
            bool operator==(JString &other);
            static JClass* getClazz();
            string getString();
            void setString(string str);
            string toString();
            ~JString();
        };
    }
}
#endif // JSTRING_H
