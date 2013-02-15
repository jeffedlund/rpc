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
using namespace std;
using namespace jcpp::lang;
using namespace jcpp::util;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace gateway{
                    class JRoute : public JObject{
                        protected:
                            JArrayList* addressList;
                            JPrimitiveBoolean* bIsHttp;

                        public:
                            JRoute();
                            bool operator==(JObject &other);

                            static JClass* getClazz();

                            void setIsHttp(bool h);

                            bool isHttp();

                            JPrimitiveBoolean* getPIsHttp();

                            void setPIsHttp(JPrimitiveBoolean* h);

                            void addAddress(JAddress* a);

                            void removeAddress(JAddress* a);

                            JArrayList* getAddressList();

                            void setAddressList(JArrayList* al);

                            JAddress* peakAddress();

                            JAddress* popAddress();

                            void pushAddress(JAddress* a);

                            int addressSize();

                            void clearAddress();

                            string toString();

                            ~JRoute();
                    };
                }
            }
        }
    }
}

#endif // JROUTE_H
