#ifndef QTDATAINPUTSTREAM_H
#define QTDATAINPUTSTREAM_H

#include "JInputStream.h"
#include "QDataStream"

class QtDataInputStream : public JInputStream
{
    QDataStream* in;
public:
    QtDataInputStream(QDataStream*);
    QDataStream* getStream();
    virtual qint64 available();
    virtual bool waitForReadyRead(int = 30000);
    virtual qint32 read();
    virtual qint32 read(qint8 b[], int off, int len);
    virtual qint8 peekByte();
    virtual qint8 readByte();
    virtual qint16 readShort();
    virtual quint16 readUnsignedShort();
    virtual qint32 readInt();
    virtual qint64 readLong();
    virtual float readFloat();
    virtual double readDouble();
    virtual char readChar();
    virtual bool readBool();
    virtual void close();
    virtual ~QtDataInputStream();
};

#endif // QTDATAINPUTSTREAM_H
