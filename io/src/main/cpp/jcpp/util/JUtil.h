#ifndef JUTIL_H
#define JUTIL_H

#include "JArrayList.h"
#include "JCollection.h"
#include "JHashtable.h"

static int UTL_CLASSES_SIZE = 1;

static JClass* UTIL_CLASSES[] = {
    JArrayList::getClazz()
    //TODO JCollection::
    //TODO JHashtable::getC
};

#endif // JUTIL_H
