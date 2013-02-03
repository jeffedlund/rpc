#ifndef JIO_H
#define JIO_H

#include "JDataInputStream.h"
#include "JEOFException.h"
#include "JInputStream.h"
#include "JInvalidClassException.h"
#include "JIOException.h"
#include "JNotActiveException.h"
#include "JObjectInputStream.h"
#include "JObjectStreamClass.h"
#include "JObjectStreamException.h"
#include "JOptionalDataException.h"
#include "JSerializable.h"
#include "JStreamCorruptedException.h"
#include "JUTFDataFormatException.h"
#include "QtDataInputStream.h"
using namespace std;

static int IO_CLASSES_SIZE = 14;

static JClass* IO_CLASSES[] = {
    JDataInputStream::getClazz(),
    JEOFException::getClazz(),
    JInputStream::getClazz(),
    JInvalidClassException::getClazz(),
    JIOException::getClazz(),
    JNotActiveException::getClazz(),
    JObjectInputStream::getClazz(),
    JObjectStreamClass::getClazz(),
    JObjectStreamException::getClazz(),
    JOptionalDataException::getClazz(),
    JSerializable::getClazz(),
    JStreamCorruptedException::getClazz(),
    JUTFDataFormatException::getClazz(),
    QtDataInputStream::getClazz()
};

#endif // JIO_H
