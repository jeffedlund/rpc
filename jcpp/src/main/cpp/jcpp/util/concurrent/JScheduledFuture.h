#ifndef JSCHEDULEDFUTURE_H
#define JSCHEDULEDFUTURE_H

#include "JInterface.h"
#include "JClass.h"
#include "JObject.h"
#include "JFuture.h"
#include "JDelayed.h"
#include "JCPP.h"
using namespace std;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace concurrent{
            class JCPP_LIBRARY_EXPORT JScheduledFuture : public JFuture, public JDelayed{

            public:
                static JClass* getClazz();
                virtual ~JScheduledFuture();
            };
        }
    }
}


#endif // JSCHEDULEDFUTURE_H
