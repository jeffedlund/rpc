#ifndef JSHORT_H
#define JSHORT_H

#include "JObject.h"
#include "JNumber.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
#include "JPrimitiveShort.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JShort : public JNumber{
            protected:
                JPrimitiveShort* value;

            public:
                JShort();
                JShort(qint16 value);
                bool operator==(JObject &other);

                static JClass* getClazz();

                void set(qint16 value);

                qint16 get();

                void setPrimitiveShort(JPrimitiveShort* value);

                JPrimitiveShort* getPrimitiveShort();

                string toString();

                ~JShort();
        };
    }
}

#endif // JSHORT_H

