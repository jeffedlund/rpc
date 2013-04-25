#ifndef JPATH_H
#define JPATH_H

#include "JString.h"
#include "JWatchEvent.h"
#include "JIterable.h"
#include "JObject.h"
#include "JWatchable.h"
#include "JWatchService.h"
#include "JIterator.h"
#include "JComparable.h"
#include "JPath.h"
#include "JInterface.h"
#include "JWatchKey.h"
#include "JLinkOption.h"

using namespace jcpp::util;
using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class JFile;
    }
    namespace nio{
        namespace file{
            class JFileSystem;
            class JPath : public JComparable  , public JIterable  , public JWatchable  {
                public:
                    static JClass* getClazz();
                    virtual JFileSystem* getFileSystem()=0;
                    virtual jbool isAbsolute()=0;
                    virtual JPath* getRoot()=0;
                    virtual JPath* getFileName()=0;
                    virtual JPath* getParent()=0;
                    virtual jint getNameCount()=0;
                    virtual JPath* getName(jint name)=0;
                    virtual JPath* subpath(jint begin, jint end)=0;
                    virtual jbool startsWith(JPath* other)=0;
                    virtual jbool startsWith(string other)=0;
                    virtual jbool endsWith(JPath* other)=0;
                    virtual jbool endsWith(string other)=0;
                    virtual JPath* normalize()=0;
                    virtual JPath* resolve(JPath* other)=0;
                    virtual JPath* resolve(string other)=0;
                    virtual JPath* resolveSibling(JPath* other)=0;
                    virtual JPath* resolveSibling(string other)=0;
                    virtual JPath* relativize(JPath* other)=0;
                    //TODO virtual JURI* toUri()=0;
                    virtual JPath* toAbsolutePath()=0;
                    virtual JPath* toRealPath(vector<JLinkOption*>* options)=0;
                    virtual JFile * toFile()=0;
                    virtual ~JPath();
            };
        }
    }
}

#endif // JPATH_H
