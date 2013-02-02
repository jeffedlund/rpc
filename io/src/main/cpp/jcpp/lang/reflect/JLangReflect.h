#ifndef JLANGREFLECT_H
#define JLANGREFLECT_H

#include "JField.h"
#include "JInvocationHandler.h"
#include "JMethod.h"
#include "JProxy.h"

static int LANG_REFLECT_CLASSES_SIZE=4;

static JClass* LANG_REFLECT_CLASSES[] = {
    JField::getClazz(),
    JInvocationHandler::getClazz(),
    JMethod::getClazz(),
    JProxy::getClazz()
};

#endif // JLANGREFLECT_H
