#include "HandleTable.h"
#include "JObject.h"
#include "memory.h"
#include "JObjectInputStream.h"

//HandleTable implementation
//        void markException(int handle, MJavaException* ex) {
//            switch (status[handle]) {
//            case STATUS_UNKNOWN:
//            {
//                status[handle] = STATUS_EXCEPTION;
//                entries[handle] = ex;

//                // propagate exception to dependents
//                HandleList *dlist = deps[handle];
//                if (dlist != NULL) {
//                    int ndeps = dlist->getSize();
//                    for (int i = 0; i < ndeps; ++i) {
//                        markException(dlist->get(i), ex);
//                    }
//                    delete deps[handle];
//                    deps[handle] = NULL;
//                }
//            }
//                break;

//            case STATUS_EXCEPTION:
//                break;

//            default:
//                throw "new InternalError()";
//            }
//        }

    /**
     * Looks up and returns ClassNotFoundException associated with the
     * given handle.  Returns null if the given handle is NULL_HANDLE, or
     * if there is no ClassNotFoundException associated with the handle.
     */
//        MJavaException* lookupException(int handle) {
//            return (handle != NULL_HANDLE &&
//                    status[handle] == STATUS_EXCEPTION) ?
//                        (MJavaException*) entries[handle] : NULL;
//        }

void HandleTable::grow() {
    int newCapacity = (length*2) +1;

    qint8 *newStatus = new qint8[newCapacity];
    JObject **newEntries = new JObject*[newCapacity];
    HandleList **newDeps = new HandleList*[newCapacity];

    memcpy(newStatus, status, size * sizeof(qint8));
    delete[] status;
    memcpy(newEntries, entries, size * sizeof(JObject*));
    delete[] entries;
    memcpy(newDeps, deps, size * sizeof(HandleList*));
    delete[] deps;

    status = newStatus;
    entries = newEntries;
    deps = newDeps;
    for (int i = length; i < newCapacity; ++i) {
        status[i] = (qint8) 0;
        entries[i] = NULL;
        deps[i] = NULL;
    }
    length = newCapacity;
}

HandleTable::HandleTable(int initialCapacity) {
    length = initialCapacity;
    lowDep = -1;
    size = 0;
    status = new qint8[initialCapacity];
    entries = new JObject*[initialCapacity];
    deps = new HandleList*[initialCapacity];

    // initialize
    for (int i = 0; i < initialCapacity; ++i) {
        status[i] = (qint8) 0;
        entries[i] = NULL;
        deps[i] = NULL;
    }
}

HandleTable::~HandleTable() {
    delete[] status;
    for (int i = 0; i < size; ++i) {
        delete deps[i];
    }
    delete[] entries;
    delete[] deps;
}

//        void markDependency(int dependent, int target) {
//            if (dependent == NULL_HANDLE || target == NULL_HANDLE) {
//                return;
//            }
//            switch (status[dependent]) {

//            case STATUS_UNKNOWN:
//                switch (status[target]) {
//                case STATUS_OK:
//                    // ignore dependencies on objs with no exception
//                    break;

//                case STATUS_EXCEPTION:
//                    // eagerly propagate exception
//                    markException(dependent,(MJavaException*) entries[target]);
//                    break;

//                case STATUS_UNKNOWN:
//                    // add dependency list of target
//                    if (deps[target] == NULL) {
//                        deps[target] = new HandleList;
//                    }
//                    deps[target]->add(dependent);

//                    // remember lowest unresolved target seen
//                    if (lowDep < 0 || lowDep > target) {
//                        lowDep = target;
//                    }
//                    break;

//                default:
//                    throw "new InternalError()";
//                }
//                break;

//            case STATUS_EXCEPTION:
//                break;

//            default:
//                throw "new InternalError()";
//            }
//        }

int HandleTable::assign(JObject *obj) {
    if (size >= length) {
        grow();
    }
    status [size] = STATUS_UNKNOWN;
    entries[size] = obj;
    return size++;
}

void HandleTable::setObject(int handle, JObject* obj) {
    switch (status[handle]) {
    case STATUS_UNKNOWN:
    case STATUS_OK:
        entries[handle] = obj;
        break;

    case STATUS_EXCEPTION:
        break;

    default:
        throw "new InternalError()";//TODO
    }
}

void HandleTable::finish(int handle) {
    int end = 0;
    if (lowDep < 0) {
        // no pending unknowns, only resolve current handle
        end = handle + 1;
    } else if (lowDep >= handle) {
        // pending unknowns now clearable, resolve all upward handles
        end = size;
        lowDep = -1;
    } else {
        // unresolved backrefs present, can't resolve anything yet
        return;
    }

    // change STATUS_UNKNOWN -> STATUS_OK in selected span of handles
    for (int i = handle; i < end; i++) {
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
            throw "new InternalError()";//TODO
        }
    }
}

int HandleTable::getSize(){
    return size;
}

JObject* HandleTable::lookupObject(int handle) {
    return (handle != NULL_HANDLE && status[handle] != STATUS_EXCEPTION) ? entries[handle] : NULL;
}

void HandleTable::clear() {
    for (int i = 0; i < size; ++i) {
        status[i] = (qint8) 0;
        delete entries[i];
        entries[i] = NULL;
        delete deps[i];
        deps[i] = NULL;
    }
    lowDep = -1;
    size = 0;
}

