#ifndef JTHROWABLE_H
#define JTHROWABLE_H


#include "JObject.h"
#include "JStackTraceElement.h"
using namespace std;

class JThrowable: public JObject {
protected:
    string message;
    JThrowable* cause;
    vector<JStackTraceElement*>* stackTrace;
    JThrowable(JClass* _class);

public:
    JThrowable();
    JThrowable(string message);
    JThrowable(string, JThrowable *cause);

    static JClass* getClazz();

    JThrowable *getCause();
    void setCause(JThrowable* throwable);

    void setMessage(string message);
    string getMessage();

    vector<JStackTraceElement*>* getStackTrace();
    void setStackTrace(vector<JStackTraceElement*>* stackTrace);

    ~JThrowable();
};

#endif // JTHROWABLE_H
