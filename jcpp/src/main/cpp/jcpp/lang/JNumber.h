#ifndef JNUMBER_H
#define JNUMBER_H

#include "JObject.h"
#include "JClass.h"
#include "JSerializable.h"
#include <vector>
#include <iostream>
#include "JCPP.h"
#include "JSerializable.h"
using namespace std;
using namespace jcpp::io;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JNumber: public JObject, public JSerializable{
            protected :
                JNumber(JClass* _class);

            public:
                static JClass* getClazz();
                virtual jint intValue()=0;
                virtual jlong longValue()=0;
                virtual jfloat floatValue()=0;
                virtual jdouble doubleValue()=0;
                virtual jbyte byteValue() {
                    return (jbyte)intValue();
                }
                virtual jshort shortValue() {
                    return (jshort)intValue();
                }
                virtual JString toString()=0;
                virtual ~JNumber();
        };
    }
}
#endif // JNUMBER_H
