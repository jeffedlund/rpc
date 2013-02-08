#ifndef JLANG_H
#define JLANG_H

#include "JClassNotFoundException.h"
#include "JError.h"
#include "JException.h"
#include "JIllegalArgumentException.h"
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
#include "JPrimitiveShort.h"
#include "JShort.h"
#include "JStackTraceElement.h"
#include "JString.h"
#include "JIllegalStateException.h"
#include "JClassCastException.h"

static int LANG_CLASSES_SIZE = 39;

static JClass* LANG_CLASSES[] = {
    JClassCastException::getClazz(),
    JClassNotFoundException::getClazz(),
    JError::getClazz(),
    JException::getClazz(),
    JIllegalArgumentException::getClazz(),
    JIllegalStateException::getClazz(),
    JIndexOutOfBoundsException::getClazz(),
    JInstantiationException::getClazz(),
    JInternalError::getClazz(),
    JNoSuchFieldException::getClazz(),
    JNoSuchMethodException::getClazz(),
    JNullPointerException::getClazz(),
    JRuntimeException::getClazz(),
    JThrowable::getClazz(),
    JUnsupportedOperationException::getClazz(),
    JVirtualMachineError::getClazz(),
    JBoolean::getClazz(),
    JByte::getClazz(),
    JChar::getClazz(),
    JClass::getClazz(),
    JClassLoader::getClazz(),
    JDouble::getClazz(),
    JEnum::getClazz(),
    JFloat::getClazz(),
    JInteger::getClazz(),
    JLong::getClazz(),
    JNumber::getClazz(),
    JObject::getClazz(),
    JPrimitiveBoolean::getClazz(),
    JPrimitiveByte::getClazz(),
    JPrimitiveChar::getClazz(),
    JPrimitiveDouble::getClazz(),
    JPrimitiveFloat::getClazz(),
    JPrimitiveInt::getClazz(),
    JPrimitiveLong::getClazz(),
    JPrimitiveShort::getClazz(),
    JShort::getClazz(),
    JStackTraceElement::getClazz(),
    JString::getClazz()
};

#endif // JLANG_H
