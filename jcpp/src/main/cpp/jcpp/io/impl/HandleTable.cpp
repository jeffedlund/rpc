#include "HandleTable.h"
#include "JObject.h"
#include "memory.h"
#include "JObjectInputStream.h"
#include "JInternalError.h"

namespace jcpp{
    namespace io{
        void HandleTable::grow() {
            jint newCapacity = (length*2) +1;

            jbyte *newStatus = new jbyte[newCapacity];
            JObject **newEntries = new JObject*[newCapacity];
            HandleList **newDeps = new HandleList*[newCapacity];

            memcpy(newStatus, status, size * sizeof(jbyte));
            delete[] status;
            memcpy(newEntries, entries, size * sizeof(JObject*));
            delete[] entries;
            memcpy(newDeps, deps, size * sizeof(HandleList*));
            delete[] deps;

            status = newStatus;
            entries = newEntries;
            deps = newDeps;
            for (jint i = length; i < newCapacity; ++i) {
                status[i] = (jbyte) 0;
                entries[i] = NULL;
                deps[i] = NULL;
            }
            length = newCapacity;
        }

        HandleTable::HandleTable(jint initialCapacity) {
            length = initialCapacity;
            lowDep = -1;
            size = 0;
            status = new jbyte[initialCapacity];
            entries = new JObject*[initialCapacity];
            deps = new HandleList*[initialCapacity];

            // initialize
            for (jint i = 0; i < initialCapacity; ++i) {
                status[i] = (jbyte) 0;
                entries[i] = NULL;
                deps[i] = NULL;
            }
        }

        HandleTable::~HandleTable() {
            delete[] status;
            for (jint i = 0; i < size; ++i) {
                delete deps[i];
            }
            delete[] entries;
            delete[] deps;
        }

        jint HandleTable::assign(JObject *obj) {
            if (size >= length) {
                grow();
            }
            status [size] = STATUS_UNKNOWN;
            entries[size] = obj;
            return size++;
        }

        void HandleTable::markDependency(jint dependent, jint target) {
            if (dependent == NULL_HANDLE || target == NULL_HANDLE) {
                return;
            }
            switch (status[dependent]) {
                case STATUS_UNKNOWN:
                    switch (status[target]) {
                    case STATUS_OK:
                        break;

                    case STATUS_EXCEPTION:
                        markException(dependent,(JClassNotFoundException*) entries[target]);
                        break;

                    case STATUS_UNKNOWN:
                        if (deps[target] == NULL) {
                            deps[target] = new HandleList;
                        }
                        deps[target]->add(dependent);

                        if (lowDep < 0 || lowDep > target) {
                            lowDep = target;
                        }
                        break;

                    default:
                        throw new JInternalError();
                    }
                    break;

                case STATUS_EXCEPTION:
                    break;

                default:
                    throw new JInternalError();
                }
        }

        void HandleTable::markException(jint handle, JClassNotFoundException* ex) {
            switch (status[handle]) {
                case STATUS_UNKNOWN:
                {
                    status[handle] = STATUS_EXCEPTION;
                    entries[handle] = ex;

                    HandleList *dlist = deps[handle];
                    if (dlist != NULL) {
                        jint ndeps = dlist->getSize();
                        for (jint i = 0; i < ndeps; ++i) {
                            markException(dlist->get(i), ex);
                        }
                        delete deps[handle];
                        deps[handle] = NULL;
                    }
                }
                    break;

                case STATUS_EXCEPTION:
                    break;

                default:
                    throw new JInternalError();
            }
        }

        void HandleTable::setObject(jint handle, JObject* obj) {
            switch (status[handle]) {
            case STATUS_UNKNOWN:
            case STATUS_OK:
                entries[handle] = obj;
                break;

            case STATUS_EXCEPTION:
                break;

            default:
                throw new JInternalError();
            }
        }

        void HandleTable::finish(jint handle) {
            jint end = 0;
            if (lowDep < 0) {
                end = handle + 1;
            } else if (lowDep >= handle) {
                end = size;
                lowDep = -1;
            } else {
                return;
            }

            for (jint i = handle; i < end; i++) {
                switch (status[i]) {
                case STATUS_UNKNOWN:
                    status[i] = STATUS_OK;
                    delete deps[i];
                    deps[i] = NULL;
                    break;

                case STATUS_OK:
                case STATUS_EXCEPTION:
                    break;

                default:
                    throw new JInternalError();
                }
            }
        }

        jint HandleTable::getSize(){
            return size;
        }

        JObject* HandleTable::lookupObject(jint handle) {
            return (handle != NULL_HANDLE && status[handle] != STATUS_EXCEPTION) ? entries[handle] : NULL;
        }

        JClassNotFoundException* HandleTable::lookupException(jint handle) {
            return (handle != NULL_HANDLE && status[handle] == STATUS_EXCEPTION) ? (JClassNotFoundException*) entries[handle] : NULL;
        }


        void HandleTable::clear() {
            for (jint i = 0; i < size; ++i) {
                status[i] = (jbyte) 0;
                delete entries[i];
                entries[i] = NULL;
                delete deps[i];
                deps[i] = NULL;
            }
            lowDep = -1;
            size = 0;
        }
    }
}
