#ifndef QTDATAINPUTSTREAM_H
#define QTDATAINPUTSTREAM_H

#include "JInputStream.h"
#include "JDataInputStream.h"
#include "QDataStream"
#include "JClass.h"
#include "Object.h"
#include "JCPP.h"

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT QtDataInputStream : public JInputStream{
            QDataStream* in;
            vector<jbyte>* bytes;
        public:
            QtDataInputStream();
            QtDataInputStream(QDataStream*);
            static JClass* getClazz();
            QDataStream* getStream();
            void setStream(QDataStream* in);
            virtual jint available();
            virtual bool waitForReadyRead(int = 30000);
            virtual jint peek();
            virtual jint read();
            virtual void close();
            virtual ~QtDataInputStream();
        };
    }
}

#endif // QTDATAINPUTSTREAM_H
