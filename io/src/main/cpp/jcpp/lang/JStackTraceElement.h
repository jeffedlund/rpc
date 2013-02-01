#ifndef JSTACKTRACEELEMENT_H
#define JSTACKTRACEELEMENT_H

#include "JObject.h"
using namespace std;

class JStackTraceElement: public JObject {
private:
    string declaringClass;
    string methodName;
    string fileName;
    int lineNumber;

public:
    JStackTraceElement();

    static JClass* getClazz();

    string getDeclaringClass();

    void setDeclaringClass(string declaringClass);

    string getMethodName();

    void setMethodName(string methodName);

    string getFileName();

    void setFileName(string fileName);

    int getLineNumber();

    void setLineNumber(int lineNumber);

    string toString();

    ~JStackTraceElement();
};


#endif // JSTACKTRACEELEMENT_H
