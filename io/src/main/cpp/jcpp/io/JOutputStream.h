#ifndef JOUTPUTSTREAM_H
#define JOUTPUTSTREAM_H

#include <string>
#include "JObject.h"
#include "JClass.h"
#include "Object.h"
using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class JOutputStream : public JObject{
        protected:
            JOutputStream(JClass* _class);

        public:
            JOutputStream();
            static JClass* getClazz();
            virtual void write(jbyte b);
            virtual void write(jbyte b[]);
            virtual void write(jbyte b[], int off, int len);
            virtual void flush();
            virtual void close();

            virtual void writeBoolean(jbool v);
            virtual void writeByte(jbyte v);
            virtual void writeShort(jshort v);
            virtual void writeChar(jchar v);
            virtual void writeInt(jint v);
            virtual void writeLong(jlong v);
            virtual void writeFloat(jfloat v);
            virtual void writeDouble(jdouble v);
            virtual ~JOutputStream();
        };
    }
}

#endif // JOUTPUTSTREAM_H
