#ifndef JERRORTEST_H
#define JERRORTEST_H

#include "JThrowableTest.h"
#include "JError.h"


class JErrorTest : public JThrowableTest{
public:
    JErrorTest();

    virtual string getFileName();

    virtual JThrowable* createFirstCause();

    virtual JThrowable* createSecondCause();

    virtual string getThrowableClassName();
};


#endif // JERRORTEST_H
