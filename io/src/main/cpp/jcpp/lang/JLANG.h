#ifndef JLANG_H
#define JLANG_H

#include "JClassCastException.h"
#include "JClassNotFoundException.h"
#include "JError.h"
#include "JException.h"
#include "JIllegalArgumentException.h"
#include "JIllegalStateException.h"
#include "JIndexOutOfBoundsException.h"
#include "JInstantiationException.h"
#include "JInternalError.h"
#include "JNoSuchFieldException.h"
#include "JNoSuchMethodException.h"
#include "JNullPointerException.h"
#include "JRuntimeException.h"
#include "JThrowable.h"
#include "JUnsupportedOperationException.h"
#include "JVirtualMachineError.h"
#include "JBoolean.h"
#include "JByte.h"
#include "JChar.h"
#include "JClass.h"
#include "JClassLoader.h"
#include "JDouble.h"
#include "JEnum.h"
#include "JFloat.h"
#include "JInteger.h"
#include "JLong.h"
#include "JNumber.h"
#include "JObject.h"
#include "JPrimitiveArray.h"
#include "JPrimitiveBoolean.h"
#include "JPrimitiveByte.h"
#include "JPrimitiveChar.h"
#include "JPrimitiveDouble.h"
#include "JPrimitiveFloat.h"
#include "JPrimitiveInt.h"
#include "JPrimitiveLong.h"
#include "JRunnable.h"
#include "JPrimitiveShort.h"
#include "JShort.h"
#include "JStackTraceElement.h"
#include "JString.h"
#include "JThread.h"
#include "JIllegalStateException.h"
#include "JVoid.h"
#include "JPackage.h"
#include "JCPP.h"
using namespace jcpp::lang::reflect;
using namespace jcpp;

namespace jcpp{
    namespace lang{
        class JLANG : public JPackage{
        protected:
            JLANG();

        public:
            JPackage* getSuperPackage();

            vector<JPackage*>* getPackages();

            static JLANG* getPackage();

            virtual ~JLANG();
        };
    }
}
#endif // JLANG_H
