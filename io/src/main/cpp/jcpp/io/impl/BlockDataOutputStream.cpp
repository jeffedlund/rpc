#include "BlockDataOutputStream.h"
#include "JBits.h"
#include "JUTFDataFormatException.h"
#include "JObjectStreamConstants.h"
using namespace std;
using namespace jcpp::util;

namespace jcpp{
    namespace io{
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

        void JBlockDataOutputStream::write(jint b){
            if (pos >= MAX_BLOCK_SIZE) {
                drain();
            }
            buf[pos++] = (jbyte) b;
        }

        void JBlockDataOutputStream::write(jbyte b[]){
            write(b, 0, sizeof(b), false);
        }

        void JBlockDataOutputStream::write(jbyte b[], int off, int len){
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

        void JBlockDataOutputStream::write(jbyte b[], int off, int len, bool copy) {
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
        }

        void JBlockDataOutputStream::arraycopy(jbyte src[],jint srcPos, jbyte dest[], jint destPos, jint length){
            jbyte* ptr = &src[srcPos];
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
                hbuf[0] = JObjectStreamConstants::TC_BLOCKDATA;
                hbuf[1] = (jbyte) len;
                out->write(hbuf, 0, 2);
            } else {
                hbuf[0] = JObjectStreamConstants::TC_BLOCKDATALONG;
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

        void JBlockDataOutputStream::writeByte(jbyte v){
            if (pos >= MAX_BLOCK_SIZE) {
                drain();
            }
            buf[pos++] = (jbyte) v;
        }

        void JBlockDataOutputStream::writeShort(jshort v){
            if (pos + 2 <= MAX_BLOCK_SIZE) {
                JBits::putShort(buf, pos, (short) v);
                pos += 2;
            } else {
                dout->writeShort(v);
            }
        }

        void JBlockDataOutputStream::writeChar(jushort v){
            if (pos + 2 <= MAX_BLOCK_SIZE) {
                JBits::putChar(buf, pos, (char) v);
                pos += 2;
            } else {
                dout->writeChar(v);
            }
        }

        void JBlockDataOutputStream::writeInt(jint v){
            if (pos + 4  <= MAX_BLOCK_SIZE) {
                JBits::putInt(buf, pos, v);
                pos += 4;
            } else {
                dout->writeInt(v);
            }
        }

        void JBlockDataOutputStream::writeLong(jlong v){
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

        void JBlockDataOutputStream::writeBytes(string s){
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
                    buf[pos++] = (jbyte) cbuf[cpos++];
                }
                off += n;
            }

        }

        void JBlockDataOutputStream::getChars( string s,jint srcBegin, jint srcEnd, jushort dest[], jint dstBegin){
            const char* str = s.c_str();
            for( jint i = 0; i < srcEnd - srcBegin; ++i){
                dest[dstBegin + i] = str[ srcBegin+i];
            }
        }

        void JBlockDataOutputStream::writeChars(string s){
            int endoff = s.length();
            for (int off = 0; off < endoff; ) {
                int csize = (endoff - off) < CHAR_BUF_SIZE ? endoff - off : CHAR_BUF_SIZE;
                getChars(s, off, off + csize, cbuf, 0);
                writeChars(cbuf, 0, csize);
                off += csize;
            }
        }

        jlong JBlockDataOutputStream::getUTFLength(string s){
            jint len = s.length();
            jlong utflen = 0;
            for (jint off = 0; off < len; ) {
                jint csize = (len - off) < CHAR_BUF_SIZE ? (len - off) : CHAR_BUF_SIZE;
                getChars(s, off, off + csize, cbuf, 0);
                for (jint cpos = 0; cpos < csize; cpos++) {
                    jushort c = cbuf[cpos];
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

        void JBlockDataOutputStream::writeUTF(string s){
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

        void JBlockDataOutputStream::writeChars(jushort v[], int off, int len){
            int limit = MAX_BLOCK_SIZE - 2;
            int endoff = off + len;
            while (off < endoff) {
                if (pos <= limit) {
                    jint avail = (MAX_BLOCK_SIZE - pos) >> 1;
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

        void JBlockDataOutputStream::writeShorts(jshort v[], int off, int len){
            int limit = MAX_BLOCK_SIZE - 2;
            int endoff = off + len;
            while (off < endoff) {
                if (pos <= limit) {
                    jint avail = (MAX_BLOCK_SIZE - pos) >> 1;
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

        void JBlockDataOutputStream::writeInts(jint v[], int off, int len){
            int limit = MAX_BLOCK_SIZE - 4;
            int endoff = off + len;
            while (off < endoff) {
                if (pos <= limit) {
                    jint avail = (MAX_BLOCK_SIZE - pos) >> 2;
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
                    jint avail = (MAX_BLOCK_SIZE - pos) >> 2;
                    int chunklen = endoff - off < avail ? endoff - off : avail ;
                    //floatsToBytes(v, off, buf, pos, chunklen); TODO something should be done...
                    off += chunklen;
                    pos += chunklen << 2;
                } else {
                    dout->writeFloat(v[off++]);
                }
            }
        }

        void JBlockDataOutputStream::writeLongs(jlong v[], int off, int len){
            int limit = MAX_BLOCK_SIZE - 8;
            int endoff = off + len;
            while (off < endoff) {
                if (pos <= limit) {
                    jint avail = (MAX_BLOCK_SIZE - pos) >> 3;
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
                    jint avail = (MAX_BLOCK_SIZE - pos) >> 3;
                    int chunklen = endoff - off < avail ? endoff - off : avail;
                    //doublesToBytes(v, off, buf, pos, chunklen);  TODO something should be done...
                    off += chunklen;
                    pos += chunklen << 3;
                } else {
                    dout->writeDouble(v[off++]);
                }
            }
        }

        void JBlockDataOutputStream::writeUTF(string s, jlong utflen){
            if (utflen > 0xFFFFL) {
                throw new JUTFDataFormatException();
            }
            writeShort((jshort) utflen);
            if (utflen == (jlong) s.length()) {
                writeBytes(s);
            } else {
                writeUTFBody(s);
            }
        }

        void JBlockDataOutputStream::writeLongUTF(string s){
            writeLongUTF(s, getUTFLength(s));
        }

        void JBlockDataOutputStream::writeLongUTF(string s, jlong utflen){
            writeLong(utflen);
            if (utflen == (jlong) s.length()) {
                writeBytes(s);
            } else {
                writeUTFBody(s);
            }
        }

        void JBlockDataOutputStream::writeUTFBody(string s){
            int limit = MAX_BLOCK_SIZE - 3;
            int len = s.length();
            for (int off = 0; off < len; ) {
                int csize = len - off < CHAR_BUF_SIZE ? len - off  : CHAR_BUF_SIZE;
                getChars(s, off, off + csize, cbuf, 0);
                for (int cpos = 0; cpos < csize; cpos++) {
                    char c = cbuf[cpos];
                    if (pos <= limit) {
                        if (c <= 0x007F && c != 0) {
                            buf[pos++] = (jbyte) c;
                        } else if (c > 0x07FF) {
                            buf[pos + 2] = (jbyte) (0x80 | ((c >> 0) & 0x3F));
                            buf[pos + 1] = (jbyte) (0x80 | ((c >> 6) & 0x3F));
                            buf[pos + 0] = (jbyte) (0xE0 | ((c >> 12) & 0x0F));
                            pos += 3;
                        } else {
                            buf[pos + 1] = (jbyte) (0x80 | ((c >> 0) & 0x3F));
                            buf[pos + 0] = (jbyte) (0xC0 | ((c >> 6) & 0x1F));
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
    }
}
