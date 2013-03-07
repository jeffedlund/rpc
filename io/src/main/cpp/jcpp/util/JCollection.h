#ifndef JCOLLECTION_H
#define JCOLLECTION_H

#include "JInterface.h"
#include "JCPP.h"
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        class JCPP_LIBRARY_EXPORT JCollection : public JInterface{
        public:
            static JClass* getClazz();
            virtual ~JCollection();
        };
    }
}

#endif // JCOLLECTION_H
