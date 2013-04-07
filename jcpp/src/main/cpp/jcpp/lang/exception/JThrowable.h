#ifndef JTHROWABLE_H
#define JTHROWABLE_H

#include "JObject.h"
#include "JStackTraceElement.h"
#include "JString.h"
#include "JPrimitiveArray.h"
#include "JSerializable.h"
#include "JCPP.h"
#include "JList.h"
using namespace std;
using namespace jcpp::util;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JThrowable: public JObject, public JSerializable {
        protected:
            JString* message;
            JThrowable* cause;
            JPrimitiveArray* stackTrace;
            JList* suppressedExceptions;
            JThrowable(JClass* _class);
            friend class JThrowableClass;

        public:
            JThrowable();
            JThrowable(string message);
            JThrowable(JString* message);
            JThrowable(string, JThrowable *cause);
            JThrowable(JString*, JThrowable *cause);
            static JClass* getClazz();
            JThrowable *getCause();
            void setCause(JThrowable* throwable);
            void setMessage(JString* message);
            JString* getMessage();
            JPrimitiveArray* getStackTrace();
            void setStackTrace(JPrimitiveArray* stackTrace);
            void printStackTrace(ostream* os);
            JList* getSuppressedExceptions();
            void addSuppressedException(JThrowable* t);
            virtual bool equals(JObject* other);
            virtual string toString();
            virtual ~JThrowable();
        };
    }
}

#endif // JTHROWABLE_H
