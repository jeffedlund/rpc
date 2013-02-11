#ifndef JCLASSBUILDER_H
#define JCLASSBUILDER_H

#include "JObject.h"
#include "JClass.h"
using namespace  std;

namespace jcpp{
    namespace lang{
        class JClassBuilder {

        public:
            virtual vector<JClass*>* getClasses()=0;
        };
    }
}

#endif // JCLASSBUILDER_H
