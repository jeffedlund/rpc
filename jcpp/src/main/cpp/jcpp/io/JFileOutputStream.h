#ifndef JFILEOUTPUTSTREAM_H
#define JFILEOUTPUTSTREAM_H

#include "JOutputStream.h"
#include <QDataStream>
#include <QFile>
#include "JFile.h"

namespace jcpp{
    namespace io{
        class JFileOutputStream : public JOutputStream  {
            protected:
                jbool bIsClosed;
                QDataStream* out;
                QFile* file;
                jbool isClosed();

            public:
                static JClass* getClazz();
                JFileOutputStream(string name,jbool append=false);
                JFileOutputStream(JFile* file,jbool append=false);
                virtual void write(jint b);
                virtual void flush();
                virtual void close();
                virtual ~JFileOutputStream();
        };
    }
}

#endif // JFILEOUTPUTSTREAM_H
