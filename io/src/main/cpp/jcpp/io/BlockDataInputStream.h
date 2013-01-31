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

//BlockDataInputStream
class BlockDataInputStream : public JInputStream, public JObjectStreamConstants {
public:

    /** buffer for reading general/block data */
    qint8 buf[MAX_BLOCK_SIZE];
    /** buffer for reading block data headers */
    qint8 hbuf[MAX_HEADER_SIZE];
    /** char buffer for fast string reads */
    char cbuf[CHAR_BUF_SIZE];

    /** block data mode */
    bool blkmode;

    // block data state fields; values meaningful only when blkmode true
    /** current offset into buf */
    qint32 pos;
    /** end offset of valid data in buf, or -1 if no more block data */
    qint32 end;
    /** number of bytes in current block yet to be read from stream */
    qint32 unread;

    JInputStream *in;

    BlockDataInputStream(JInputStream *in);

    /**
     * Sets block data mode to the given mode (true == on, false == off)
     * and returns the previous mode value.  If the new mode is the same as
     * the old mode, no action is taken.  Throws IllegalStateException if
     * block data mode is being switched from on to off while unconsumed
     * block data is still present in the stream.
     */
    bool setBlockDataMode(bool newmode);

    /**
     * Returns true if the stream is currently in block data mode, false
     * otherwise.
     */
    bool getBlockDataMode();

    /**
     * If in block data mode, skips to the end of the current group of data
     * blocks (but does not unset block data mode).  If not in block data
     * mode, throws an IllegalStateException.
     */
    void skipBlockData();

private:
    /**
     * Attempts to read in the next block data header (if any).  If
     * canBlock is false and a full header cannot be read without possibly
     * blocking, returns HEADER_BLOCKED, else if the next element in the
     * stream is a block data header, returns the block data length
     * specified by the header, else returns -1.
     */
    qint32 readBlockHeader(bool canBlock);

    /**
     * Refills internal buffer buf with block data.  Any data in buf at the
     * time of the call is considered consumed.  Sets the pos, end, and
     * unread fields to reflect the new amount of available block data; if
     * the next element in the stream is not a data block, sets pos and
     * unread to 0 and end to -1.
     */
    void refill();

public:
    /**
     * If in block data mode, returns the number of unconsumed bytes
     * remaining in the current data block.  If not in block data mode,
     * throws an IllegalStateException.
     */
    qint32 currentBlockRemaining() ;

    /**
     * Peeks at (but does not consume) and returns the next byte value in
     * the stream, or -1 if the end of the stream/block data (if in block
     * data mode) has been reached.
     */
    int peek();

    /**
     * Peeks at (but does not consume) and returns the next byte value in
     * the stream, or -1 if the end of the stream/block data (if in block
     * data mode) has been reached.
     */
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
