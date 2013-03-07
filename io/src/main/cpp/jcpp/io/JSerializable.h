#ifndef JSERIALIZABLE_H
#define JSERIALIZABLE_H

#include "JObject.h"
#include "JClass.h"
#include "JInterface.h"
#include "JCPP.h"
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JSerializable : public JInterface{
        protected:
            JSerializable();
        public:

            static JClass* getClazz();
            virtual ~JSerializable();
        };
    }
}

#endif // JSERIALIZABLE_H
