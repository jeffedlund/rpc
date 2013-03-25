#ifndef JCOMPARATOR_H
#define JCOMPARATOR_H

#include "JObject.h"
#include "JInterface.h"
#include "JCPP.h"
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        class JCPP_LIBRARY_EXPORT JComparator : public JInterface{
        public:
            static JClass* getClazz();
            virtual jint compare(JObject* o1,JObject* o2)=0;
            virtual jbool equals(JObject* o)=0;
            virtual ~JComparator();
        };
    }
}
#endif // JCOMPARATOR_H
