#ifndef JPRIMITIVELONG_H
#define JPRIMITIVELONG_H

#include "JObject.h"
#include <vector>
#include <iostream>
#include "Object.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JPrimitiveLong : public JObject{

            protected:
                jlong value;

            public:
                JPrimitiveLong();
                JPrimitiveLong(jlong value);
                JPrimitiveLong operator+=(jlong f);
                JPrimitiveLong operator-=(jlong f);
                JPrimitiveLong operator*=(jlong f);
                static JClass* getClazz();
                void set(jlong value);
                jlong get();
                virtual bool equals(JObject* other);
                virtual jint hashCode();
                virtual string toString();
                virtual ~JPrimitiveLong();
        };
    }
}

#endif // JPRIMITIVELONG_H
