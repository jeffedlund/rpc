#ifndef JPRIMITIVELONG_H
#define JPRIMITIVELONG_H

#include "JObject.h"
#include <vector>
#include <iostream>
#include "Object.h"
#include "JCPP.h"
#include "JComparable.h"
#include "JSerializable.h"
using namespace std;
using namespace jcpp::io;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JPrimitiveLong : public JObject, public JComparable, public JSerializable{

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
                virtual jint compareTo(JObject* o);
                virtual jbool equals(JObject* other);
                virtual jint hashCode();
                virtual string toString();
                virtual ~JPrimitiveLong();
        };
    }
}

#endif // JPRIMITIVELONG_H
