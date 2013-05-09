#ifndef BLOCKDATAINPUTSTREAM_H
#define BLOCKDATAINPUTSTREAM_H

#include "JInputStream.h"
#include "JObjectStreamConstants.h"
#include "JBits.h"
#include "climits"
#include "memory.h"
#include "Object.h"
#include "JDataInputStream.h"
#include "JString.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JBlockDataInputStream : public JInputStream, public JObjectStreamConstants {
        protected:
            jbyte* buf;
            jbyte* hbuf;
            jchar* cbuf;
            jbool blkmode;
            jint pos;
            jint end;
            jint unread;
            JInputStream *in;
            JDataInputStream *din;
            jbool defaultDataEnd;

            JBlockDataInputStream(JInputStream *in);
            jbool setBlockDataMode(jbool newmode);
            jbool getBlockDataMode();
            void skipBlockData();
            jint read(jbyte b[], jint off, jint len, jbool copy);
            JString readLongUTF();
            JString readUTFBody(jlong len);
            void arraycopy(jbyte src[],jint srcPos, jbyte dest[], jint destPos, jint length);
            void readBools(jbool *v, jint off, jint len);
            void readChars(jchar *v, jint off, jint len);
            void readShorts(jshort *v, jint off, jint len);
            void readInts(jint *v, jint off, jint len);
            void readFloats(jfloat *v, jint off, jint len);
            void readLongs(jlong *v, jint off, jint len);
            void readDoubles(jdouble *v, jint off, jint len);
            jlong readUTFSpan(vector<jchar>* sbuf, jlong utflen);
            jint readUTFChar(vector<jchar>* sbuf, jlong utflen);
            jint readBlockHeader(jbool canBlock);
            void refill();
            jint currentBlockRemaining() ;
            jbool isDefaultDataEnd();
            void setDefaultDataEnd(jbool defaultDataEnd);
            friend class JObjectInputStream;

        public:
            static JClass* getClazz();
            virtual jint peek();
            virtual jint read();
            virtual jint read(jbyte b[], jint off, jint len);
            virtual jlong skip(jlong len);
            virtual jint available();
            virtual void close();
            virtual void readFully(jbyte *b, jint off, jint len);
            virtual void readFully(jbyte *b, jint off, jint len, jbool copy);
            virtual jint skipBytes(jint n);
            virtual jbool readBool();
            virtual jbyte readByte();
            virtual jbyte readUnsignedByte();
            virtual jchar readChar();
            virtual jshort readShort();
            virtual jshort readUnsignedShort();
            virtual jint readInt();
            virtual jfloat readFloat();
            virtual jlong readLong();
            virtual jdouble readDouble();
            virtual JString readUTF();
            virtual ~JBlockDataInputStream();
        };
    }
}

#endif // BLOCKDATAINPUTSTREAM_H
