#ifndef JERROR_H
#define JERROR_H

#include "JObject.h"
#include "JThrowable.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JError : public JThrowable {
        protected:
            JError(JClass* _class);

        public:
            JError();
            JError(string message);
            JError(string message, JThrowable *cause);

            static JClass* getClazz();

            virtual ~JError();
        };
    }
}

#endif // JERROR_H
