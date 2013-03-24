#ifndef JPRIMITIVEBYTE_H
#define JPRIMITIVEBYTE_H

#include "JObject.h"
#include <vector>
#include <iostream>
#include "Object.h"
#include "JCPP.h"
#include "JComparable.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JPrimitiveByte : public JObject, public JComparable{

            protected:
                jbyte value;

            public:
                JPrimitiveByte();
                JPrimitiveByte(jbyte value);
                JPrimitiveByte operator+=(jbyte f);
                JPrimitiveByte operator-=(jbyte f);
                JPrimitiveByte operator*=(jbyte f);
                static JClass* getClazz();
                void set(jbyte value);
                jbyte get();
                virtual jint compareTo(JObject* o);
                virtual bool equals(JObject* other);
                virtual jint hashCode();
                virtual string toString();
                virtual ~JPrimitiveByte();
        };
    }
}
#endif // JPRIMITIVEBYTE_H
