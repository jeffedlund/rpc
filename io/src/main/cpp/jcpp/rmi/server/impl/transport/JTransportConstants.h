#ifndef JTRANSPORTCONSTANTS_H
#define JTRANSPORTCONSTANTS_H

#include "Object.h"

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace transport{
                    static jbyte MSG_TYPE_PING = (jbyte) 0x11;
                    static jbyte MSG_TYPE_CALL = (jbyte) 0x21;
                    static jbyte MSG_TYPE_OK = (jbyte) 0x31;
                    static jbyte MSG_TYPE_EXCEPTION = (jbyte) 0x41;
                    static jint MAGIC_NUMBER = 0x4d524d49;
                }
            }
        }
    }
}

#endif // JTRANSPORTCONSTANTS_H
