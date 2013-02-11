#ifndef JTEST_H
#define JTEST_H

#include "assert.h"
#include "JIO.h"
#include "JLang.h"
#include "JUtil.h"
#include "JObject.h"
#include <QtGlobal>
#include <QFile>
#include <QString>
#include <QDataStream>

namespace jcpp{
    class JTest{
    public :

        virtual string getFileName()=0;

        virtual JObject* testReflect()=0;

        void testWrite(JObject* object);

        JObject* testRead();

        void test();
    };
}

#endif // JTEST_H
