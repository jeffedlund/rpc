#include "BlockDataInputStream.h"
#include "JIllegalStateException.h"
#include "JStreamCorruptedException.h"
#include "JEOFException.h"
#include <sstream>

//TODO missing following methods : skip,skipBytes,readUnsignedByte,readUTFSpan,readUTFChar
//BlockDataInputStream implementation
BlockDataInputStream::BlockDataInputStream(JInputStream *in): blkmode(false), pos(0), end (-1), unread(0) {
    this->in = in;
}

bool BlockDataInputStream::setBlockDataMode(bool newmode) {
    if (blkmode == newmode) {
        return blkmode;
    }
    if (newmode) {
        pos = 0;
        end = 0;
        unread = 0;
    }else if (pos < end) {
        throw new JIllegalStateException("unread block dat");
    }
    blkmode = newmode;
    return !blkmode;
}

bool BlockDataInputStream::getBlockDataMode() {
    return blkmode;
}

void BlockDataInputStream::skipBlockData() {
    if (!blkmode) {
        throw new JIllegalStateException("not in block data mode");
    }
    while (end >= 0) {
        refill();
    }
}

qint32 BlockDataInputStream::readBlockHeader(bool canBlock) {
    for (;;) {
        qint64 avail;
        if (canBlock) {
            avail = INT_MAX;
        }
        else {
            if ((avail = in->available()) == 0) {
                if (in->waitForReadyRead(5000)) {
                    avail = in->available();
                }
            }
        }
        if (avail == 0) {
            return HEADER_BLOCKED;
        }

        qint32 tc = in->peekByte();
        switch (tc) {
        case JObjectStreamConstants::TC_BLOCKDATA:
            if (avail < 2) {
                return HEADER_BLOCKED;
            }
            in->read(hbuf,0,2);
            return hbuf[1] & 0xFF;

        case JObjectStreamConstants::TC_BLOCKDATALONG:
        {
            if (avail < 5) {
                return HEADER_BLOCKED;
            }
            in->read(hbuf,0,5);
            qint32 len = JBits::getInt(hbuf,1);
            if (len < 0) {
                stringstream ss;
                ss<<"illegal block data header length: "<< len;
                throw new JStreamCorruptedException(ss.str());
            }
            return len;
        }

        /*
         * TC_RESETs may occur in between data blocks.
         * Unfortunately, this case must be parsed at a lower
         * level than other typecodes, since primitive data
         * reads may span data blocks separated by a TC_RESET.
         */
        case JObjectStreamConstants::TC_RESET:
            in->readByte();
            break;

        default:
            if (tc >= 0 && (tc < JObjectStreamConstants::TC_BASE || tc > JObjectStreamConstants::TC_MAX)) {
                stringstream ss;
                ss<<"invalid type code: "<<tc;
                throw new JStreamCorruptedException(ss.str());
            }
            return -1;
        }
    }
}

void BlockDataInputStream::refill() {
    do {
        pos = 0;
        if (unread > 0) {
            int n = in->read(buf,0,min(unread, MAX_BLOCK_SIZE));
            if (n >= 0) {
                end = n;
                unread -= n;
            }
            else {
                throw new JStreamCorruptedException("unexpected EOF in middle of data block");
            }
        }else {
            qint32 n = readBlockHeader(false);
            if (n >= 0) {
                end = 0;
                unread = n;
            }else {
                end = -1;
                unread = 0;
            }
        }
    } while (pos == end);
}

qint32 BlockDataInputStream::currentBlockRemaining() {
    if (blkmode) {
        return (end >= 0) ? (end - pos) + unread : 0;
    }else {
        throw new JIllegalStateException();
    }
}

int BlockDataInputStream::peek() {
    if (blkmode) {
        if (pos == end) {
            refill();
        }
        return (end >= 0) ? (buf[pos] & 0xFF) : -1;
    }else {
        return in->peekByte();
    }
}

qint8 BlockDataInputStream::peekByte() {
    int val = peek();
    if (val < 0) {
        throw new JEOFException();
    }
    return (qint8) val;
}

qint32 BlockDataInputStream::read() {
    if (blkmode) {
        if (pos == end) {
            refill();
        }
        return (end >= 0) ? (buf[pos++] & 0xFF) : -1;
    }else {
        return in->readByte();
    }
}

int BlockDataInputStream::read(qint8 b[], int off, int len) {
    return read(b, off, len, false);
}

qint64 BlockDataInputStream::available() {
    if (blkmode) {
        if ((pos == end) && (unread == 0)) {
            qint32 n;
            while ((n = readBlockHeader(false)) == 0);
            switch (n) {
            case HEADER_BLOCKED:
                break;

            case -1:
                pos = 0;
                end = -1;
                break;

            default:
                pos = 0;
                end = 0;
                unread = n;
                break;
            }
        }
        // avoid unnecessary call to in.available() if possible
        qint64 unreadAvail = (unread > 0) ? min(in->available(), (qint64) unread) : 0;
        return (end >= 0) ? (end - pos) + unreadAvail : 0;
    }else {
        return in->available();
    }
}

bool BlockDataInputStream::waitForReadyRead(int i) {
    return in->waitForReadyRead(i);
}

void BlockDataInputStream::close() {
    if (blkmode) {
        pos = 0;
        end = -1;
        unread = 0;
    }
    in->close();
}

int BlockDataInputStream::read(qint8 b[], int off, int len, bool copy) {
    if (len == 0) {
        return 0;
    }else if (blkmode) {
        if (pos == end) {
            refill();
        }
        if (end < 0) {
            return -1;
        }
        int nread = min(len, end - pos);
        memcpy(b+off,buf+pos,nread);
        pos += read();
        return nread;
    }else if (copy) {
        int nread = in->read(buf,0,min(len, MAX_BLOCK_SIZE));
        if (nread > 0) {
            memcpy((char*)b+off,buf,nread);
        }
        return nread;
    }else {
        return in->read(b,off,len);
    }
}

void BlockDataInputStream::readFully(qint8 *b, int off, int len) {
    readFully(b, off, len, false);
}

void BlockDataInputStream::readFully(qint8 *b, int off, int len, bool copy) {
    while (len > 0) {
        int n = read(b, off, len, copy);
        if (n < 0) {
            throw new JEOFException();
        }
        off += n;
        len -= n;
    }
}

qint8 BlockDataInputStream::readByte() {
    quint32 v = read();
    if (v < 0) {
        throw new JEOFException();
    }
    return (qint8) v;
}

qint16 BlockDataInputStream::readShort() {
    if (!blkmode) {
        pos = 0;
        in->read(buf,0,2);
    }
    else if ( end - pos < 2) {
        qint8 readBuffer[2];
        for (int i = 0; i < 2; ++i) {
            readBuffer[i] = read();
        }
        return JBits::getShort(readBuffer,0);
    }
    qint16 v = JBits::getShort(buf, pos);
    pos += 2;
    return v;
}

qint32 BlockDataInputStream::readInt() {
    if (!blkmode) {
        pos = 0;
        in->read(buf, 0, 4);
    } else if (end - pos < 4) {
        qint8 readBuffer[4];
        for (int i = 0; i < 4; ++i) {
            readBuffer[i] = read();
        }
        return JBits::getInt(readBuffer,0);
    }
    qint32 v = JBits::getInt(buf, pos);
    pos += 4;
    return v;
}

float BlockDataInputStream::readFloat() {
    if (!blkmode) {
        pos = 0;
        in->read(buf, 0, 4);
    }
    else if (end - pos < 4) {
        qint8 readBuffer[4];
        for (int i = 0; i < 4; ++i) {
            readBuffer[i] = read();
        }
        return JBits::getFloat(readBuffer,0);
    }
    float v = JBits::getFloat(buf, pos);
    pos += 4;
    return v;
}

qint64 BlockDataInputStream::readLong() {
    if (!blkmode) {
        pos = 0;
        in->read(buf, 0, 8);
    }
    else if (end - pos < 8) {
        qint8 readBuffer[8];
        for (int i = 0; i < 8; ++i) {
            readBuffer[i] = read();
        }
        return JBits::getLong(readBuffer,0);
    }
    qint64 v = JBits::getLong(buf, pos);
    pos += 8;
    return v;
}

double BlockDataInputStream::readDouble() {
    if (!blkmode) {
        pos = 0;
        in->read(buf, 0, 8);
    } else if (end - pos < 8) {
        qint8 readBuffer[8];
        for (int i = 0; i < 8; ++i) {
            readBuffer[i] = read();
        }
        return JBits::getDouble(readBuffer,0);
    }
    double v = JBits::getDouble(buf, pos);
    pos += 8;
    return v;
}

char BlockDataInputStream::readChar() {
    if (!blkmode) {
       pos = 0;
       in->read(buf, 0, 2);
   } else if (end - pos < 2) {
        qint8 readBuffer[2];
        for (int i = 0; i < 2; ++i) {
            readBuffer[i] = read();
        }
        return readBuffer[1];
   }
   char v = buf[pos+1];
   pos += 2;
   return v;
}

bool BlockDataInputStream::readBool() {
    int v = read();
    if (v < 0) {
        throw new JEOFException();
    }
    return (v != 0);
}

string BlockDataInputStream::readUTFBody(qint64 len) {
    if (!blkmode) {
        end = pos = 0;
    }

    char *cname = new char[len+1];
    cname[len] = '\0';
    in->read((qint8*)cname, 0, len);
    string str(cname);
    delete cname;
    return str;
}

string BlockDataInputStream::readUTF() {
    return readUTFBody(readShort());
}

string BlockDataInputStream::readLongUTF() {
    return readUTFBody(readLong());
}

void BlockDataInputStream::readBools(bool *v, int off, int len) {
    int stop, endoff = off+ len;
    while(off < endoff) {
        if (!blkmode) {
            int span = min(endoff - off, MAX_BLOCK_SIZE);
            in->read(buf,0, span);
            stop = off + span;
            pos = 0;
        }else if (end - pos < 1) {
            v[off++] = in->readBool();
            continue;
        }else {
            stop = min(endoff, off + end - pos);
        }
        while (off < stop) {
            v[off++] = JBits::getBool(buf, pos++);
        }
    }
}

void BlockDataInputStream::readChars(char *v, int off, int len) {
    int stop, endoff = off+ len;
    while(off < endoff) {
        if (!blkmode) {
            int span = min(endoff - off, MAX_BLOCK_SIZE >> 1);
            in->read(buf,0, span << 1);
            stop = off + span;
            pos = 0;
        }else if (end - pos < 2) {
            v[off++] = in->readChar();
            continue;
        }else {
            stop = min(endoff, off + ((end - pos) >> 1));
        }
        while (off < stop) {
            v[off++] = buf[pos+1];
            pos += 2;
        }
    }
}

void BlockDataInputStream::readShorts(qint16 *v, int off, int len) {
    int stop, endoff = off + len;
    while (off < endoff) {
        if (!blkmode) {
            int span = min(endoff - off, MAX_BLOCK_SIZE >> 1);
            in->read(buf, 0,span << 1);
            stop = off + span;
            pos = 0;
        } else if (end - pos < 2) {
            v[off++] = in->readShort();
            continue;
        } else {
            stop = min(endoff, off + ((end - pos) >> 1));
        }

        while (off < stop) {
            v[off++] = JBits::getShort(buf, pos);
            pos += 2;
        }
    }
}

void BlockDataInputStream::readInts(qint32 *v, int off, int len) {
    int stop, endoff = off + len;
    while (off < endoff) {
        if (!blkmode) {
            int span = min(endoff - off, MAX_BLOCK_SIZE >> 2);
            in->read(buf, 0, span << 2);
            stop = off + span;
            pos = 0;
        } else if (end - pos < 4) {
            v[off++] = in->readInt();
            continue;
        } else {
            stop = min(endoff, off + ((end - pos) >> 2));
        }

        while (off < stop) {
            v[off++] = JBits::getInt(buf, pos);
            pos += 4;
        }
    }
}

void BlockDataInputStream::readFloats(float *v, int off, int len) {
    int stop, endoff = off + len;
    while (off < endoff) {
        if (!blkmode) {
            int span = min(endoff - off, MAX_BLOCK_SIZE >> 2);
            in->read(buf, 0, span << 2);
            stop = off + span;
            pos = 0;
        } else if (end - pos < 4) {
            v[off++] = in->readFloat();
            continue;
        } else {
            stop = min(endoff, off + ((end - pos) >> 2));
        }

        while (off < stop) {
            v[off++] = JBits::getFloat(buf,pos);
            pos += 4;
        }
    }
}

void BlockDataInputStream::readLongs(qint64 *v, int off, int len) {
    int stop, endoff = off + len;
    while (off < endoff) {
        if (!blkmode) {
            int span = min(endoff - off, MAX_BLOCK_SIZE >> 3);
            in->read(buf, 0, span << 3);
            stop = off + span;
            pos = 0;
        } else if (end - pos < 8) {
            v[off++] = in->readLong();
            continue;
        } else {
            stop = min(endoff, off + ((end - pos) >> 3));
        }

        while (off < stop) {
            v[off++] = JBits::getLong(buf, pos);
            pos += 8;
        }
    }
}

void BlockDataInputStream::readDoubles(double *v, int off, int len) {
    int stop, endoff = off + len;
    while (off < endoff) {
        if (!blkmode) {
            int span = min(endoff - off, MAX_BLOCK_SIZE >> 3);
            in->read(buf, 0, span << 3);
            stop = off + span;
            pos = 0;
        } else if (end - pos < 8) {
            v[off++] = in->readDouble();
            continue;
        } else {
            stop = min(endoff - off, ((end - pos) >> 3));
        }

        while (off < stop) {
            v[off++] = JBits::getDouble(buf, pos);
            pos += 8;
        }
    }
}

BlockDataInputStream::~BlockDataInputStream() {
    close();
}
