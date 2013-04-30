#ifndef JIPACKAGELOADER_H
#define JIPACKAGELOADER_H

#include "JPackage.h"

namespace jcpp{
    namespace lang{
        namespace reflect{
            class JIPackageLoader{
                public:
                    virtual JPackage* getPackage() = 0;
                    virtual ~JIPackageLoader() {
                    }
            };
        }
    }
}

Q_DECLARE_INTERFACE(jcpp::lang::reflect::JIPackageLoader,"jipackageloader")

#endif // JIPACKAGELOADER_H
