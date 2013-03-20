#ifndef JOBJECTPOINTER_H
#define JOBJECTPOINTER_H

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
#include "JCPP.h"
using namespace std;
using namespace jcpp::lang;
using namespace jcpp::io;
using namespace jcpp::rmi::server::impl::gateway;
using namespace jcpp::rmi::server::impl::transport;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    class JCPP_LIBRARY_EXPORT JObjectPointer : public JObject, public JSerializable{
                        public:
                            struct POINTER_COMPARATOR{
                                bool operator()(JObjectPointer* e1, JObjectPointer* e2){
                                    if ((*e1->getEndPoint())<(*e2->getEndPoint())){
                                        if ((*e1->getId())<(*e2->getId())){
                                            return true;
                                        }
                                    }
                                    return false;
                                }
                            };

                        protected:
                            JEndPoint* endPoint;
                            JString* id;

                        public:
                            JObjectPointer();
                            JObjectPointer(JEndPoint* endPoint, JString* id);
                            static JClass* getClazz();
                            JEndPoint* getEndPoint();
                            void setEndPoint(JEndPoint* endPoint);
                            JString* getId();
                            void setId(JString* id);
                            virtual bool equals(JObject* other);
                            virtual string toString();
                            virtual ~JObjectPointer();
                    };
                }
            }
        }
    }
}

#endif // JOBJECTPOINTER_H
