#ifndef JCHAR_H
#define JCHAR_H

#include "JObject.h"
#include <vector>
#include <iostream>
#include "JPrimitiveChar.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JChar : public JObject{

            protected:
                JPrimitiveChar* value;

            public:
                JChar();
                JChar(char value);
                JChar(jchar value);
                bool operator==(JObject &other);

                static JClass* getClazz();

                void set(char value);

                char get();

                void setPrimitiveChar(JPrimitiveChar* value);

                JPrimitiveChar* getPrimitiveChar();

                string toString();

                virtual ~JChar();
        };
    }
}
#endif // JCHAR_H
