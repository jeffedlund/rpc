#ifndef JCLASSNOTFOUNDEXCEPTION_H
#define JCLASSNOTFOUNDEXCEPTION_H

#include "JException.h"
#include "JClass.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JClassNotFoundException : public JException{
        public:
            JClassNotFoundException();
            JClassNotFoundException(string message);

            static JClass* getClazz();
        };
    }
}

#endif // JCLASSNOTFOUNDEXCEPTION_H
