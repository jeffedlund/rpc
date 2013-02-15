#ifndef BLOCKDATAOUTPUTSTREAM_H
#define BLOCKDATAOUTPUTSTREAM_H

#include "JOutputStream.h"
#include "JDataOutputStream.h"
#include "JBits.h"
#include "Object.h"

namespace jcpp{
    namespace io{
        //TODO implement getClazz,
        class JBlockDataOutputStream : public JOutputStream{
        private:
            static const jint MAX_BLOCK_SIZE = 1024;
            static const jint MAX_HEADER_SIZE = 5;
            static const jint CHAR_BUF_SIZE = 256;

            jbyte buf[MAX_BLOCK_SIZE];
            jbyte hbuf[MAX_HEADER_SIZE];
            jushort cbuf[CHAR_BUF_SIZE];
            bool blkmode;
            jint pos;
            JOutputStream* out;
            JDataOutputStream* dout;
        public:
            JBlockDataOutputStream();
            JBlockDataOutputStream(JOutputStream* out);

            bool setBlockDataMode(bool mode);
            bool getBlockDataMode();
            void write(jint b);
            void write(jbyte b[]);
            void write(jbyte b[], int off, int len);
            void flush();
            void close();
            void write(jbyte b[], int off, int len, bool copy);
            void arraycopy(jbyte src[],jint srcPos, jbyte dest[], jint destPos, jint length);
            void drain();
            void writeBlockHeader(int len);
            void writeBoolean(bool v);
            void writeByte(jbyte v);
            void writeShort(jshort v);
            void writeChar(jushort v);
            void writeInt(jint v);
            void writeLong(jlong v);
            void writeFloat(float v);
            void writeDouble(double v);
            void writeBytes(std::string s);
            void getChars(std:: string s,jint srcBegin, jint srcEnd, jushort dest[], jint dstBegin);
            void writeChars(std::string s);
            jlong getUTFLength(std::string s);
            void writeUTF(std::string s);
            void writeBooleans(bool v[], int off, int len);
            void writeChars(jushort v[], int off, int len);
            void writeShorts(jshort v[], int off, int len);
            void writeInts(jint v[], int off, int len);
            void writeFloats(float v[], int off, int len);
            void writeLongs(jlong v[], int off, int len);
            void writeDoubles(double v[], int off, int len);
            void writeUTF(std::string s, jlong utflen);
            void writeLongUTF(std::string s);
            void writeLongUTF(std::string s, jlong utflen);
            void writeUTFBody(std::string s);
            ~JBlockDataOutputStream();
        };
    }
}

#endif // BLOCKDATAOUTPUTSTREAM_H
