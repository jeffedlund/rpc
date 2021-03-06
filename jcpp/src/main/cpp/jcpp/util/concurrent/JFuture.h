#ifndef JFUTURE_H
#define JFUTURE_H

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
            class JCPP_LIBRARY_EXPORT JFuture : public JInterface{
            protected:
                virtual void setResult(JObject* result)=0;
            public:
                static JClass* getClazz();
                virtual jbool cancel()=0;
                virtual jbool isCancelled()=0;
                virtual jbool isDone()=0;
                virtual JObject* get()=0;
                virtual ~JFuture();
            };
        }
    }
}

#endif // JFUTURE_H
