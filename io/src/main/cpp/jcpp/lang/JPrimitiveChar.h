#ifndef JPRIMITIVECHAR_H
#define JPRIMITIVECHAR_H

#include "JObject.h"
#include <vector>
#include <iostream>
using namespace std;

namespace jcpp{
    namespace lang{
        class JPrimitiveChar : public JObject{

            protected:
                jchar value;

            public:
                JPrimitiveChar();
                JPrimitiveChar(char value);
                JPrimitiveChar(jchar value);
                bool operator==(JObject &other);

                static JClass* getClazz();

                void set(jchar value);

                jchar get();

                string toString();

                virtual ~JPrimitiveChar();
        };
    }
}
#endif // JPRIMITIVECHAR_H
