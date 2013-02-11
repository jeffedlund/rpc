#ifndef BLOCKDATAOUTPUTSTREAM_H
#define BLOCKDATAOUTPUTSTREAM_H

#include<QtGlobal>
#include "JOutputStream.h"
#include "JDataOutputStream.h"
#include "JBits.h"

namespace jcpp{
    namespace io{
        //TODO implement getClazz,
        class JBlockDataOutputStream : public JOutputStream{
        private:
            static const qint32 MAX_BLOCK_SIZE = 1024;
            static const qint32 MAX_HEADER_SIZE = 5;
            static const qint32 CHAR_BUF_SIZE = 256;

            qint8 buf[MAX_BLOCK_SIZE];
            qint8 hbuf[MAX_HEADER_SIZE];
            quint16 cbuf[CHAR_BUF_SIZE];
            bool blkmode;
            qint32 pos;
            JOutputStream* out;
            JDataOutputStream* dout;
        public:
            JBlockDataOutputStream();
            JBlockDataOutputStream(JOutputStream* out);

            bool setBlockDataMode(bool mode);
            bool getBlockDataMode();
            void write(qint32 b);
            void write(qint8 b[]);
            void write(qint8 b[], int off, int len);
            void flush();
            void close();
            void write(qint8 b[], int off, int len, bool copy);
            void arraycopy(qint8 src[],qint32 srcPos, qint8 dest[], qint32 destPos, qint32 length);
            void drain();
            void writeBlockHeader(int len);
            void writeBoolean(bool v);
            void writeByte(qint8 v);
            void writeShort(qint16 v);
            void writeChar(quint16 v);
            void writeInt(qint32 v);
            void writeLong(qint64 v);
            void writeFloat(float v);
            void writeDouble(double v);
            void writeBytes(std::string s);
            void getChars(std:: string s,qint32 srcBegin, qint32 srcEnd, quint16 dest[], qint32 dstBegin);
            void writeChars(std::string s);
            qint64 getUTFLength(std::string s);
            void writeUTF(std::string s);
            void writeBooleans(bool v[], int off, int len);
            void writeChars(quint16 v[], int off, int len);
            void writeShorts(qint16 v[], int off, int len);
            void writeInts(qint32 v[], int off, int len);
            void writeFloats(float v[], int off, int len);
            void writeLongs(qint64 v[], int off, int len);
            void writeDoubles(double v[], int off, int len);
            void writeUTF(std::string s, qint64 utflen);
            void writeLongUTF(std::string s);
            void writeLongUTF(std::string s, qint64 utflen);
            void writeUTFBody(std::string s);
            ~JBlockDataOutputStream();
        };
    }
}

#endif // BLOCKDATAOUTPUTSTREAM_H
