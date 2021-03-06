#ifndef JRUNNABLE_H
#define JRUNNABLE_H

#include "JInterface.h"
#include "JClass.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JRunnable : public JInterface{
        public:
            static JClass* getClazz();
            virtual void run()=0;
            virtual ~JRunnable();
        };
    }
}

#endif // JRUNNABLE_H
