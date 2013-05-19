#ifndef JTHROWABLE_H
#define JTHROWABLE_H

#include "JObject.h"
#include "JString.h"
#include "JStackTraceElement.h"
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
            JThrowable(JString message);
            JThrowable(JString message, JThrowable* cause);
            static JClass* getClazz();
            virtual void setCause(JThrowable* throwable);
            virtual JThrowable *getCause();
            virtual void setMessage(JString* message);
            virtual JString* getMessage();
            virtual void setStackTrace(JPrimitiveArray* stackTrace);
            virtual JPrimitiveArray* getStackTrace();
            virtual JList* getSuppressedExceptions();
            virtual void addSuppressedException(JThrowable* t);
            virtual void printStackTrace(ostream* os);
            virtual void printStackTrace();
            virtual jbool equals(JObject* other);
            virtual JString toString();
            virtual ~JThrowable();
        };
    }
}

#endif // JTHROWABLE_H
