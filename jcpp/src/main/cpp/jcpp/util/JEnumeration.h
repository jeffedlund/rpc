#ifndef JENUMERATION_H
#define JENUMERATION_H

#include "JObject.h"
#include "JInterface.h"
#include "JCPP.h"
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        class JCPP_LIBRARY_EXPORT JEnumeration : public JInterface{
        public:
            static JClass* getClazz();
            virtual jbool hasMoreElements()=0;
            virtual JObject* nextElement()=0;
            virtual ~JEnumeration();
        };
    }
}


#endif // JENUMERATION_H
