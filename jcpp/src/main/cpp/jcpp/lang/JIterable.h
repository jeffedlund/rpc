#ifndef JITERABLE_H
#define JITERABLE_H

#include "JInterface.h"
#include "JClass.h"
#include "JIterator.h"
#include "JObject.h"
using namespace std;
using namespace jcpp::util;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JIterable : public JInterface{
        public:
            static JClass* getClazz();
            virtual JIterator* iterator()=0;
            virtual ~JIterable();
        };
    }
}

#endif // JITERABLE_H
