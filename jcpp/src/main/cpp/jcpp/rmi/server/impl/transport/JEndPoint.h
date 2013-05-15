#ifndef JENDPOINT_H
#define JENDPOINT_H

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
#include "JCPP.h"
using namespace std;
using namespace jcpp::lang;
using namespace jcpp::io;
using namespace jcpp::rmi::server::impl::gateway;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace transport{
                    class JCPP_LIBRARY_EXPORT JEndPoint : public JObject, public JSerializable{
                        protected:
                            JAddress* address;
                            JString* site;

                        public:
                            struct POINTER_COMPARATOR{//TODO better way?
                                jbool operator()(JEndPoint* e1, JEndPoint* e2){
                                    return (*e1)<(*e2);
                                }
                            };
                            JEndPoint();
                            JEndPoint(JDataInputStream* in);
                            JEndPoint(JAddress* a, JString* s);
                            jbool operator<(JEndPoint &other);
                            static JClass* getClazz();
                            void write(JDataOutputStream* out);
                            void setAddress(JAddress* a);
                            JAddress* getAddress();
                            void setSite(JString* site);
                            JString* getSite();
                            virtual jbool equals(JObject* other);
                            virtual jint hashCode();
                            virtual JString toString();
                            virtual ~JEndPoint();
                    };
                }
            }
        }
    }
}

#endif // JENDPOINT_H
