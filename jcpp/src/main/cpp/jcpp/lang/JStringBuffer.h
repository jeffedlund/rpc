#ifndef JSTRINGBUFFER_H
#define JSTRINGBUFFER_H

#include "JCharSequence.h"
#include "JAppendable.h"
#include "JSerializable.h"
#include "JAbstractStringBuilder.h"
#include "JObject.h"
#include "JString.h"

using namespace jcpp::io;

namespace jcpp{
    namespace lang{
        class JStringBuffer : public JAbstractStringBuilder  , public JSerializable{
            public:
                static JClass* getClazz();
                JStringBuffer();
                JStringBuffer(JString* str);
                JStringBuffer(string str);
                JStringBuffer(JCharSequence* cs);
                virtual jint length();
                virtual jint capacity();
                virtual void ensureCapacity(jint c);
                virtual void trimToSize();
                virtual void setLength(jint l);
                virtual jchar charAt(jint index);
                virtual void getChars(jint srcBegin,jint srcEnd,jchar dst[],jint dstBegin);
                virtual void setCharAt(jint index,jchar c);
                virtual JStringBuffer* append(JObject* o);
                virtual JStringBuffer* append(JString* o);
                virtual JStringBuffer* append(string str);
                virtual JStringBuffer* append(JStringBuffer* sb);
                virtual JStringBuffer* append(JCharSequence* s);
                virtual JStringBuffer* append(JCharSequence* s,jint start,jint end);
                virtual JStringBuffer* append(jchar str[],jint offset,jint length);
                virtual JStringBuffer* append(jbool b);
                virtual JStringBuffer* append(jchar c);
                virtual JStringBuffer* append(jint i);
                virtual JStringBuffer* append(jlong l);
                virtual JStringBuffer* append(jfloat f);
                virtual JStringBuffer* append(jdouble d);
                virtual JStringBuffer* deleteChar(jint start,jint end);
                virtual JStringBuffer* deleteCharAt(jint index);
                virtual JStringBuffer* replace(jint start,jint end,JString* str);
                virtual JString* substring(jint start);
                virtual JCharSequence* subSequence(jint start,jint end);
                virtual JString* substring(jint start,jint end);
                virtual JStringBuffer* insert(jint index,jchar str[],jint offset,jint len);
                virtual JStringBuffer* insert(jint offset,JObject* o);
                virtual JStringBuffer* insert(jint offset,JString* str);
                virtual JStringBuffer* insert(jint offset,string str);
                virtual JStringBuffer* insert(jint offset,jchar str[],jint l);
                virtual JStringBuffer* insert(jint offset,JCharSequence* s);
                virtual JStringBuffer* insert(jint offset,JCharSequence* s,jint start,jint end);
                virtual JStringBuffer* insert(jint offset,jbool b);
                virtual JStringBuffer* insert(jint offset,jchar c);
                virtual JStringBuffer* insert(jint offset,jint i);
                virtual JStringBuffer* insert(jint offset,jlong l);
                virtual JStringBuffer* insert(jint offset,jfloat f);
                virtual JStringBuffer* insert(jint offset,jdouble d);
                virtual jint indexOf(JString* str);
                virtual jint indexOf(JString* str,jint fromIndex);
                virtual jint lastIndexOf(JString* str);
                virtual jint lastIndexOf(JString* str,jint fromIndex);
                virtual JStringBuffer* reverse();
                virtual string toString();
                virtual ~JStringBuffer();
        };
    }
}

#endif // JSTRINGBUFFER_H
