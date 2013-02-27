#ifndef QTDATAOUTPUTSTREAM_H
#define QTDATAOUTPUTSTREAM_H

#include <QDataStream>
#include <QFile>
#include <QAbstractSocket>
#include "JOutputStream.h"
#include "Object.h"

namespace jcpp{
    namespace io{
        class QtDataOutputStream : public JOutputStream{
            QDataStream* out;
            QFile* file;
            QAbstractSocket* socket;
        public:
            QtDataOutputStream();
            QtDataOutputStream(QDataStream* out,QFile* file);
            QtDataOutputStream(QDataStream* out,QAbstractSocket* socket);

            static JClass* getClazz();

            QDataStream* getStream();
            void setStream(QDataStream* in);

            virtual void write(jbyte b);
            virtual void write(jbyte b[]);
            virtual void write(jbyte b[], int off, int len);
            virtual void flush();
            virtual void close();

            virtual void writeBoolean(jbool v);
            virtual void writeByte(jbyte v);
            virtual void writeShort(jshort v);
            virtual void writeChar(jchar v);
            virtual void writeInt(jint v);
            virtual void writeLong(jlong v);
            virtual void writeFloat(jfloat v);
            virtual void writeDouble(jdouble v);
            virtual ~QtDataOutputStream();
        };
    }
}

#endif // QTDATAOUTPUTSTREAM_H
