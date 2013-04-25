#ifndef JFILEINPUTSTREAM_H
#define JFILEINPUTSTREAM_H

#include "JInputStream.h"
#include "QDataStream"
#include "QFile"
#include "JFile.h"

namespace jcpp{
    namespace io{
        class JFileInputStream : public JInputStream  {
            protected:
                QFile* file;
                QDataStream* in;
                jbool bIsClosed;
                jbool isClosed();
                virtual bool waitForReadyRead(int = 30000);

            public:
                static JClass* getClazz();
                JFileInputStream(string name);
                JFileInputStream(JFile* file);
                virtual jint available();
                virtual jint peek();
                virtual jint read();
                virtual void close();
                virtual ~JFileInputStream();
        };
    }
}

#endif // JFILEINPUTSTREAM_H
