#include "BlockDataOutputStream.h"
#include "JBits.h"

JBlockDataOutputStream::JBlockDataOutputStream(){
}

JBlockDataOutputStream::JBlockDataOutputStream(JOutputStream* out) {
    blkmode = false;
    pos = 0;
    this->out = out;
    dout = new JDataOutputStream(this);
}

bool JBlockDataOutputStream::setBlockDataMode(bool mode){
    if (blkmode == mode) {
        return blkmode;
    }
    drain();
    blkmode = mode;
    return !blkmode;
}

bool JBlockDataOutputStream::getBlockDataMode() {
    return blkmode;
}

void JBlockDataOutputStream::write(qint32 b){
    if (pos >= MAX_BLOCK_SIZE) {
        drain();
    }
    buf[pos++] = (qint8) b;
}

void JBlockDataOutputStream::write(qint8 b[]){
    write(b, 0, sizeof(b), false);
}

void JBlockDataOutputStream::write(qint8 b[], int off, int len){
    write(b, off, len, false);
}

void JBlockDataOutputStream::flush(){
    drain();
    out->flush();
}

void JBlockDataOutputStream::close(){
    flush();
    out->close();
}

void JBlockDataOutputStream::write(qint8 b[], int off, int len, bool copy) {
    if (!(copy || blkmode)) { 		// write directly
        drain();
        out->write(b, off, len);
        return;
    }

    while (len > 0) {
        if (pos >= MAX_BLOCK_SIZE) {
            drain();
        }
        if (len >= MAX_BLOCK_SIZE && !copy && pos == 0) {
            // avoid unnecessary copy
            writeBlockHeader(MAX_BLOCK_SIZE);
            out->write(b, off, MAX_BLOCK_SIZE);
            off += MAX_BLOCK_SIZE;
            len -= MAX_BLOCK_SIZE;
        } else {
            int wlen = (len < MAX_BLOCK_SIZE - pos ? len : MAX_BLOCK_SIZE - pos);
            arraycopy(b, off, buf, pos, wlen);
            pos += wlen;
            off += wlen;
            len -= wlen;
        }
    }
    delete[] b;
}

void JBlockDataOutputStream::arraycopy(qint8 src[],qint32 srcPos, qint8 dest[], qint32 destPos, qint32 length){
    qint8* ptr = &src[srcPos];
    for(int i = 0; i < length; ++i){
        dest[destPos] = *ptr;
        ptr++;
    }
}

void JBlockDataOutputStream::drain(){
    if (pos == 0) {
        return;
    }
    if (blkmode) {
        writeBlockHeader(pos);
    }
    out->write(buf, 0, pos);
    pos = 0;
}

void JBlockDataOutputStream::writeBlockHeader(int len){
    if (len <= 0xFF) {
        hbuf[0] = 0x77; //TC_BLOCKDATA;
        hbuf[1] = (qint8) len;
        out->write(hbuf, 0, 2);
    } else {
        hbuf[0] = 0x7a; //TC_BLOCKDATALONG;
        JBits::putInt(hbuf, 1, len);
        out->write(hbuf, 0, 5);
    }
}

void JBlockDataOutputStream::writeBoolean(bool v){
    if (pos >= MAX_BLOCK_SIZE) {
        drain();
    }
    JBits::putBoolean(buf, pos++, v);
}

void JBlockDataOutputStream::writeByte(qint8 v){
    if (pos >= MAX_BLOCK_SIZE) {
        drain();
    }
    buf[pos++] = (qint8) v;
}

void JBlockDataOutputStream::writeShort(qint16 v){
    if (pos + 2 <= MAX_BLOCK_SIZE) {
        JBits::putShort(buf, pos, (short) v);
        pos += 2;
    } else {
        dout->writeShort(v);
    }
}

void JBlockDataOutputStream::writeChar(quint16 v){
    if (pos + 2 <= MAX_BLOCK_SIZE) {
        JBits::putChar(buf, pos, (char) v);
        pos += 2;
    } else {
        dout->writeChar(v);
    }
}

void JBlockDataOutputStream::writeInt(qint32 v){
    if (pos + 4  <= MAX_BLOCK_SIZE) {
        JBits::putInt(buf, pos, v);
        pos += 4;
    } else {
        dout->writeInt(v);
    }
}

void JBlockDataOutputStream::writeLong(qint64 v){
    if (pos + 8 <= MAX_BLOCK_SIZE) {
        JBits::putLong(buf, pos, v);
        pos += 8;
    } else {
        dout->writeLong(v);
    }
}

void JBlockDataOutputStream::writeFloat(float v){
    if (pos + 4 <= MAX_BLOCK_SIZE) {
        JBits::putFloat(buf, pos, v);
        pos += 4;
    } else {
        dout->writeFloat(v);
    }
}

void JBlockDataOutputStream::writeDouble(double v){
    if (pos + 8 <= MAX_BLOCK_SIZE) {
        JBits::putDouble(buf, pos, v);
        pos += 8;
    } else {
        dout->writeDouble(v);
    }
}

void JBlockDataOutputStream::writeBytes(std::string s){
    int endoff = s.length();
    int cpos = 0;
    int csize = 0;
    for (int off = 0; off < endoff; ) {
        if (cpos >= csize) {
            cpos = 0;
            csize = (endoff - off) < CHAR_BUF_SIZE ? endoff - off : CHAR_BUF_SIZE;
            getChars(s, off, off + csize, cbuf, 0);
        }
        if (pos >= MAX_BLOCK_SIZE) {
            drain();
        }
        int n = (csize - cpos) < (MAX_BLOCK_SIZE - pos) ? csize - cpos : MAX_BLOCK_SIZE - pos;
        int stop = pos + n;
        while (pos < stop) {
            buf[pos++] = (qint8) cbuf[cpos++];
        }
        off += n;
    }

}

void JBlockDataOutputStream::getChars(std:: string s,qint32 srcBegin, qint32 srcEnd, quint16 dest[], qint32 dstBegin){
    const char* str = s.c_str();
    for( qint32 i = 0; i < srcEnd - srcBegin; ++i){
        dest[dstBegin + i] = str[ srcBegin+i];
    }
}

void JBlockDataOutputStream::writeChars(std::string s){
    int endoff = s.length();
    for (int off = 0; off < endoff; ) {
        int csize = (endoff - off) < CHAR_BUF_SIZE ? endoff - off : CHAR_BUF_SIZE;
        getChars(s, off, off + csize, cbuf, 0);
        writeChars(cbuf, 0, csize);
        off += csize;
    }
}

qint64 JBlockDataOutputStream::getUTFLength(std::string s){
    qint32 len = s.length();
    qint64 utflen = 0;
    for (qint32 off = 0; off < len; ) {
        qint32 csize = (len - off) < CHAR_BUF_SIZE ? (len - off) : CHAR_BUF_SIZE;
        getChars(s, off, off + csize, cbuf, 0);
        for (qint32 cpos = 0; cpos < csize; cpos++) {
            quint16 c = cbuf[cpos];
            if (c >= 0x0001 && c <= 0x007F) {
                utflen++;
            } else if (c > 0x07FF) {
                utflen += 3;
            } else {
                utflen += 2;
            }
        }
        off += csize;
    }
    return utflen;
}

void JBlockDataOutputStream::writeUTF(std::string s){
    writeUTF(s, getUTFLength(s));
}

void JBlockDataOutputStream::writeBooleans(bool v[], int off, int len){
    int endoff = off + len;
    while (off < endoff) {
        if (pos >= MAX_BLOCK_SIZE) {
            drain();
        }
        int stop = endoff < off + (MAX_BLOCK_SIZE - pos) ? endoff : off + (MAX_BLOCK_SIZE - pos);
        while (off < stop) {
            JBits::putBoolean(buf, pos++, v[off++]);
        }
    }
}

void JBlockDataOutputStream::writeChars(quint16 v[], int off, int len){
    int limit = MAX_BLOCK_SIZE - 2;
    int endoff = off + len;
    while (off < endoff) {
        if (pos <= limit) {
            qint32 avail = (MAX_BLOCK_SIZE - pos) >> 1;
            int stop = endoff < off + avail ? endoff : off + avail;
            while (off < stop) {
                JBits::putChar(buf, pos, v[off++]);
                pos += 2;
            }
        } else {
            dout->writeChar(v[off++]);
        }
    }
}

void JBlockDataOutputStream::writeShorts(qint16 v[], int off, int len){
    int limit = MAX_BLOCK_SIZE - 2;
    int endoff = off + len;
    while (off < endoff) {
        if (pos <= limit) {
            qint32 avail = (MAX_BLOCK_SIZE - pos) >> 1;
            int stop = endoff < off + avail ? endoff : off + avail;
            while (off < stop) {
                JBits::putShort(buf, pos, v[off++]);
                pos += 2;
            }
        } else {
            dout->writeShort(v[off++]);
        }
    }
}

void JBlockDataOutputStream::writeInts(qint32 v[], int off, int len){
    int limit = MAX_BLOCK_SIZE - 4;
    int endoff = off + len;
    while (off < endoff) {
        if (pos <= limit) {
            qint32 avail = (MAX_BLOCK_SIZE - pos) >> 2;
            int stop = endoff < off + avail ? endoff : off + avail ;
            while (off < stop) {
                JBits::putInt(buf, pos, v[off++]);
                pos += 4;
            }
        } else {
            dout->writeInt(v[off++]);
        }
    }
}

void JBlockDataOutputStream::writeFloats(float v[], int off, int len){
    int limit = MAX_BLOCK_SIZE - 4;
    int endoff = off + len;
    while (off < endoff) {
        if (pos <= limit) {
            qint32 avail = (MAX_BLOCK_SIZE - pos) >> 2;
            int chunklen = endoff - off < avail ? endoff - off : avail ;
//                floatsToBytes(v, off, buf, pos, chunklen);
            off += chunklen;
            pos += chunklen << 2;
        } else {
            dout->writeFloat(v[off++]);
        }
    }
}

void JBlockDataOutputStream::writeLongs(qint64 v[], int off, int len){
    int limit = MAX_BLOCK_SIZE - 8;
    int endoff = off + len;
    while (off < endoff) {
        if (pos <= limit) {
            qint32 avail = (MAX_BLOCK_SIZE - pos) >> 3;
            int stop = endoff < off + avail ? endoff : off + avail;
            while (off < stop) {
                JBits::putLong(buf, pos, v[off++]);
                pos += 8;
            }
        } else {
            dout->writeLong(v[off++]);
        }
    }
}

void JBlockDataOutputStream::writeDoubles(double v[], int off, int len){
    int limit = MAX_BLOCK_SIZE - 8;
    int endoff = off + len;
    while (off < endoff) {
        if (pos <= limit) {
            qint32 avail = (MAX_BLOCK_SIZE - pos) >> 3;
            int chunklen = endoff - off < avail ? endoff - off : avail;
//                doublesToBytes(v, off, buf, pos, chunklen);
            off += chunklen;
            pos += chunklen << 3;
        } else {
            dout->writeDouble(v[off++]);
        }
    }
}

void JBlockDataOutputStream::writeUTF(std::string s, qint64 utflen){
    if (utflen > 0xFFFFL) {
        throw; // UTFDataFormatException. TODO
    }
    writeShort((qint16) utflen);
    if (utflen == (qint64) s.length()) {
        writeBytes(s);
    } else {
        writeUTFBody(s);
    }
}

void JBlockDataOutputStream::writeLongUTF(std::string s){
    writeLongUTF(s, getUTFLength(s));
}

void JBlockDataOutputStream::writeLongUTF(std::string s, qint64 utflen){
    writeLong(utflen);
    if (utflen == (qint64) s.length()) {
        writeBytes(s);
    } else {
        writeUTFBody(s);
    }
}

void JBlockDataOutputStream::writeUTFBody(std::string s){
    int limit = MAX_BLOCK_SIZE - 3;
    int len = s.length();
    for (int off = 0; off < len; ) {
        int csize = len - off < CHAR_BUF_SIZE ? len - off  : CHAR_BUF_SIZE;
        getChars(s, off, off + csize, cbuf, 0);
        for (int cpos = 0; cpos < csize; cpos++) {
            char c = cbuf[cpos];
            if (pos <= limit) {
                if (c <= 0x007F && c != 0) {
                    buf[pos++] = (qint8) c;
                } else if (c > 0x07FF) {
                    buf[pos + 2] = (qint8) (0x80 | ((c >> 0) & 0x3F));
                    buf[pos + 1] = (qint8) (0x80 | ((c >> 6) & 0x3F));
                    buf[pos + 0] = (qint8) (0xE0 | ((c >> 12) & 0x0F));
                    pos += 3;
                } else {
                    buf[pos + 1] = (qint8) (0x80 | ((c >> 0) & 0x3F));
                    buf[pos + 0] = (qint8) (0xC0 | ((c >> 6) & 0x1F));
                    pos += 2;
                }
            } else { 	// write one byte at a time to normalize block
                if (c <= 0x007F && c != 0) {
                    write(c);
                } else if (c > 0x07FF) {
                    write(0xE0 | ((c >> 12) & 0x0F));
                    write(0x80 | ((c >> 6) & 0x3F));
                    write(0x80 | ((c >> 0) & 0x3F));
                } else {
                    write(0xC0 | ((c >> 6) & 0x1F));
                    write(0x80 | ((c >> 0) & 0x3F));
                }
            }
        }
        off += csize;
    }
}

JBlockDataOutputStream::~JBlockDataOutputStream(){
    delete[] buf;
    delete[] hbuf;
    delete[] cbuf;
    delete out;
    delete dout;
}
