#ifndef JREFLECT_H
#define JREFLECT_H

#include "JField.h"
#include "JInvocationHandler.h"
#include "JMethod.h"
#include "JProxy.h"
#include "JPackage.h"
using namespace jcpp;

namespace jcpp{
    namespace lang{
        namespace reflect{
            class JREFLECT : public JPackage{
            protected:
                JREFLECT();

            public:
                JPackage* getSuperPackage();

                vector<JPackage*>* getPackages();

                static JREFLECT* getPackage();

                virtual ~JREFLECT();
            };
        }
    }
}


#endif // JREFLECT_H
