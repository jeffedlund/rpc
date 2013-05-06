#ifndef HANDLETABLE_H
#define HANDLETABLE_H

#include "JObject.h"
#include "HandleList.h"
#include "JClassNotFoundException.h"

namespace jcpp{
    namespace io{
        class HandleTable {
            static const jbyte STATUS_OK = 1;
            static const jbyte STATUS_UNKNOWN = 2;
            static const jbyte STATUS_EXCEPTION = 3;

            jbyte* status;
            JObject** entries;
            HandleList** deps;
            jint lowDep;
            jint size;
            jint length;
            void grow();

        public:

            HandleTable(jint initialCapacity);
            jint assign(JObject* obj);
            void markDependency(jint dependent, jint target);
            void markException(jint handle, JClassNotFoundException* ex);
            void setObject(jint handle, JObject* obj);
            void finish(jint handle);
            jint getSize();
            JObject* lookupObject(jint handle);
            JClassNotFoundException* lookupException(jint handle);
            void clear();
            ~HandleTable();
         };
    }
}

#endif // HANDLETABLE_H
