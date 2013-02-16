#ifndef JRUNNABLE_H
#define JRUNNABLE_H

#include "JInterface.h"
#include "JClass.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JRunnable : public JInterface{
        protected:

        public:
            static JClass* getClazz();
            virtual void run()=0;
        };
    }
}

#endif // JRUNNABLE_H
