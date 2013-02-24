#ifndef JIINVOCATIONEXCEPTIONHANDLER_H
#define JIINVOCATIONEXCEPTIONHANDLER_H

#include "JObject.h"
#include "JClass.h"
#include <vector>
#include <iostream>
#include "JPrimitiveInt.h"
#include "JString.h"
#include "Object.h"
#include "JSerializable.h"
#include "JAddress.h"
#include "JDataInputStream.h"
#include "JDataOutputStream.h"
#include "JEndPoint.h"
#include "JException.h"
#include "JBoolean.h"
using namespace std;
using namespace jcpp::lang;
using namespace jcpp::io;
using namespace jcpp::rmi::server::impl::transport;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    class JIInvocationExceptionHandler : public JInterface{
                    public:
                        static JClass* getClazz();
                        virtual JThrowable* handleException(JObject* object, JMethod* method, JPrimitiveArray* args, JThrowable* exception)=0;
                    };
                }
            }
        }
    }
}

#endif // JIINVOCATIONEXCEPTIONHANDLER_H
