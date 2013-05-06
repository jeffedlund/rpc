#ifndef JCLOSEABLE_H
#define JCLOSEABLE_H

#include "JAutoCloseable.h"
using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JCloseable : public JAutoCloseable  {
        public:
            static JClass* getClazz();
            virtual void close()=0;
            virtual ~JCloseable();
        };
    }
}

#endif // JCLOSEABLE_H
