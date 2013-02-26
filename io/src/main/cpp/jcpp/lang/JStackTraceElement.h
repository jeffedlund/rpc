#ifndef JSTACKTRACEELEMENT_H
#define JSTACKTRACEELEMENT_H

#include "Object.h"
#include "JObject.h"
#include "JString.h"
#include "JSerializable.h"
#include "JPrimitiveInt.h"
using namespace std;
using namespace jcpp::io;

namespace jcpp{
    namespace lang{
        class JStackTraceElement: public JObject, public JSerializable {
        private:
            JString* declaringClass;
            JString* methodName;
            JString* fileName;
            JPrimitiveInt* lineNumber;

        public:
            JStackTraceElement();
            JStackTraceElement(JString* declaringClass,JString* methodName,JString* fileName,JPrimitiveInt* lineNumber);
            bool operator==(JObject &other);

            static JClass* getClazz();

            JString* getDeclaringClass();

            void setDeclaringClass(JString* declaringClass);

            JString* getMethodName();

            void setMethodName(JString* methodName);

            JString* getFileName();

            void setFileName(JString* fileName);

            JPrimitiveInt* getLineNumber();

            void setLineNumber(JPrimitiveInt* lineNumber);

            string toString();

            virtual ~JStackTraceElement();
        };
    }
}


#endif // JSTACKTRACEELEMENT_H
