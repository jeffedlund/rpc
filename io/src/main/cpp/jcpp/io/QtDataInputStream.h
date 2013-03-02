#ifndef QTDATAINPUTSTREAM_H
#define QTDATAINPUTSTREAM_H

#include "JInputStream.h"
#include "JDataInputStream.h"
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
            virtual jbyte peekByte();
            virtual jbyte readByte();
            virtual jbyte read();
            virtual void close();
            virtual ~QtDataInputStream();
        };
    }
}

#endif // QTDATAINPUTSTREAM_H
