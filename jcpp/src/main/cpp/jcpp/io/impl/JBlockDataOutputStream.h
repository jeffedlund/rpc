#ifndef BLOCKDATAOUTPUTSTREAM_H
#define BLOCKDATAOUTPUTSTREAM_H

#include "JOutputStream.h"
#include "JDataOutputStream.h"
#include "JBits.h"
#include "Object.h"
#include "JCPP.h"

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JBlockDataOutputStream : public JOutputStream{
        private:
            static const jint MAX_BLOCK_SIZE = 1024;
            static const jint MAX_HEADER_SIZE = 5;
            static const jint CHAR_BUF_SIZE = 256;

            jbyte buf[MAX_BLOCK_SIZE];
            jbyte hbuf[MAX_HEADER_SIZE];
            jchar cbuf[CHAR_BUF_SIZE];
            bool blkmode;
            jint pos;
            JOutputStream* out;
            JDataOutputStream* dout;

        public:
            JBlockDataOutputStream();
            JBlockDataOutputStream(JOutputStream* out);
            static JClass* getClazz();

            bool setBlockDataMode(bool mode);
            bool getBlockDataMode();
            void write(jint b);
            void write(jbyte b[], int off, int len);
            void flush();
            void close();
            void write(jbyte b[], int off, int len, bool copy);
            void arraycopy(jbyte src[],jint srcPos, jbyte dest[], jint destPos, jint length);
            void drain();
            void writeBlockHeader(jint len);
            void writeBoolean(jbool v);
            void writeByte(jint v);
            void writeShort(jint v);
            void writeChar(jint v);
            void writeInt(jint v);
            void writeLong(jlong v);
            void writeFloat(jfloat v);
            void writeDouble(jdouble v);
            void writeBytes(string s);
            void getChars(string s,jint srcBegin, jint srcEnd, jchar dest[], jint dstBegin);
            void writeChars(string s);
            jlong getUTFLength(string s);
            void writeUTF(string s);
            void writeBooleans(jbool v[], int off, int len);
            void writeChars(jchar v[], int off, int len);
            void writeShorts(jshort v[], int off, int len);
            void writeInts(jint v[], int off, int len);
            void writeFloats(jfloat v[], int off, int len);
            void writeLongs(jlong v[], int off, int len);
            void writeDoubles(jdouble v[], int off, int len);
            void writeUTF(string s, jlong utflen);
            void writeLongUTF(string s);
            void writeLongUTF(string s, jlong utflen);
            void writeUTFBody(string s);
            virtual ~JBlockDataOutputStream();
        };
    }
}

#endif // BLOCKDATAOUTPUTSTREAM_H
