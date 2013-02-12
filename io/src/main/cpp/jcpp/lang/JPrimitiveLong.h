#ifndef JPRIMITIVELONG_H
#define JPRIMITIVELONG_H

#include "JObject.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
using namespace std;

namespace jcpp{
    namespace lang{
        class JPrimitiveLong : public JObject{

            protected:
                qint64 value;

            public:
                JPrimitiveLong();
                JPrimitiveLong(qint64 value);
                bool operator==(JObject &other);

                static JClass* getClazz();

                void set(qint64 value);

                qint64 get();

                string toString();

                ~JPrimitiveLong();
        };
    }
}

#endif // JPRIMITIVELONG_H
