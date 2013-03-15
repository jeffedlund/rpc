#ifndef JPRIMITIVEBYTE_H
#define JPRIMITIVEBYTE_H

#include "JObject.h"
#include <vector>
#include <iostream>
#include "Object.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JPrimitiveByte : public JObject{

            protected:
                jbyte value;

            public:
                JPrimitiveByte();
                JPrimitiveByte(jbyte value);
                bool operator==(JObject &other);
                JPrimitiveByte operator+=(jbyte f);
                JPrimitiveByte operator-=(jbyte f);
                JPrimitiveByte operator*=(jbyte f);
                static JClass* getClazz();
                void set(jbyte value);
                jbyte get();
                string toString();
                virtual ~JPrimitiveByte();
        };
    }
}
#endif // JPRIMITIVEBYTE_H
