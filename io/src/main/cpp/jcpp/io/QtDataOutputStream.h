#ifndef QTDATAOUTPUTSTREAM_H
#define QTDATAOUTPUTSTREAM_H

#include <QDataStream>
#include "JOutputStream.h"

namespace jcpp{
    namespace io{
        class QtDataOutputStream : public JOutputStream{
            QDataStream* out;
        public:
            QtDataOutputStream();
            QtDataOutputStream(QDataStream* out);

            static JClass* getClazz();

            QDataStream* getStream();
            void setStream(QDataStream* in);

            virtual void write(qint32 b);
            virtual void write(qint8 b[]);
            virtual void write(qint8 b[], int off, int len);
            virtual void flush();
            virtual void close();

            virtual void writeBoolean(bool v);
            virtual void writeByte(qint8 v);
            virtual void writeShort(qint16 v);
            virtual void writeChar(quint16 v);
            virtual void writeInt(qint32 v);
            virtual void writeLong(qint64 v);
            virtual void writeFloat(float v);
            virtual void writeDouble(double v);
            virtual ~QtDataOutputStream();
        };
    }
}

#endif // QTDATAOUTPUTSTREAM_H
