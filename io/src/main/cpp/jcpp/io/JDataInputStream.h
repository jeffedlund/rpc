#ifndef JDATAINPUTSTREAM_H
#define JDATAINPUTSTREAM_H

#include "JInputStream.h"
#include "JClass.h"
using namespace std;

class JDataInputStream : public JInputStream{
    JInputStream *in;

public:
    JDataInputStream();
    JDataInputStream(JInputStream *in);

    static JClass* getClazz();

    void setInputStream(JInputStream *in);

    void readFully(qint8 b[], qint32 off, qint32 len);
    virtual string readUTF();

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
    virtual ~JDataInputStream();
};

#endif // JDATAINPUTSTREAM_H
