#ifndef JTHROWABLETEST_H
#define JTHROWABLETEST_H

#include "JThrowable.h"
#include "JTest.h"


class JThrowableTest : public JTest{
public:
    JThrowableTest();

    virtual string getFileName();

    virtual JThrowable* createFirstCause();

    virtual JThrowable* createSecondCause();

    virtual string getThrowableClassName();

    JObject* testReflect();
};


#endif
