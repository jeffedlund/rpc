#ifndef BLOCKDATAINPUTSTREAM_H
#define BLOCKDATAINPUTSTREAM_H

#include "JInputStream.h"
#include "JObjectStreamConstants.h"
#include "JBits.h"
#include "climits"
#include "memory.h"
#include <QtGlobal>
using namespace std;

static const qint32 MAX_BLOCK_SIZE = 1024;
static const qint32 MAX_HEADER_SIZE = 5;
static const qint32 CHAR_BUF_SIZE = 256;
static const qint32 HEADER_BLOCKED = -2;

class BlockDataInputStream : public JInputStream, public JObjectStreamConstants {
public:
    qint8 buf[MAX_BLOCK_SIZE];
    qint8 hbuf[MAX_HEADER_SIZE];
    char cbuf[CHAR_BUF_SIZE];
    bool blkmode;
    qint32 pos;
    qint32 end;
    qint32 unread;
    JInputStream *in;
    BlockDataInputStream(JInputStream *in);

    bool setBlockDataMode(bool newmode);
    bool getBlockDataMode();
    void skipBlockData();

private:
    qint32 readBlockHeader(bool canBlock);
    void refill();

public:
    qint32 currentBlockRemaining() ;
    int peek();
    qint8 peekByte();
    void readFully(qint8 *b, int off, int len);
    void readFully(qint8 *b, int off, int len, bool copy);
    string readUTFBody(qint64 len);
    string readUTF();
    string readLongUTF();
    void readBools(bool *v, int off, int len);
    void readChars(char *v, int off, int len);
    void readShorts(qint16 *v, int off, int len);
    void readInts(qint32 *v, int off, int len);
    void readFloats(float *v, int off, int len);
    void readLongs(qint64 *v, int off, int len);
    void readDoubles(double *v, int off, int len);

    virtual qint64 available();
    virtual bool waitForReadyRead(int = 30000);
    virtual qint32 read();
    virtual qint32 read(qint8 b[], int off, int len);
    virtual int read(qint8 b[], int off, int len, bool copy);
    virtual qint8 readByte();
    virtual qint16 readShort();
    virtual qint32 readInt();
    virtual qint64 readLong();
    virtual float readFloat();
    virtual double readDouble();
    virtual char readChar();
    virtual bool readBool();
    virtual void close();
    ~BlockDataInputStream();
};

#endif // BLOCKDATAINPUTSTREAM_H
