#ifndef IGC_H
#define IGC_H

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
                    class JCPP_LIBRARY_EXPORT JIGC : public JInterface{
                    public:
                        static JClass* getClazz();
                        virtual JPrimitiveArray* ping(JEndPoint* endPoint, JPrimitiveArray* id)=0;
                        virtual void endPointDead(JEndPoint* endPoint)=0;
                        virtual JPrimitiveArray* getExportedEndPoints()=0;
                        virtual ~JIGC();
                    };
                }
            }
        }
    }
}

#endif // IGC_H
