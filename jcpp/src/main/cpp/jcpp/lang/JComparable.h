#ifndef JCOMPARABLE_H
#define JCOMPARABLE_H

#include "Object.h"
#include "JInterface.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JClass;
        class JObject;

        class JCPP_LIBRARY_EXPORT JComparable : public JInterface{
        public:
            static JClass* getClazz();
            virtual jint compareTo(JObject*)=0;
            virtual ~JComparable();
        };
    }
}

#endif // JCOMPARABLE_H
