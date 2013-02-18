#ifndef JSCHEDULEDFUTURE_H
#define JSCHEDULEDFUTURE_H

#include "JInterface.h"
#include "JClass.h"
#include "JObject.h"
#include "JFuture.h"
#include "JDelayed.h"
using namespace std;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace concurrent{
            class JScheduledFuture : public JFuture, public JDelayed{

            public:
                static JClass* getClazz();
            };
        }
    }
}


#endif // JSCHEDULEDFUTURE_H
