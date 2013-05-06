#ifndef HANDLELIST_H
#define HANDLELIST_H

#include "Object.h"

namespace jcpp{
    namespace io{
        class HandleList {
        protected:
            jint* list;
            jint length;
            jint size;
        public:
            HandleList();
            HandleList(const HandleList &h);
            void add(jint handle);
            jint get(jint index);
            jint getSize();
            ~HandleList();
        };
    }
}

#endif // HANDLELIST_H
