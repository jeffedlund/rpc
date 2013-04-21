#include "JLANG.h"
#include "JREFLECT.h"
#include "Object.h"

namespace jcpp{
    namespace lang{
        JLANG::JLANG():JPackage("jcpp.lang",JPackage::getClazz()){//better class
            Object::init();
            classes->push_back(JArrayIndexOutOfBoundsException::getClazz());
            classes->push_back(JCloneNotSupportedException::getClazz());
            classes->push_back(JClassCastException::getClazz());
            classes->push_back(JClassNotFoundException::getClazz());
            classes->push_back(JError::getClazz());
            classes->push_back(JException::getClazz());
            classes->push_back(JIllegalArgumentException::getClazz());
            classes->push_back(JIllegalStateException::getClazz());
            classes->push_back(JIndexOutOfBoundsException::getClazz());
            classes->push_back(JInstantiationException::getClazz());
            classes->push_back(JInternalError::getClazz());
            classes->push_back(JNoSuchFieldException::getClazz());
            classes->push_back(JNoSuchMethodException::getClazz());
            classes->push_back(JNullPointerException::getClazz());
            classes->push_back(JRuntimeException::getClazz());
            classes->push_back(JThrowable::getClazz());
            classes->push_back(JUnsupportedOperationException::getClazz());
            classes->push_back(JVirtualMachineError::getClazz());
            classes->push_back(JAbstractStringBuilder::getClazz());
            classes->push_back(JAppendable::getClazz());
            classes->push_back(JAutoCloseable::getClazz());
            classes->push_back(JBoolean::getClazz());
            classes->push_back(JByte::getClazz());
            classes->push_back(JChar::getClazz());
            classes->push_back(JCharSequence::getClazz());
            classes->push_back(JClass::getClazz());
            classes->push_back(JClassLoader::getClazz());
            classes->push_back(JCloneable::getClazz());
            classes->push_back(JComparable::getClazz());
            classes->push_back(JDouble::getClazz());
            classes->push_back(JEnum::getClazz());
            classes->push_back(JFloat::getClazz());
            classes->push_back(JInteger::getClazz());
            classes->push_back(JInterface::getClazz());
            classes->push_back(JIterable::getClazz());
            classes->push_back(JLong::getClazz());
            classes->push_back(JNumber::getClazz());
            classes->push_back(JObject::getClazz());
            classes->push_back(JPrimitiveBoolean::getClazz());
            classes->push_back(JPrimitiveByte::getClazz());
            classes->push_back(JPrimitiveChar::getClazz());
            classes->push_back(JPrimitiveDouble::getClazz());
            classes->push_back(JPrimitiveFloat::getClazz());
            classes->push_back(JPrimitiveInt::getClazz());
            classes->push_back(JPrimitiveLong::getClazz());
            classes->push_back(JPrimitiveShort::getClazz());
            classes->push_back(JReadable::getClazz());
            classes->push_back(JRunnable::getClazz());
            classes->push_back(JShort::getClazz());
            classes->push_back(JStackTraceElement::getClazz());
            classes->push_back(JString::getClazz());
            classes->push_back(JStringBuffer::getClazz());
            classes->push_back(JStringBuilder::getClazz());
            classes->push_back(JSystem::getClazz());
            classes->push_back(JThread::getClazz());
            classes->push_back(JThreadLocal::getClazz());
            classes->push_back(JVoid::getClazz());
        }

        JPackage* JLANG::getSuperPackage(){
            return JCPP_PACKAGE::getPackage();
        }

        vector<JPackage*>* JLANG::getPackages(){
            if (packages->size()==0){
                packages->push_back(JREFLECT::getPackage());
            }
            return packages;
        }

        static JLANG* jlang=NULL;

        JLANG* JLANG::getPackage(){
            if (jlang==NULL){
                jlang=new JLANG();
            }
            return jlang;
        }

        JLANG::~JLANG(){
        }
    }
}
