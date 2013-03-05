#ifndef BLOCKDATAINPUTSTREAM_H
#define BLOCKDATAINPUTSTREAM_H

#include "JInputStream.h"
#include "JObjectStreamConstants.h"
#include "JBits.h"
#include "climits"
#include "memory.h"
#include "Object.h"
#include "JDataInputStream.h"
using namespace std;

static const jint MAX_BLOCK_SIZE = 1024;
static const jint MAX_HEADER_SIZE = 5;
static const jint CHAR_BUF_SIZE = 256;
static const jint HEADER_BLOCKED = -2;

namespace jcpp{
    namespace io{
        class BlockDataInputStream : public JInputStream, public JObjectStreamConstants {
        public:
            jbyte buf[MAX_BLOCK_SIZE];
            jbyte hbuf[MAX_HEADER_SIZE];
            jchar cbuf[CHAR_BUF_SIZE];
            bool blkmode;
            jint pos;
            jint end;
            jint unread;
            JInputStream *in;
            JDataInputStream *din;
            bool defaultDataEnd;
            BlockDataInputStream(JInputStream *in);

            bool setBlockDataMode(bool newmode);
            bool getBlockDataMode();
            void skipBlockData();

        private:
            jint readBlockHeader(bool canBlock);
            void refill();

        public:
            jint currentBlockRemaining() ;
            bool isDefaultDataEnd();
            void setDefaultDataEnd(bool defaultDataEnd);
            jbyte peek();
            jbyte peekByte();
            void readFully(jbyte *b, int off, int len);
            void readFully(jbyte *b, int off, int len, bool copy);
            jint skipBytes(jint n);
            string readUTFBody(jlong len);
            jlong readUTFSpan(vector<jchar>* sbuf, jlong utflen);
            jint readUTFChar(vector<jchar>* sbuf, jlong utflen);
            string readUTF();
            string readLongUTF();
            void arraycopy(jbyte src[],jint srcPos, jbyte dest[], jint destPos, jint length);
            void readBools(jbool *v, int off, int len);
            void readChars(jchar *v, int off, int len);
            void readShorts(jshort *v, int off, int len);
            void readInts(jint *v, int off, int len);
            void readFloats(jfloat *v, int off, int len);
            void readLongs(jlong *v, int off, int len);
            void readDoubles(jdouble *v, int off, int len);

            jlong skip(jlong len);//TODO put it everywhere in io
            virtual jlong available();
            virtual bool waitForReadyRead(int = 30000);
            virtual jbyte read();
            virtual jint read(jbyte b[], int off, int len);
            virtual int read(jbyte b[], int off, int len, bool copy);
            virtual jbyte readUnsignedByte();
            virtual jbyte readByte();
            virtual jshort readShort();
            virtual jshort readUnsignedShort();
            virtual jint readInt();
            virtual jlong readLong();
            virtual jfloat readFloat();
            virtual jdouble readDouble();
            virtual jchar readChar();
            virtual jbool readBool();
            virtual void close();
            virtual ~BlockDataInputStream();
        };
    }
}

#endif // BLOCKDATAINPUTSTREAM_H
