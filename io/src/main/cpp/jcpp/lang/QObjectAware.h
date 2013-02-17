#ifndef QOBJECTAWARE_H
#define QOBJECTAWARE_H

#include <QObject>
#include <iostream>
using namespace std;

namespace jcpp{
    namespace lang{
        class QObjectAware{
            public:
                virtual QObject* getQObject()=0;
        };
    }
}

#endif // QOBJECTAWARE_H
