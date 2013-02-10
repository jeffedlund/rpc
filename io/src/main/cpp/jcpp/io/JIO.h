#ifndef JIO_H
#define JIO_H

#include "JDataInputStream.h"
#include "JDataOutputStream.h"
#include "JEOFException.h"
#include "JExternalizable.h"
#include "JInputStream.h"
#include "JInvalidClassException.h"
#include "JIOException.h"
#include "JNotActiveException.h"
#include "JNotSerializableException.h"
#include "JObjectInputStream.h"
#include "JObjectOutputStream.h"
#include "JObjectStreamClass.h"
#include "JObjectStreamException.h"
#include "JOptionalDataException.h"
#include "JOutputStream.h"
#include "JSerializable.h"
#include "JStreamCorruptedException.h"
#include "JUTFDataFormatException.h"
#include "QtDataInputStream.h"
#include "QtDataOutputStream.h"
using namespace std;

//TODO define h and cpp file that contains all that + metadata on packages ...
static int IO_CLASSES_SIZE = 20;

static JClass* IO_CLASSES[] = {
    JDataInputStream::getClazz(),
    JDataOutputStream::getClazz(),
    JEOFException::getClazz(),
    JExternalizable::getClazz(),
    JInputStream::getClazz(),
    JInvalidClassException::getClazz(),
    JIOException::getClazz(),
    JNotActiveException::getClazz(),
    JNotSerializableException::getClazz(),
    JObjectInputStream::getClazz(),
    JObjectOutputStream::getClazz(),
    JObjectStreamClass::getClazz(),
    JObjectStreamException::getClazz(),
    JOptionalDataException::getClazz(),
    JOutputStream::getClazz(),
    JSerializable::getClazz(),
    JStreamCorruptedException::getClazz(),
    JUTFDataFormatException::getClazz(),
    QtDataInputStream::getClazz(),
    QtDataOutputStream::getClazz()
};

#endif // JIO_H
