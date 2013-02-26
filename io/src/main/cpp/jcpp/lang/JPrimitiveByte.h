#ifndef JPRIMITIVEBYTE_H
#define JPRIMITIVEBYTE_H

#include "JObject.h"
#include <vector>
#include <iostream>
#include "Object.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JPrimitiveByte : public JObject{

            protected:
                jbyte value;

            public:
                JPrimitiveByte();
                JPrimitiveByte(jbyte value);
                bool operator==(JObject &other);

                static JClass* getClazz();

                void set(jbyte value);

                jbyte get();

                string toString();

                virtual ~JPrimitiveByte();
        };
    }
}
#endif // JPRIMITIVEBYTE_H
