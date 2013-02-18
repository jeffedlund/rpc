#ifndef JFUTURE_H
#define JFUTURE_H

#include "JInterface.h"
#include "JClass.h"
#include "JObject.h"
#include "JRunnable.h"
using namespace std;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace concurrent{
            class JFuture : public JInterface{

            public:
                static JClass* getClazz();
                virtual bool cancel()=0;
                virtual bool isCancelled()=0;
                virtual bool isDone()=0;
                virtual JObject* get()=0;
            };
        }
    }
}

#endif // JFUTURE_H
