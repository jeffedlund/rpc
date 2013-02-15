#ifndef HANDLETABLE_H
#define HANDLETABLE_H

#include "JObject.h"
#include "HandleList.h"
#include "JClassNotFoundException.h"

namespace jcpp{
    namespace io{
        //Input HandleTable
        class HandleTable {
            static const jbyte STATUS_OK = 1;
            static const jbyte STATUS_UNKNOWN = 2;
            static const jbyte STATUS_EXCEPTION = 3;

            jbyte* status;
            JObject** entries;
            HandleList** deps;
            int lowDep;
            int size;
            int length;

            void grow();

        public:

            HandleTable(int initialCapacity);
            ~HandleTable();

            int assign(JObject *obj);
            void markDependency(int dependent, int target);
            void markException(int handle, JClassNotFoundException* ex);
            void setObject(int handle, JObject* obj);
            void finish(int handle);
            int getSize();
            JObject* lookupObject(int handle);
            JClassNotFoundException* lookupException(int handle);
            void clear();
         };
    }
}

#endif // HANDLETABLE_H
