#ifndef QOBJECTAWARE_H
#define QOBJECTAWARE_H

#include <QObject>
#include <iostream>
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT QObjectAware{
            public:
                virtual void takeOwner()=0;
                virtual void releaseOwner()=0;
                virtual QObject* getQObject()=0;
        };
    }
}

#endif // QOBJECTAWARE_H
