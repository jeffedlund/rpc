#ifndef JCOLLECTION_H
#define JCOLLECTION_H

#include "JInterface.h"
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        class JCollection : public JInterface{
        public:
            static JClass* getClazz();
        };
    }
}

#endif // JCOLLECTION_H
