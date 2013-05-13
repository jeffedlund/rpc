#ifndef JPRIMITIVEBYTE_H
#define JPRIMITIVEBYTE_H

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
        class JCPP_LIBRARY_EXPORT JPrimitiveByte : public JObject, public JComparable, public JSerializable{
            protected:
                jbyte value;

            public:
                JPrimitiveByte();
                JPrimitiveByte(jbyte value);
                JPrimitiveByte& operator+=(jbyte f);
                JPrimitiveByte& operator-=(jbyte f);
                JPrimitiveByte& operator*=(jbyte f);
                static JClass* getClazz();
                void set(jbyte value);
                jbyte get();
                virtual jint compareTo(JObject* o);
                virtual jbool equals(JObject* other);
                virtual jint hashCode();
                virtual JString toString();
                virtual ~JPrimitiveByte();
        };
    }
}
#endif // JPRIMITIVEBYTE_H
