#ifndef BLOCKDATAINPUTSTREAM_H
#define BLOCKDATAINPUTSTREAM_H

#include "JInputStream.h"
#include "JObjectStreamConstants.h"
#include "JBits.h"
#include "climits"
#include "memory.h"
#include "Object.h"
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
            char cbuf[CHAR_BUF_SIZE];
            bool blkmode;
            jint pos;
            jint end;
            jint unread;
            JInputStream *in;
            BlockDataInputStream(JInputStream *in);

            bool setBlockDataMode(bool newmode);
            bool getBlockDataMode();
            void skipBlockData();

        private:
            jint readBlockHeader(bool canBlock);
            void refill();

        public:
            jint currentBlockRemaining() ;
            int peek();
            jbyte peekByte();
            void readFully(jbyte *b, int off, int len);
            void readFully(jbyte *b, int off, int len, bool copy);
            string readUTFBody(jlong len);
            string readUTF();
            string readLongUTF();
            void readBools(bool *v, int off, int len);
            void readChars(char *v, int off, int len);
            void readShorts(jshort *v, int off, int len);
            void readInts(jint *v, int off, int len);
            void readFloats(float *v, int off, int len);
            void readLongs(jlong *v, int off, int len);
            void readDoubles(double *v, int off, int len);

            virtual jlong available();
            virtual bool waitForReadyRead(int = 30000);
            virtual jint read();
            virtual jint read(jbyte b[], int off, int len);
            virtual int read(jbyte b[], int off, int len, bool copy);
            virtual jbyte readByte();
            virtual jshort readShort();
            virtual jint readInt();
            virtual jlong readLong();
            virtual float readFloat();
            virtual double readDouble();
            virtual char readChar();
            virtual bool readBool();
            virtual void close();
            virtual ~BlockDataInputStream();
        };
    }
}

#endif // BLOCKDATAINPUTSTREAM_H
