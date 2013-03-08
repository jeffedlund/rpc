#ifndef JCONNECTIONEXCEPTION_H
#define JCONNECTIONEXCEPTION_H

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
#include "JCPP.h"
using namespace std;
using namespace jcpp::lang;
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    class JCPP_LIBRARY_EXPORT JConnectionException : public JException{
                    protected:
                        JConnectionException(JClass* _class);

                    public:
                        JConnectionException();
                        JConnectionException(string message);
                        JConnectionException(string message,JThrowable* cause);

                        static JClass* getClazz();

                        virtual ~JConnectionException();
                    };
                }
            }
        }
    }
}

#endif // JCONNECTIONEXCEPTION_H
