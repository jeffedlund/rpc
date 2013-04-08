#ifndef JAUTOCLOSEABLE_H
#define JAUTOCLOSEABLE_H

#include "JInterface.h"
#include "JClass.h"
#include "JObject.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JAutoCloseable : public JInterface{
        protected:

        public:
            static JClass* getClazz();
            virtual void close()=0;
            virtual ~JAutoCloseable();
        };
    }
}
#endif // JAUTOCLOSEABLE_H
