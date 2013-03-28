#include "BlockDataInputStream.h"
#include "JIllegalStateException.h"
#include "JStreamCorruptedException.h"
#include "JEOFException.h"
#include <sstream>
#include "JUTFDataFormatException.h"
#include "JInstantiationException.h"

namespace jcpp{
    namespace io{
        class JBlockDataInputStreamClass : public JClass{
        public:
            JBlockDataInputStreamClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.io.ObjectInputStream$BlockDataInputStream";
                name="java.io.ObjectInputStream$BlockDataInputStream";
                simpleName="ObjectInputStream$BlockDataInputStream";
            }

            JClass* getSuperclass(){
                return JInputStream::getClazz();
            }

            JObject* newInstance(){
                throw new JInstantiationException("cannot instantiate object of class "+getName());
            }
        };

        static JClass* clazz;

        JClass* BlockDataInputStream::getClazz(){
            if (clazz==NULL){
                clazz=new JBlockDataInputStreamClass();
            }
            return clazz;
        }

        BlockDataInputStream::BlockDataInputStream(JInputStream *in): JInputStream(getClazz()) {
            this->blkmode=false;
            this->pos=0;
            this->end=-1;
            this->unread=0;
            this->defaultDataEnd=false;
            this->in = in;
            this->din = new JDataInputStream(this);
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

        jint BlockDataInputStream::readBlockHeader(bool canBlock) {
            if (defaultDataEnd) {
                return -1;
            }
            for (;;) {
                jlong avail;
                if (canBlock) {
                    avail = INT_MAX;
                }else {
                    if ((avail = in->available()) == 0) {
                        if (in->waitForReadyRead(100000)) {//TODO use readtimeout
                            avail = in->available();
                        }
                    }
                }
                if (avail == 0) {
                    return HEADER_BLOCKED;
                }

                jbyte tc = in->peekByte();
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
                    jint len = JBits::getInt(hbuf,1);
                    if (len < 0) {
                        stringstream ss;
                        ss<<"illegal block data header length: "<< len;
                        throw new JStreamCorruptedException(ss.str());
                    }
                    return len;
                }

                case JObjectStreamConstants::TC_RESET:
                    in->read();
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
                    } else {
                        throw new JStreamCorruptedException("unexpected EOF in middle of data block");
                    }
                }else {
                    jint n = readBlockHeader(false);
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

        jint BlockDataInputStream::currentBlockRemaining() {
            if (blkmode) {
                return (end >= 0) ? (end - pos) + unread : 0;
            }else {
                throw new JIllegalStateException();
            }
        }

        bool BlockDataInputStream::isDefaultDataEnd(){
            return defaultDataEnd;
        }

        void BlockDataInputStream::setDefaultDataEnd(bool defaultDataEnd){
            this->defaultDataEnd=defaultDataEnd;
        }

        jint BlockDataInputStream::peek() {
            if (blkmode) {
                if (pos == end) {
                    refill();
                }
                return (end >= 0) ? (buf[pos] & 0xFF) : -1;
            }else {
                return in->peek();
            }
        }

        jint BlockDataInputStream::read() {
            if (blkmode) {
                if (pos == end) {
                    refill();
                }
                return (end >= 0) ? (buf[pos++] & 0xFF) : -1;
            }else {
                return in->read();
            }
        }

        int BlockDataInputStream::read(jbyte b[], int off, int len) {
            return read(b, off, len, false);
        }

        jlong BlockDataInputStream::skip(jlong len){
            jlong remain = len;
            while (remain > 0) {
                if (blkmode) {
                    if (pos == end) {
                        refill();
                    }
                    if (end < 0) {
                        break;
                    }
                    jint nread = (jint) min((jint)remain, end - pos);
                    remain -= nread;
                    pos += nread;
                } else {
                    jint nread = (jint) min((jint)remain, MAX_BLOCK_SIZE);
                    if ((nread = in->read(buf, 0, nread)) < 0) {
                        break;
                    }
                    remain -= nread;
                }
            }
            return len - remain;
        }

        jint BlockDataInputStream::available() {
            if (blkmode) {
                if ((pos == end) && (unread == 0)) {
                    jint n;
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
                jint unreadAvail = (unread > 0) ? min(in->available(), unread) : 0;
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

        int BlockDataInputStream::read(jbyte b[], int off, int len, bool copy) {
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
                pos += nread;
                return nread;
            }else if (copy) {
                int nread = in->read(buf,0,min(len, MAX_BLOCK_SIZE));
                if (nread > 0) {
                    memcpy(b+off,buf,nread);
                }
                return nread;
            }else {
                return in->read(b,off,len);
            }
        }

        void BlockDataInputStream::readFully(jbyte *b, int off, int len) {
            readFully(b, off, len, false);
        }

        void BlockDataInputStream::readFully(jbyte *b, int off, int len, bool copy) {
            while (len > 0) {
                int n = read(b, off, len, copy);
                if (n < 0) {
                    throw new JEOFException();
                }
                off += n;
                len -= n;
            }
        }

        jint BlockDataInputStream::skipBytes(jint n){
            return din->skipBytes(n);
        }

        jbyte BlockDataInputStream::readUnsignedByte() {
            jbyte v = read();
            if (v < 0) {
                throw new JEOFException();
            }
            return (jbyte) v;
        }

        jbyte BlockDataInputStream::readByte() {
            jbyte v = read();
            if (v < 0) {
                throw new JEOFException();
            }
            return (jbyte) v;
        }

        jshort BlockDataInputStream::readShort() {
            if (!blkmode) {
                pos = 0;
                in->readFully(buf,0,2);

            }else if ( end - pos < 2) {
                return din->readShort();
            }
            jshort v = JBits::getShort(buf, pos);
            pos += 2;
            return v;
        }

        jshort BlockDataInputStream::readUnsignedShort(){
            if (!blkmode) {
                pos = 0;
                in->readFully(buf, 0, 2);
            } else if (end - pos < 2) {
                return din->readUnsignedShort();
            }
            jshort v = JBits::getShort(buf, pos) & 0xFFFF;
            pos += 2;
            return v;
        }

        jint BlockDataInputStream::readInt() {
            if (!blkmode) {
                pos = 0;
                in->readFully(buf, 0, 4);

            } else if (end - pos < 4) {
                return din->readInt();
            }
            jint v = JBits::getInt(buf, pos);
            pos += 4;
            return v;
        }

        float BlockDataInputStream::readFloat() {
            if (!blkmode) {
                pos = 0;
                in->readFully(buf, 0, 4);

            }else if (end - pos < 4) {
                return din->readFloat();
            }
            jfloat v = JBits::getFloat(buf, pos);
            pos += 4;
            return v;
        }

        jlong BlockDataInputStream::readLong() {
            if (!blkmode) {
                pos = 0;
                in->readFully(buf, 0, 8);

            }else if (end - pos < 8) {
                return din->readLong();
            }
            jlong v = JBits::getLong(buf, pos);
            pos += 8;
            return v;
        }

        jdouble BlockDataInputStream::readDouble() {
            if (!blkmode) {
                pos = 0;
                in->readFully(buf, 0, 8);

            } else if (end - pos < 8) {
                return din->readDouble();
            }
            jdouble v = JBits::getDouble(buf, pos);
            pos += 8;
            return v;
        }

        jchar BlockDataInputStream::readChar() {
            if (!blkmode) {
               pos = 0;
               in->readFully(buf, 0, 2);
           } else if (end - pos < 2) {
                return din->readChar();
           }
           jchar v = JBits::getChar(buf, pos);
           pos += 2;
           return v;
        }

        jbool BlockDataInputStream::readBool() {
            int v = read();
            if (v < 0) {
                throw new JEOFException();
            }
            return (v != 0);
        }

        string BlockDataInputStream::readUTFBody(jlong utflen) {
            vector<jchar>* sbuf=new vector<jchar>();
            if (!blkmode) {
                end = pos = 0;
            }

            while (utflen > 0) {
                jint avail = end - pos;
                if (avail >= 3 || (jlong) avail == utflen) {
                    utflen -= readUTFSpan(sbuf, utflen);
                } else {
                    if (blkmode) {
                        // near block boundary, read one byte at a time
                        utflen -= readUTFChar(sbuf, utflen);
                    } else {
                        // shift and refill buffer manually
                        if (avail > 0) {
                            arraycopy(buf, pos, buf, 0, avail);
                        }
                        pos = 0;
                        end = (jint) min(MAX_BLOCK_SIZE,(jint) utflen);
                        in->readFully(buf, avail, end - avail);
                    }
                }
            }

            jchar* jc=new jchar[sbuf->size()];//not extra
            for (unsigned int i=0;i<sbuf->size();i++){
                jc[i]=sbuf->at(i);
            }
            char* cs=new char[sbuf->size()+1];
            cs[sbuf->size()] = '\0';
            JBits::fromJChartoChar(jc,cs,0,sbuf->size());
            string str(cs);
            delete cs;
            delete sbuf;
            delete jc;
            return str;
        }

        void BlockDataInputStream::arraycopy(jbyte src[],jint srcPos, jbyte dest[], jint destPos, jint length){
            jbyte* ptr = &src[srcPos];
            for(int i = 0; i < length; ++i){
                dest[destPos+i] = *ptr;
                ptr++;
            }
        }

        jlong BlockDataInputStream::readUTFSpan(vector<jchar>* sbuf, jlong utflen) {
            jint cpos = 0;
            jint start = pos;
            jint avail = min(end - pos, CHAR_BUF_SIZE);
            jint stop = pos + ((utflen > avail) ? avail - 2 : (jint) utflen);
            bool outOfBounds = false;

            try {
                while (pos < stop) {
                    jint b1, b2, b3;
                    b1 = buf[pos++] & 0xFF;
                    switch (b1 >> 4) {
                        case 0:
                        case 1:
                        case 2:
                        case 3:
                        case 4:
                        case 5:
                        case 6:
                        case 7:	  // 1 byte format: 0xxxxxxx
                            cbuf[cpos++] = (jchar) b1;
                            break;

                        case 12:
                        case 13:  // 2 byte format: 110xxxxx 10xxxxxx
                            b2 = buf[pos++];
                            if ((b2 & 0xC0) != 0x80) {
                                throw new JUTFDataFormatException();
                            }
                            cbuf[cpos++] = (jchar) (((b1 & 0x1F) << 6) |  ((b2 & 0x3F) << 0));
                            break;

                        case 14:  // 3 byte format: 1110xxxx 10xxxxxx 10xxxxxx
                            b3 = buf[pos + 1];
                            b2 = buf[pos + 0];
                            pos += 2;
                            if ((b2 & 0xC0) != 0x80 || (b3 & 0xC0) != 0x80) {
                                throw new JUTFDataFormatException();
                            }
                            cbuf[cpos++] = (jchar) (((b1 & 0x0F) << 12) |  ((b2 & 0x3F) << 6) |  ((b3 & 0x3F) << 0));
                            break;

                        default:  // 10xx xxxx, 1111 xxxx
                            throw new JUTFDataFormatException();
                    }
                }
            } catch (JThrowable* ex){//ideally JArrayIndexOutOfBoundsException*
                outOfBounds = true;
            }
            if (outOfBounds || (pos - start) > utflen) {
                pos = start + (int) utflen;
                throw new JUTFDataFormatException();
            }
            for (int i=0;i<cpos;i++){
                sbuf->push_back(cbuf[i]);
            }
            return pos - start;
        }

        jint BlockDataInputStream::readUTFChar(vector<jchar>* sbuf, jlong utflen){
            jint b1, b2, b3;
            b1 = readByte() & 0xFF;
            switch (b1 >> 4) {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:     // 1 byte format: 0xxxxxxx
                    sbuf->push_back((jchar) b1);
                    return 1;

                case 12:
                case 13:    // 2 byte format: 110xxxxx 10xxxxxx
                    if (utflen < 2) {
                        throw new JUTFDataFormatException();
                    }
                    b2 = readByte();
                    if ((b2 & 0xC0) != 0x80) {
                        throw new JUTFDataFormatException();
                    }
                    sbuf->push_back((jchar) (((b1 & 0x1F) << 6) | ((b2 & 0x3F) << 0)));
                    return 2;

                case 14:    // 3 byte format: 1110xxxx 10xxxxxx 10xxxxxx
                    if (utflen < 3) {
                        if (utflen == 2) {
                            readByte();		// consume remaining byte
                        }
                        throw new JUTFDataFormatException();
                    }
                    b2 = readByte();
                    b3 = readByte();
                    if ((b2 & 0xC0) != 0x80 || (b3 & 0xC0) != 0x80) {
                        throw new JUTFDataFormatException();
                    }
                    sbuf->push_back((jchar) (((b1 & 0x0F) << 12) |  ((b2 & 0x3F) << 6) | ((b3 & 0x3F) << 0)));
                    return 3;

                default:   // 10xx xxxx, 1111 xxxx
                    throw new JUTFDataFormatException();
            }
        }


        string BlockDataInputStream::readUTF() {
            return readUTFBody(readUnsignedShort());
        }

        string BlockDataInputStream::readLongUTF() {
            return readUTFBody(readLong());
        }

        void BlockDataInputStream::readBools(jbool *v, int off, int len) {
            int stop, endoff = off+ len;
            while(off < endoff) {
                if (!blkmode) {
                    int span = min(endoff - off, MAX_BLOCK_SIZE);
                    in->readFully(buf,0, span);
                    stop = off + span;
                    pos = 0;
                }else if (end - pos < 1) {
                    v[off++] = din->readBool();
                    continue;
                }else {
                    stop = min(endoff, off + end - pos);
                }
                while (off < stop) {
                    v[off++] = JBits::getBool(buf, pos++);
                }
            }
        }

        void BlockDataInputStream::readChars(jchar *v, int off, int len) {
            int stop, endoff = off+ len;
            while(off < endoff) {
                if (!blkmode) {
                    int span = min(endoff - off, MAX_BLOCK_SIZE >> 1);
                    in->readFully(buf,0, span << 1);
                    stop = off + span;
                    pos = 0;
                }else if (end - pos < 2) {
                    v[off++] = din->readChar();
                    continue;
                }else {
                    stop = min(endoff, off + ((end - pos) >> 1));
                }
                while (off < stop) {
                    v[off++] = JBits::getChar(buf,pos);
                    pos += 2;
                }
            }
        }

        void BlockDataInputStream::readShorts(jshort *v, int off, int len) {
            int stop, endoff = off + len;
            while (off < endoff) {
                if (!blkmode) {
                    int span = min(endoff - off, MAX_BLOCK_SIZE >> 1);
                    in->readFully(buf, 0,span << 1);
                    stop = off + span;
                    pos = 0;
                } else if (end - pos < 2) {
                    v[off++] = din->readShort();
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

        void BlockDataInputStream::readInts(jint *v, int off, int len) {
            int stop, endoff = off + len;
            while (off < endoff) {
                if (!blkmode) {
                    int span = min(endoff - off, MAX_BLOCK_SIZE >> 2);
                    in->readFully(buf, 0, span << 2);
                    stop = off + span;
                    pos = 0;
                } else if (end - pos < 4) {
                    v[off++] = din->readInt();
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

        void BlockDataInputStream::readFloats(jfloat *v, int off, int len) {
            int stop, endoff = off + len;
            while (off < endoff) {
                if (!blkmode) {
                    int span = min(endoff - off, MAX_BLOCK_SIZE >> 2);
                    in->readFully(buf, 0, span << 2);
                    stop = off + span;
                    pos = 0;
                } else if (end - pos < 4) {
                    v[off++] = din->readFloat();
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

        void BlockDataInputStream::readLongs(jlong *v, int off, int len) {
            int stop, endoff = off + len;
            while (off < endoff) {
                if (!blkmode) {
                    int span = min(endoff - off, MAX_BLOCK_SIZE >> 3);
                    in->readFully(buf, 0, span << 3);
                    stop = off + span;
                    pos = 0;
                } else if (end - pos < 8) {
                    v[off++] = din->readLong();
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

        void BlockDataInputStream::readDoubles(jdouble *v, int off, int len) {
            int stop, endoff = off + len;
            while (off < endoff) {
                if (!blkmode) {
                    int span = min(endoff - off, MAX_BLOCK_SIZE >> 3);
                    in->readFully(buf, 0, span << 3);
                    stop = off + span;
                    pos = 0;
                } else if (end - pos < 8) {
                    v[off++] = din->readDouble();
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
            delete din;
        }
    }
}
