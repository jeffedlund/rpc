#ifndef QTDATAOUTPUTSTREAM_H
#define QTDATAOUTPUTSTREAM_H

#include <QDataStream>
#include <QFile>
#include "JOutputStream.h"
#include "Object.h"

namespace jcpp{
    namespace io{
        class QtDataOutputStream : public JOutputStream{
            QDataStream* out;
            QFile* file;
        public:
            QtDataOutputStream();
            QtDataOutputStream(QDataStream* out,QFile* file);

            static JClass* getClazz();

            QDataStream* getStream();
            void setStream(QDataStream* in);

            virtual void write(jint b);
            virtual void write(jbyte b[]);
            virtual void write(jbyte b[], int off, int len);
            virtual void flush();
            virtual void close();

            virtual void writeBoolean(bool v);
            virtual void writeByte(jbyte v);
            virtual void writeShort(jshort v);
            virtual void writeChar(jushort v);
            virtual void writeInt(jint v);
            virtual void writeLong(jlong v);
            virtual void writeFloat(float v);
            virtual void writeDouble(double v);
            virtual ~QtDataOutputStream();
        };
    }
}

#endif // QTDATAOUTPUTSTREAM_H
