#ifndef JSTRINGBUILDER_H
#define JSTRINGBUILDER_H

#include "JStringBuffer.h"
#include "JAppendable.h"
#include "JString.h"
#include "JCharSequence.h"
#include "JSerializable.h"
#include "JAbstractStringBuilder.h"
#include "JObject.h"
#include "JObjectOutputStream.h"
#include "JObjectInputStream.h"

using namespace jcpp::io;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JStringBuilder : public JAbstractStringBuilder  , public JSerializable{
            protected:
                virtual void writeObject(JObjectOutputStream* out);
                virtual void readObject(JObjectInputStream* in);
                friend class JStringBuilderClass;

            public:
                static JClass* getClazz();
                JStringBuilder();
                JStringBuilder(JString str);
                JStringBuilder(JCharSequence* seq);
                virtual JStringBuilder* append(JObject* o);
                virtual JStringBuilder* append(JString* o);
                virtual JStringBuilder* append(JString str);
                virtual JStringBuilder* append(JStringBuffer* sb);
                virtual JStringBuilder* append(JCharSequence* sq);
                virtual JStringBuilder* append(JCharSequence* sq,jint start,jint end);
                virtual JStringBuilder* append(jchar str[],jint offset,jint len);
                virtual JStringBuilder* append(JString str,jint offset,jint len);
                virtual JStringBuilder* append(jbool b);
                virtual JStringBuilder* append(jchar c);
                virtual JStringBuilder* append(jint i);
                virtual JStringBuilder* append(jlong l);
                virtual JStringBuilder* append(jfloat f);
                virtual JStringBuilder* append(jdouble d);
                virtual JStringBuilder* deleteChar(jint start,jint end);
                virtual JStringBuilder* deleteCharAt(jint index);
                virtual JStringBuilder* replace(jint start,jint end,JString* str);
                virtual JStringBuilder* insert(jint index,jchar str[],jint offset,jint len);
                virtual JStringBuilder* insert(jint offset,JObject* o);
                virtual JStringBuilder* insert(jint offset,JString* str);
                virtual JStringBuilder* insert(jint offset,JString str);
                virtual JStringBuilder* insert(jint offset,jchar str[],jint l);
                virtual JStringBuilder* insert(jint offset,JCharSequence* s);
                virtual JStringBuilder* insert(jint offset,JCharSequence* s,jint start,jint end);
                virtual JStringBuilder* insert(jint offset,jbool b);
                virtual JStringBuilder* insert(jint offset,jchar c);
                virtual JStringBuilder* insert(jint offset,jint i);
                virtual JStringBuilder* insert(jint offset,jlong l);
                virtual JStringBuilder* insert(jint offset,jfloat f);
                virtual JStringBuilder* insert(jint offset,jdouble d);
                virtual JStringBuilder* reverse();
                virtual ~JStringBuilder();
        };
    }
}

#endif // JSTRINGBUILDER_H
