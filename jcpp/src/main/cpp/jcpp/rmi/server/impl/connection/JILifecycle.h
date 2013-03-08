#ifndef JILIFECYCLE_H
#define JILIFECYCLE_H

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
#include "JObjectInformation.h"
#include "JCPP.h"
using namespace std;
using namespace jcpp::lang;
using namespace jcpp::io;
using namespace jcpp::rmi::server::impl::transport;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    class JObjectInformation;
                    class JCPP_LIBRARY_EXPORT JILifecycle : public JInterface{
                    public:
                        static JClass* getClazz();
                        virtual void doExport(JObjectInformation* objectInformation)=0;
                        virtual void doExport(JObjectInformation* objectInformation, JEndPoint* endPoint)=0;
                        virtual void unexport(JObjectInformation* objectInformation,JEndPoint* endPoint)=0;
                        virtual void unexport(JObjectInformation* objectInformation)=0;
                        virtual ~JILifecycle();
                    };
                }
            }
        }
    }
}
#endif // JILIFECYCLE_H
