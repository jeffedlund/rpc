#ifndef JCOLLECTIONS_H
#define JCOLLECTIONS_H

#include "JInterface.h"
#include "JIterable.h"
#include "JList.h"
#include "JCPP.h"
#include "JEnumeration.h"
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        class JCPP_LIBRARY_EXPORT JCollections : public JObject{
        public:
            static JClass* getClazz();
            static JList* synchronizedList(JList* list);
            static JIterator* emptyIterator();
            static JEnumeration* emptyEnumeration();
            virtual ~JCollections();
        };
    }
}

#endif // JCOLLECTIONS_H
