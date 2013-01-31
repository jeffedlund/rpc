#include "JDataInputStream.h"
#include "JIndexOutOfBoundsException.h"
#include "JEOFException.h"
#include "JUTFDataFormatException.h"

JDataInputStream::JDataInputStream(JInputStream *in)
{
    this->in = in;
}

void JDataInputStream::readFully(qint8 b[], qint32 off, qint32 len) {
    if (len < 0)
        throw new JIndexOutOfBoundsException;
    int n = 0;
    while (n < len) {
        qint32 count = in->read(b, off + n, len - n);
        if (count < 0)
            throw new JEOFException;
        n += count;
    }
}

std::string JDataInputStream::readUTF() {
    quint16 utflen = in->readUnsignedShort();
    qint8 *bytearr = new qint8[utflen*2];
    char *chararr = new char[utflen*2+1];

    qint32 c, char2, char3;
    qint32 count = 0;
    qint32 chararr_count = 0;

    readFully(bytearr, 0, utflen);

    while (count < utflen) {
        c = (qint32) bytearr[count] & 0xff;
        if (c > 127) break;
        count++;
        chararr[chararr_count++] = (char)c;
    }

    while (count < utflen) {
        c = (qint32) bytearr[count] & 0xff;
        switch (c >> 4) {
        case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7:
            /* 0xxxxxxx*/
            count++;
            chararr[chararr_count++] = (char)c;
            break;
        case 12: case 13:
            /* 110x xxx  10xx xxx*/
            count += 2;
            if (count > utflen)
                throw new JUTFDataFormatException();
            char2 = (qint32) bytearr[count-1];
            if ((char2 & 0xC0) != 0x80)
                throw new JUTFDataFormatException;
            chararr[chararr_count++] = (char)(((c & 0x1F) << 6) | (char2 & 0x3F));
            break;
        case 14:
            /* 1110 xxxx  10xx xxxx  10xx xxxx */
            count += 3;
            if (count > utflen)
                throw new JUTFDataFormatException;
            char2 = (qint32) bytearr[count-2];
            char3 = (qint32) bytearr[count-1];
            if (((char2 & 0xC0) != 0x80) || ((char3 & 0xC0) != 0x80))
                throw new JUTFDataFormatException;
            chararr[chararr_count++] = (char) (((c     & 0x0F) << 12) |
                                               ((char2 & 0x3F) << 6)  |
                                               ((char3 & 0x3F) << 0));
            break;
        default:
            /* 10xx xxxx,  1111 xxxx */
            throw new JUTFDataFormatException;
        }
    }
    delete[] bytearr;
    delete[] chararr;

    // The number of chars produced may be less than utflen
    chararr[chararr_count] = '\0';
    std::string str(chararr);//TODO faire new
    return str;
}

qint64 JDataInputStream::available() {
    return in->available();
}

bool JDataInputStream::waitForReadyRead(int timeout) {
    return in->waitForReadyRead(timeout);
}

qint32 JDataInputStream::read() {
    return in->read();
}

qint32 JDataInputStream::read(qint8 b[], int off, int len) {
    return in->read(b,off,len);
}

qint8 JDataInputStream::peekByte() {
    return in->peekByte();
}

qint8 JDataInputStream::readByte() {
    return in->readByte();
}

qint16 JDataInputStream::readShort() {
    return in->readShort();
}

quint16 JDataInputStream::readUnsignedShort() {
    return in->readUnsignedShort();
}

qint32 JDataInputStream::readInt() {
    return in->readInt();
}

qint64 JDataInputStream::readLong() {
    return in->readLong();
}

float JDataInputStream::readFloat() {
    return in->readFloat();
}

double JDataInputStream::readDouble() {
    return in->readDouble();
}

char JDataInputStream::readChar() {
    return in->readChar();
}

bool JDataInputStream::readBool() {
    return in->readBool();
}

void JDataInputStream::close() {
    in->close();
}

JDataInputStream::~JDataInputStream() {
    close();
}
