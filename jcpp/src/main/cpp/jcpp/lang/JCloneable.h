#ifndef JCLONEABLE_H
#define JCLONEABLE_H

#include "JInterface.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JClass;
        class JCPP_LIBRARY_EXPORT JCloneable : public JInterface{
        protected:

        public:
            static JClass* getClazz();
            virtual ~JCloneable();
        };
    }
}

#endif // JCLONEABLE_H
