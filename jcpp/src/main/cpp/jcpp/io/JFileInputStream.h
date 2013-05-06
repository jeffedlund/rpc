#ifndef JFILEINPUTSTREAM_H
#define JFILEINPUTSTREAM_H

#include "JInputStream.h"
#include "QDataStream"
#include "QFile"
#include "JFile.h"

//TODO implement qobjectaware
namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JFileInputStream : public JInputStream  {
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
                virtual ~JFileInputStream();
        };
    }
}

#endif // JFILEINPUTSTREAM_H
