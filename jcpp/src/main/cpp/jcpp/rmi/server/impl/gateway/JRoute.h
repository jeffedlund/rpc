#ifndef JROUTE_H
#define JROUTE_H

#include "JObject.h"
#include "JClass.h"
#include <vector>
#include <iostream>
#include "JPrimitiveBoolean.h"
#include "JArrayList.h"
#include "JString.h"
#include "Object.h"
#include "JAddress.h"
#include "JSerializable.h"
#include "JCPP.h"
using namespace std;
using namespace jcpp::lang;
using namespace jcpp::util;
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace gateway{
                    class JCPP_LIBRARY_EXPORT JRoute : public JObject, public JSerializable, public JCloneable{
                        protected:
                            JArrayList* addressList;
                            JPrimitiveBoolean* bIsHttp;
                            JPrimitiveBoolean* getPIsHttp();
                            void setPIsHttp(JPrimitiveBoolean* h);
                            friend class JRouteClass;

                        public:
                            JRoute();
                            static JClass* getClazz();
                            virtual void setIsHttp(jbool h);
                            virtual jbool isHttp();
                            virtual void addAddress(JAddress* a);
                            virtual void removeAddress(JAddress* a);
                            virtual JArrayList* getAddressList();
                            virtual void setAddressList(JArrayList* al);
                            virtual JAddress* peakAddress();
                            virtual JAddress* popAddress();
                            virtual void pushAddress(JAddress* a);
                            virtual jint addressSize();
                            virtual void clearAddress();
                            virtual jbool equals(JObject* other);
                            virtual JRoute* clone();
                            virtual JString toString();
                            virtual ~JRoute();
                    };
                }
            }
        }
    }
}

#endif // JROUTE_H
