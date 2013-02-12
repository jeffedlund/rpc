#ifndef JBYTE_H
#define JBYTE_H

#include "JObject.h"
#include "JNumber.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
#include "JPrimitiveByte.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JByte : public JNumber{

            protected:
                JPrimitiveByte* value;

            public:
                JByte();
                JByte(qint8 value);
                bool operator==(JObject &other);

                static JClass* getClazz();

                void set(qint8 value);

                qint8 get();

                void setPrimitiveByte(JPrimitiveByte* value);

                JPrimitiveByte* getPrimitiveByte();

                string toString();

                ~JByte();
        };
    }
}

#endif // JBYTE_H
