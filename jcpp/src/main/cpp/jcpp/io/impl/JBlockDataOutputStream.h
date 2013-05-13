#ifndef BLOCKDATAOUTPUTSTREAM_H
#define BLOCKDATAOUTPUTSTREAM_H

#include "JOutputStream.h"
#include "JDataOutputStream.h"
#include "JBits.h"
#include "Object.h"
#include "JCPP.h"

namespace jcpp{
    namespace io{
        class JObjectOutputStream;
        class JPutFieldImpl;
        class JCPP_LIBRARY_EXPORT JBlockDataOutputStream : public JOutputStream{
        protected:
            static const jint MAX_BLOCK_SIZE = 1024;
            static const jint MAX_HEADER_SIZE = 5;
            static const jint CHAR_BUF_SIZE = 256;

            jbyte* buf;
            jbyte* hbuf;
            jchar* cbuf;
            jbool blkmode;
            jint pos;
            JOutputStream* out;
            JDataOutputStream* dout;
            JBlockDataOutputStream(JOutputStream* out);
            jbool setBlockDataMode(jbool mode);
            jbool getBlockDataMode();
            void write(jbyte b[], jint off, jint len, jbool copy);
            void arraycopy(jbyte src[],jint srcPos, jbyte dest[], jint destPos, jint length);
            void drain();
            void writeBlockHeader(jint len);
            void writeBooleans(jbool v[], jint off, jint len);
            void writeChars(jchar v[], jint off, jint len);
            void writeShorts(jshort v[], jint off, jint len);
            void writeInts(jint v[], jint off, jint len);
            void writeFloats(jfloat v[], jint off, jint len);
            void writeLongs(jlong v[], jint off, jint len);
            void writeDoubles(jdouble v[], jint off, jint len);
            jlong getUTFLength(JString* s);
            void writeUTF(JString* s);
            void writeUTF(JString* s, jlong utflen);
            void writeLongUTF(JString* s);
            void writeLongUTF(JString* s, jlong utflen);
            void writeUTFBody(JString* s);
            void getChars(JString* s,jint srcBegin, jint srcEnd, jchar dest[], jint dstBegin);
            friend class JObjectOutputStream;
            friend class JPutFieldImpl;

        public:
            static JClass* getClazz();
            virtual void write(jint b);
            virtual void write(jbyte b[], jint off, jint len);
            virtual void flush();
            virtual void close();
            void writeBoolean(jbool v);
            void writeByte(jint v);
            void writeShort(jint v);
            void writeChar(jint v);
            void writeInt(jint v);
            void writeLong(jlong v);
            void writeFloat(jfloat v);
            void writeDouble(jdouble v);
            void writeBytes(JString* s);
            void writeChars(JString* s);
            virtual ~JBlockDataOutputStream();
        };
    }
}

#endif // BLOCKDATAOUTPUTSTREAM_H
