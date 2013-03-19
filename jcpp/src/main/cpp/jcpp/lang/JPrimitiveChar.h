#ifndef JPRIMITIVECHAR_H
#define JPRIMITIVECHAR_H

#include "JObject.h"
#include <vector>
#include <iostream>
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JPrimitiveChar : public JObject{

            protected:
                jchar value;

            public:
                JPrimitiveChar();
                JPrimitiveChar(char value);
                JPrimitiveChar(jchar value);
                virtual bool equals(JObject* other);

                static JClass* getClazz();

                void set(jchar value);

                jchar get();

                string toString();

                virtual ~JPrimitiveChar();
        };
    }
}
#endif // JPRIMITIVECHAR_H
