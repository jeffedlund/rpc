#ifndef JCONNECTION_SERIALIZATION_PACKAGE_H
#define JCONNECTION_SERIALIZATION_PACKAGE_H

#include "JCONNECTION_PACKAGE.h"
#include "JDefaultNotSerializableObjectHandler.h"
#include "JINotSerializableObjectHandler.h"
#include "JNullNotSerializableObjectHandler.h"
#include "JCPP.h"

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    namespace serialization{
                        class JCPP_LIBRARY_EXPORT JCONNECTION_SERIALIZATION_PACKAGE : public JPackage{
                        protected:
                            JCONNECTION_SERIALIZATION_PACKAGE();

                        public:
                            JPackage* getSuperPackage();

                            vector<JPackage*>* getPackages();

                            static JCONNECTION_SERIALIZATION_PACKAGE* getPackage();

                            virtual ~JCONNECTION_SERIALIZATION_PACKAGE();
                        };
                    }
                }
            }
        }
    }
}

#endif // JCONNECTION_SERIALIZATION_PACKAGE_H
