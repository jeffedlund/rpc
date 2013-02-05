#ifndef JOUTPUTSTREAM_H
#define JOUTPUTSTREAM_H

#include<QtGlobal>
#include <string>
#include "JObject.h"
#include "JClass.h"


class JOutputStream : public JObject{
protected:
    JOutputStream(JClass* _class);

public:
    JOutputStream();
    static JClass* getClazz();
    virtual void write(qint32 b);
    virtual void write(qint8 b[]);
    virtual void write(qint8 b[], int off, int len);
    virtual void flush();
    virtual void close();

    virtual void writeBoolean(bool v);
    virtual void writeByte(qint8 v);
    virtual void writeShort(qint16 v);
    virtual void writeChar(quint16 v);
    virtual void writeInt(qint32 v);
    virtual void writeLong(qint64 v);
    virtual void writeFloat(float v);
    virtual void writeDouble(double v);
    ~JOutputStream(){}
};

#endif // JOUTPUTSTREAM_H
