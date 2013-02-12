#ifndef JLONG_H
#define JLONG_H

#include "JObject.h"
#include "JNumber.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
#include "JPrimitiveLong.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JLong : public JNumber{

            protected:
                JPrimitiveLong* value;

            public:
                JLong();
                JLong(qint64 value);
                bool operator==(JObject &other);

                static JClass* getClazz();

                void set(qint64 value);

                qint64 get();

                void setPrimitiveLong(JPrimitiveLong* value);

                JPrimitiveLong* getPrimitiveLong();

                string toString();

                ~JLong();
        };
    }
}

#endif // JLONG_H
