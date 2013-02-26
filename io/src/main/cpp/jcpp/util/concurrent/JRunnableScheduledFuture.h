#ifndef JRUNNABLESCHEDULEDFUTURE_H
#define JRUNNABLESCHEDULEDFUTURE_H

#include "JInterface.h"
#include "JClass.h"
#include "JObject.h"
#include "JFuture.h"
#include "JDelayed.h"
#include "JRunnableFuture.h"
#include "JScheduledFuture.h"
using namespace std;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace concurrent{
            class JRunnableScheduledFuture : public JRunnableFuture, public JScheduledFuture{

            public:
                static JClass* getClazz();
                virtual bool isPeriodic()=0;
                virtual ~JRunnableScheduledFuture();
            };
        }
    }
}

#endif // JRUNNABLESCHEDULEDFUTURE_H
