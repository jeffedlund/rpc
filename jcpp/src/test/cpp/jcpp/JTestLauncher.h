#ifndef JTESTLAUNCHER_H
#define JTESTLAUNCHER_H

#include "JObject.h"
#include "JClass.h"
#include "JPrimitiveArray.h"
using namespace jcpp::lang;

namespace jcpp{
    class JTestLauncher : public JObject{
    public:
        JTestLauncher();
        static JClass* getClazz();
        static JObject* main(JPrimitiveArray* argv);
        virtual ~JTestLauncher();
    };
}

#endif // JTESTLAUNCHER_H
