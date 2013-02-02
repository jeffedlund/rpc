#ifndef JERROR_H
#define JERROR_H

#include "JObject.h"
#include "JThrowable.h"
using namespace std;

class JError : public JThrowable {
protected:
    JError(JClass* _class);

public:
    JError();
    JError(string message);
    JError(string message, JThrowable *cause);

    static JClass* getClazz();

    ~JError();
};

#endif // JERROR_H
