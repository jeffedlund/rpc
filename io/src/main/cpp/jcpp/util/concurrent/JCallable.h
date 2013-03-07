#ifndef JCALLABLE_H
#define JCALLABLE_H

#include "JInterface.h"
#include "JClass.h"
#include "JRunnable.h"
#include "JCPP.h"
using namespace std;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace concurrent{
            class JCPP_LIBRARY_EXPORT JCallable : public JInterface{

            public:
                static JClass* getClazz();
                virtual JObject* call()=0;
                virtual ~JCallable();
            };
        }
    }
}

#endif // JCALLABLE_H
