#include "QtDataInputStream.h"

QtDataInputStream::QtDataInputStream(QDataStream* in)
{
    this->in = in;
}

QDataStream* QtDataInputStream::getStream(){
    return this->in;
}

qint64 QtDataInputStream::available() {
    return in->device()->bytesAvailable();
}

bool QtDataInputStream::waitForReadyRead(int i) {
    return in->device()->waitForReadyRead(i);
}

qint32 QtDataInputStream::read() {
    return readByte();
}

qint32 QtDataInputStream::read(qint8 b[], int off, int len) {
    if (available() < len) {
        waitForReadyRead(-1);
    }
    return in->readRawData((char*)b+off,len);
}

qint8 QtDataInputStream::peekByte() {
    qint8 b;
    while (available() < 1) {
        waitForReadyRead(-1);
    }
    in->device()->peek((char*) &b,1);
    return b;
}

qint8 QtDataInputStream::readByte() {
    qint8 b;
    while (available() < 1) {
        waitForReadyRead(-1);
    }
    (*in)>>b;
    return b;
}

qint16 QtDataInputStream::readShort() {
    qint16 s;
    while (available() < 2) {
        waitForReadyRead(-1);
    }
    (*in)>>s;
    return s;
}

quint16 QtDataInputStream::readUnsignedShort() {
    quint16 us;
    while (available() < 2) {
        waitForReadyRead(-1);
    }
    (*in)>>us;
    return us;
}

qint32 QtDataInputStream::readInt() {
    qint32 i;
    while (available() < 4) {
        waitForReadyRead(-1);
    }
    (*in) >> i;
    return i;
}

qint64 QtDataInputStream::readLong() {
    qint64 l;
    while (available() < 8) {
        waitForReadyRead(-1);
    }
    (*in) >> l;
    return l;
}

// In versions Qt 4.5 and before, the floating point precision
// is implicitly dealt with by the corresponding operator<<()
// and operator>>().
// In versions Qt 4.6 and after, the floating point precision
// has to be set explicitly. It is double by default.
float QtDataInputStream::readFloat() {
    int ver = in->version();
    in->setVersion(QDataStream::Qt_4_5);
    float f;
    while (available() < 4) {
        waitForReadyRead(-1);
    }
    (*in) >> f;
    in->setVersion(ver);
    return f;
}

double QtDataInputStream::readDouble() {
    double d;
    while (available() < 8) {
        waitForReadyRead(-1);
    }
    (*in)>>d;
    return d;
}

char QtDataInputStream::readChar() {
    qint8 c;
    while (available() < 2) {
        waitForReadyRead(-1);
    }
    (*in) >> c;
    (*in) >> c;
    return c;
}

bool QtDataInputStream::readBool() {
    bool b;
    while (available() < 1) {
        waitForReadyRead(-1);
    }
    (*in)>>b;
    return b;
}

void QtDataInputStream::close(){
    this->in->setDevice(0);
}

QtDataInputStream::~QtDataInputStream() {
}
