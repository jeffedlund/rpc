#ifndef JSERIALIZABLE_H
#define JSERIALIZABLE_H

#include "JObject.h"
#include "JClass.h"
#include "JInterface.h"
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{
        class JSerializable : public JInterface{
        protected:
            JSerializable();
        public:

            static JClass* getClazz();
        };
    }
}

#endif // JSERIALIZABLE_H
