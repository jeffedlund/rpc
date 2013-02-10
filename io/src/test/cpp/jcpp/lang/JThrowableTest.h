#ifndef JTHROWABLETEST_H
#define JTHROWABLETEST_H

#include "JThrowable.h"
#include "JTest.h"


class JThrowableTest : public JTest{
public:
    JThrowableTest();

    string getFileName();

    JObject* testReflect();
};


#endif
