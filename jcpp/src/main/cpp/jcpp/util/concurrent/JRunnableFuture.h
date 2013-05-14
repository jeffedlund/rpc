#ifndef JRUNNABLEFUTURE_H
#define JRUNNABLEFUTURE_H

#include "JInterface.h"
#include "JClass.h"
#include "JRunnable.h"
#include "JFuture.h"
#include "JCPP.h"
using namespace std;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace concurrent{
            class JCPP_LIBRARY_EXPORT JRunnableFuture : public JRunnable, public JFuture{
            public:
                static JClass* getClazz();
                virtual ~JRunnableFuture();
            };
        }
    }
}

#endif // JRUNNABLEFUTURE_H
