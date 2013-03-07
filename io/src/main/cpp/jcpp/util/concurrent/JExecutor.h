#ifndef JEXECUTOR_H
#define JEXECUTOR_H

#include "JInterface.h"
#include "JClass.h"
#include "JRunnable.h"
#include "JCPP.h"
using namespace std;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace concurrent{
            class JCPP_LIBRARY_EXPORT JExecutor : public JInterface{
            protected:

            public:
                static JClass* getClazz();
                virtual void execute(JRunnable* command)=0;
                virtual ~JExecutor();
            };
        }
    }
}

#endif // JEXECUTOR_H
