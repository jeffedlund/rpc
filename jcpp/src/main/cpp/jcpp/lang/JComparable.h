#ifndef JCOMPARABLE_H
#define JCOMPARABLE_H

#include "JInterface.h"
#include "JClass.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JComparable : public JInterface{
        protected:

        public:
            static JClass* getClazz();
            virtual jint compareTo(JObject*)=0;
            virtual ~JComparable();
        };
    }
}

#endif // JCOMPARABLE_H