#ifndef JCONNECTION_SERIALIZATION_PACKAGE_H
#define JCONNECTION_SERIALIZATION_PACKAGE_H

#include "JCONNECTION_PACKAGE.h"
#include "JDefaultNotSerializableObjectHandler.h"
#include "JINotSerializableObjectHandler.h"
#include "JNullNotSerializableObjectHandler.h"

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    namespace serialization{
                        class JCONNECTION_SERIALIZATION_PACKAGE : public JPackage{
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
