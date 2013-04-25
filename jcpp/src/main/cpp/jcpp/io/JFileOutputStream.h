#ifndef JFILEOUTPUTSTREAM_H
#define JFILEOUTPUTSTREAM_H

//include declaration
#include "JOutputStream.h"
#include <QDataStream>
#include <QFile>

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
                JFileOutputStream(string name);//TODO
                virtual void write(jint b);
                virtual void flush();
                virtual void close();
                virtual ~JFileOutputStream();
        };
    }
}

#endif // JFILEOUTPUTSTREAM_H
