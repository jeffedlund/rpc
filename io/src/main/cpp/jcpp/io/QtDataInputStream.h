#ifndef QTDATAINPUTSTREAM_H
#define QTDATAINPUTSTREAM_H

#include "JInputStream.h"
#include "QDataStream"
#include "JClass.h"
#include "Object.h"

namespace jcpp{
    namespace io{
        class QtDataInputStream : public JInputStream{
            QDataStream* in;
        public:
            QtDataInputStream();
            QtDataInputStream(QDataStream*);
            static JClass* getClazz();
            QDataStream* getStream();
            void setStream(QDataStream* in);
            virtual jlong available();
            virtual bool waitForReadyRead(int = 30000);
            virtual jint read();
            virtual jint read(jbyte b[], int off, int len);
            virtual jbyte peekByte();
            virtual jbyte readByte();
            virtual jshort readShort();
            virtual jushort readUnsignedShort();
            virtual jint readInt();
            virtual jlong readLong();
            virtual float readFloat();
            virtual double readDouble();
            virtual char readChar();
            virtual bool readBool();
            virtual void close();
            virtual ~QtDataInputStream();
        };
    }
}

#endif // QTDATAINPUTSTREAM_H
