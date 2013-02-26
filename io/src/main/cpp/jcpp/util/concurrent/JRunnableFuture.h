#ifndef JRUNNABLEFUTURE_H
#define JRUNNABLEFUTURE_H

#include "JInterface.h"
#include "JClass.h"
#include "JRunnable.h"
#include "JFuture.h"
using namespace std;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace concurrent{
            class JRunnableFuture : public JRunnable, public JFuture{

            public:
                static JClass* getClazz();
                virtual ~JRunnableFuture();
            };
        }
    }
}

#endif // JRUNNABLEFUTURE_H
