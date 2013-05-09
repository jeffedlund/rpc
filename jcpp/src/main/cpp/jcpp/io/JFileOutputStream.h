#ifndef JFILEOUTPUTSTREAM_H
#define JFILEOUTPUTSTREAM_H

#include "JOutputStream.h"
#include <QDataStream>
#include <QFile>
#include "JFile.h"
#include "QObjectAware.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JFileOutputStream : public JOutputStream, public QObjectAware  {
            protected:
                jbool bIsClosed;
                QDataStream* out;
                QFile* file;
                jbool isClosed();

            public:
                static JClass* getClazz();
                JFileOutputStream(JString name,jbool append=false);
                JFileOutputStream(JFile* file,jbool append=false);
                virtual void write(jint b);
                virtual void flush();
                virtual void close();
                virtual void takeOwner();
                virtual void releaseOwner();
                virtual QObject* getQObject();
                virtual ~JFileOutputStream();
        };
    }
}

#endif // JFILEOUTPUTSTREAM_H
