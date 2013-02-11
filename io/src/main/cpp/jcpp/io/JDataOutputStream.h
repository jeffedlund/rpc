#ifndef JDATAOUTPUTSTREAM_H
#define JDATAOUTPUTSTREAM_H

#include <QtGlobal>
#include <QDataStream>
#include "JOutputStream.h"
using namespace std;

namespace jcpp{
    namespace io{
        class JDataOutputStream : public JOutputStream{
        private:
            qint32 length;
            qint8* bytearr;
            void incCount(qint32 value);
            qint8 writeBuffer[8];
        protected:
            JOutputStream* out;
            qint32 written;

        public:
            JDataOutputStream();
            JDataOutputStream(JOutputStream* out);
            static JClass* getClazz();
            void setOutputStream(JOutputStream* out);
            void write(qint32 b);
            void write(qint8 b[], int off, int len);
            void flush() ;
            void close();

            virtual void writeBoolean(bool v);
            virtual void writeByte(qint8 v);
            virtual void writeShort(qint16 v);
            virtual void writeChar(quint16 v);
            virtual void writeInt(qint32 v);
            virtual void writeLong(qint64 v);
            virtual void writeFloat(float v);
            virtual void writeDouble(double v);
            virtual void writeBytes(std::string s);
            virtual void writeChars(std::string s);
            virtual void writeUTF(std::string str);
            qint32 writeUTF(std::string str, JOutputStream* out);
            qint32 size();
            ~JDataOutputStream();
        };
    }
}

#endif // JDATAOUTPUTSTREAM_H
