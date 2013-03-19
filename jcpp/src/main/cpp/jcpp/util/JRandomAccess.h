#ifndef JRANDOMACCESS_H
#define JRANDOMACCESS_H

#include "JObject.h"
#include "JInterface.h"
#include "JCPP.h"
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        class JCPP_LIBRARY_EXPORT JRandomAccess : public JInterface{
        public:
            static JClass* getClazz();
            virtual ~JRandomAccess();
        };
    }
}
#endif // JRANDOMACCESS_H
