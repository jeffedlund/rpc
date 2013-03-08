#ifndef JCLASSNOTFOUNDEXCEPTION_H
#define JCLASSNOTFOUNDEXCEPTION_H

#include "JException.h"
#include "JClass.h"
using namespace std;
#include"JCPP.h"

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JClassNotFoundException : public JException{
        public:
            JClassNotFoundException();
            JClassNotFoundException(string message);

            static JClass* getClazz();
            virtual ~JClassNotFoundException();
        };
    }
}

#endif // JCLASSNOTFOUNDEXCEPTION_H
