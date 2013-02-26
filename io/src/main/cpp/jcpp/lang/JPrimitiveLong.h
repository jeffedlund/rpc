#ifndef JPRIMITIVELONG_H
#define JPRIMITIVELONG_H

#include "JObject.h"
#include <vector>
#include <iostream>
#include "Object.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JPrimitiveLong : public JObject{

            protected:
                jlong value;

            public:
                JPrimitiveLong();
                JPrimitiveLong(jlong value);
                bool operator==(JObject &other);

                static JClass* getClazz();

                void set(jlong value);

                jlong get();

                string toString();

                virtual ~JPrimitiveLong();
        };
    }
}

#endif // JPRIMITIVELONG_H
