#ifndef JENUMSAMPLE_H
#define JENUMSAMPLE_H

#include "JObject.h"
#include "JClass.h"
#include "JPrimitiveBoolean.h"
#include "JPrimitiveByte.h"
#include "JPrimitiveChar.h"
#include "JPrimitiveDouble.h"
#include "JPrimitiveFloat.h"
#include "JPrimitiveInt.h"
#include "JPrimitiveLong.h"
#include "JPrimitiveShort.h"
#include "JSerializable.h"
#include "JEnum.h"
using namespace jcpp::io;

namespace jcpp{
    class JEnumSample : public JEnum{
    protected:
        class JEnumSampleClass : public JEnumClass{
          public:
            JEnumSampleClass();
            virtual JClass* getSuperclass();
            virtual void fillEnumConstants();
        };

        JString* fieldString;
        JEnumSample(JString* fieldString, JString* name, JPrimitiveInt* ordinal);
    public:
        static JClass* getClazz();
        static JEnumSample* E1;
        static JEnumSample* E2;
        static JEnumSample* E3;
        static JEnumSample* E4;
        static JEnumSample* E5;
        JString* getFieldString();
        void setFieldString(JString* fieldString);
        virtual string toString();
        virtual ~JEnumSample();
    };
}

#endif // JENUMSAMPLE_H
