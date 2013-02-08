#ifndef JTHROWABLE_H
#define JTHROWABLE_H


#include "JObject.h"
#include "JStackTraceElement.h"
#include "JString.h"
#include "JPrimitiveArray.h"
#include "JSerializable.h"
using namespace std;

class JThrowable: public JObject, public JSerializable {
protected:
    JString* message;
    JThrowable* cause;
    JPrimitiveArray* stackTrace;
    JThrowable(JClass* _class);

public:
    JThrowable();
    JThrowable(string message);
    JThrowable(JString* message);
    JThrowable(string, JThrowable *cause);
    JThrowable(JString*, JThrowable *cause);
    bool operator==(JThrowable &other);

    static JClass* getClazz();

    JThrowable *getCause();
    void setCause(JThrowable* throwable);

    void setMessage(JString* message);
    JString* getMessage();

    JPrimitiveArray* getStackTrace();
    void setStackTrace(JPrimitiveArray* stackTrace);

    void printStackTrace(ostream* os);

    string toString();

    ~JThrowable();
};

#endif // JTHROWABLE_H
