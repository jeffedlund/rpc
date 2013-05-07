#ifndef JFILEINPUTSTREAM_H
#define JFILEINPUTSTREAM_H

#include "JInputStream.h"
#include "QDataStream"
#include "QFile"
#include "JFile.h"
#include "QObjectAware.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JFileInputStream : public JInputStream, public QObjectAware  {
            protected:
                QFile* file;
                QDataStream* in;
                jbool bIsClosed;
                jbool isClosed();
                virtual jbool waitForReadyRead(jint = 30000);

            public:
                static JClass* getClazz();
                JFileInputStream(string name);
                JFileInputStream(JFile* file);
                virtual jint available();
                virtual jint peek();
                virtual jint read();
                virtual void close();
                virtual void takeOwner();
                virtual void releaseOwner();
                virtual QObject* getQObject();
                virtual ~JFileInputStream();
        };
    }
}

#endif // JFILEINPUTSTREAM_H
