#ifndef JCHAR_H
#define JCHAR_H

#include "JObject.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
#include "JPrimitiveChar.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JChar : public JObject{

            protected:
                JPrimitiveChar* value;

            public:
                JChar();
                JChar(char value);
                bool operator==(JObject &other);

                static JClass* getClazz();

                void set(char value);

                char get();

                void setPrimitiveChar(JPrimitiveChar* value);

                JPrimitiveChar* getPrimitiveChar();

                string toString();

                ~JChar();
        };
    }
}
#endif // JCHAR_H
