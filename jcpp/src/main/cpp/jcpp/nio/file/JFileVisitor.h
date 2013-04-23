#ifndef JFILEVISITOR_H
#define JFILEVISITOR_H

#include "JIOException.h"
#include "JObject.h"
#include "JInterface.h"
#include "JFileVisitResult.h"

using namespace jcpp::lang;
using namespace jcpp::io;

namespace jcpp{
    namespace nio{
        namespace file{
            class JFileVisitor : public JInterface  {
                public:
                    static JClass* getClazz();
                    virtual JFileVisitResult * preVisitDirectory(JObject* dir, JObject* attrs)=0;//TODO JBasicFileAttributes
                    virtual JFileVisitResult * visitFile(JObject* file, JObject* attrs)=0;//TODO JBasicFileAttributes
                    virtual JFileVisitResult * visitFileFailed(JObject* file, JIOException* exc)=0;
                    virtual JFileVisitResult * postVisitDirectory(JObject* dir, JIOException* exc)=0;
                    virtual ~JFileVisitor();
            };
        }
    }
}

#endif // JFILEVISITOR_H
