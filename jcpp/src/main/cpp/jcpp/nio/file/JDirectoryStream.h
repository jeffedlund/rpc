#ifndef JDIRECTORYSTREAM_H
#define JDIRECTORYSTREAM_H

#include "JIterator.h"
#include "JIterable.h"
#include "JInterface.h"
#include "JCloseable.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::util;

namespace jcpp{
    namespace nio{
        namespace file{
            class JCPP_LIBRARY_EXPORT JDirectoryStream : public JCloseable  , public JIterable  {
                public:
                    class JCPP_LIBRARY_EXPORT JFilter : public JInterface{
                    public:
                        static JClass* getClazz();
                        virtual jbool accept(JObject* entry)=0;
                        virtual ~JFilter();
                    };

                    static JClass* getClazz();
                    virtual JIterator* iterator()=0;
                    virtual ~JDirectoryStream();
            };
        }
    }
}

#endif // JDIRECTORYSTREAM_H
