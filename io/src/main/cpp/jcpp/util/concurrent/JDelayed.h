#ifndef JDELAYED_H
#define JDELAYED_H

#include "JInterface.h"
#include "JClass.h"
#include "JObject.h"
#include "JRunnable.h"
#include "JCPP.h"
using namespace std;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace concurrent{
            class JCPP_LIBRARY_EXPORT JDelayed : public JInterface{

            public:
                static JClass* getClazz();
                virtual jlong getDelay()=0;
                virtual ~JDelayed();
            };
        }
    }
}

#endif // JDELAYED_H
