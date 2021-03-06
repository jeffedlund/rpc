#ifndef JLANG_H
#define JLANG_H

#include "JArrayIndexOutOfBoundsException.h"
#include "JClassCastException.h"
#include "JClassNotFoundException.h"
#include "JCloneNotSupportedException.h"
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
#include "JAbstractStringBuilder.h"
#include "JAppendable.h"
#include "JAutoCloseable.h"
#include "JBoolean.h"
#include "JByte.h"
#include "JChar.h"
#include "JCharSequence.h"
#include "JClass.h"
#include "JClassLoader.h"
#include "JCloneable.h"
#include "JComparable.h"
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
#include "JReadable.h"
#include "JShort.h"
#include "JStackTraceElement.h"
#include "JString.h"
#include "JStringBuffer.h"
#include "JStringBuilder.h"
#include "JThread.h"
#include "JThreadLocal.h"
#include "JIllegalStateException.h"
#include "JVoid.h"
#include "JPackage.h"
#include "JSystem.h"
#include "JCPP_PACKAGE.h"
#include "JCPP.h"
using namespace jcpp::lang::reflect;
using namespace jcpp;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JLANG : public JPackage{
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
