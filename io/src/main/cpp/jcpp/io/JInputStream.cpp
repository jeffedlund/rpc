#include "JInputStream.h"

JInputStream::JInputStream(){
}

qint64 JInputStream::available() {
    return 0;
}

bool JInputStream::waitForReadyRead(int i) {
    return false;
}

qint32 JInputStream::read() {
    return 0;
}

qint32 JInputStream::read(qint8 b[], int off, int len) {
    return 0;
}

qint8 JInputStream::peekByte() {
    return 0;
}

qint8 JInputStream::readByte() {
    return 0;
}

qint16 JInputStream::readShort() {
    return 0;
}

quint16 JInputStream::readUnsignedShort() {
    return 0;
}

qint32 JInputStream::readInt() {
    return 0;
}

qint64 JInputStream::readLong() {
    return 0;
}

float JInputStream::readFloat() {
    return 0;
}

double JInputStream::readDouble() {
    return 0;
}

char JInputStream::readChar() {
    return 0;
}

bool JInputStream::readBool() {
    return 0;
}

void JInputStream::close() {
}

JInputStream::~JInputStream() {
}
