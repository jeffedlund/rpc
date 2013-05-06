#ifndef QTDATAOUTPUTSTREAM_H
#define QTDATAOUTPUTSTREAM_H

#include <QDataStream>
#include <QFile>
#include <QAbstractSocket>
#include "JOutputStream.h"
#include "Object.h"
#include "JCPP.h"

//TODO remove
namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT QtDataOutputStream : public JOutputStream{
            jbool bIsClosed;
            QDataStream* out;
            QFile* file;
            QAbstractSocket* socket;
            vector<jbyte>* bytes;
            jbool isClosed();

        public:
            QtDataOutputStream();
            QtDataOutputStream(QDataStream* out,QFile* file);
            QtDataOutputStream(QDataStream* out,QAbstractSocket* socket);

            static JClass* getClazz();

            QDataStream* getStream();
            void setStream(QDataStream* in);

            virtual void write(jint b);
            virtual void flush();
            virtual void close();
            virtual ~QtDataOutputStream();
        };
    }
}

#endif // QTDATAOUTPUTSTREAM_H
