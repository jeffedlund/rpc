#ifndef JPRIMITIVESHORT_H
#define JPRIMITIVESHORT_H

#include "JObject.h"
#include <vector>
#include <iostream>
#include "Object.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JPrimitiveShort : public JObject{

            protected:
                jshort value;

            public:
                JPrimitiveShort();
                JPrimitiveShort(jshort value);
                bool operator==(JObject &other);

                static JClass* getClazz();

                void set(jshort value);

                jshort get();

                string toString();

                ~JPrimitiveShort();
        };
    }
}

#endif // JPRIMITIVESHORT_H
