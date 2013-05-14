#ifndef JRUNNABLESCHEDULEDFUTURE_H
#define JRUNNABLESCHEDULEDFUTURE_H

#include "JInterface.h"
#include "JClass.h"
#include "JObject.h"
#include "JFuture.h"
#include "JDelayed.h"
#include "JRunnableFuture.h"
#include "JScheduledFuture.h"
#include "JCPP.h"
using namespace std;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace concurrent{
            class JCPP_LIBRARY_EXPORT JRunnableScheduledFuture : public JRunnableFuture, public JScheduledFuture{
            public:
                static JClass* getClazz();
                virtual jbool isPeriodic()=0;
                virtual ~JRunnableScheduledFuture();
            };
        }
    }
}

#endif // JRUNNABLESCHEDULEDFUTURE_H
