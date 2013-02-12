#ifndef JPRIMITIVEBYTE_H
#define JPRIMITIVEBYTE_H

#include "JObject.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
using namespace std;

namespace jcpp{
    namespace lang{
        class JPrimitiveByte : public JObject{

            protected:
                qint8 value;

            public:
                JPrimitiveByte();
                JPrimitiveByte(qint8 value);
                bool operator==(JObject &other);

                static JClass* getClazz();

                void set(qint8 value);

                qint8 get();

                string toString();

                ~JPrimitiveByte();
        };
    }
}
#endif // JPRIMITIVEBYTE_H
