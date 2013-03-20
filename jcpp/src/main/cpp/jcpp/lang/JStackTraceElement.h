#ifndef JSTACKTRACEELEMENT_H
#define JSTACKTRACEELEMENT_H

#include "Object.h"
#include "JObject.h"
#include "JString.h"
#include "JSerializable.h"
#include "JPrimitiveInt.h"
#include "JCPP.h"
using namespace std;
using namespace jcpp::io;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JStackTraceElement: public JObject, public JSerializable {
        private:
            JString* declaringClass;
            JString* methodName;
            JString* fileName;
            JPrimitiveInt* lineNumber;

        public:
            JStackTraceElement();
            JStackTraceElement(JString* declaringClass,JString* methodName,JString* fileName,JPrimitiveInt* lineNumber);
            static JClass* getClazz();
            JString* getDeclaringClass();
            void setDeclaringClass(JString* declaringClass);
            JString* getMethodName();
            void setMethodName(JString* methodName);
            JString* getFileName();
            void setFileName(JString* fileName);
            JPrimitiveInt* getLineNumber();
            void setLineNumber(JPrimitiveInt* lineNumber);
            virtual bool equals(JObject* other);
            virtual jint hashCode();
            virtual string toString();
            virtual ~JStackTraceElement();
        };
    }
}


#endif // JSTACKTRACEELEMENT_H
