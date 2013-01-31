#ifndef HANDLETABLE_H
#define HANDLETABLE_H

#include "JObject.h"
#include "HandleList.h"


//HandleTable
class HandleTable {

    /* status codes indicating whether object has associated exception */
    static const qint8 STATUS_OK = 1;
    static const qint8 STATUS_UNKNOWN = 2;
    static const qint8 STATUS_EXCEPTION = 3;

    /** array mapping handle -> object status */
    qint8* status;
    /** array mapping handle -> object/exception (depending on status) */
    JObject** entries;
    /** array mapping handle -> list of dependent handles (if any) */
    HandleList** deps;
    /** lowest unresolved dependency */
    int lowDep;
    /** number of handles in table */
    int size;

    int length;

    /**
     * Associates a ClassNotFoundException (if one not already associated)
     * with the currently active handle and propagates it to other
     * referencing objects as appropriate.  The specified handle must be
     * "open" (i.e., assigned, but not finished yet).
     */
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

    /**
     * Expands capacity of internal arrays.
     */
    void grow();

public:

    HandleTable(int initialCapacity);

    ~HandleTable();

    /**
     * Assigns next available handle to given object, and returns assigned
     * handle. Once object has been completely deserialized (and all
     * dependencies on other objects identified), the handle should be
     * "closed" by passing it to finish().
     */
    int assign(JObject *obj);

    /**
     * Assigns a new object to the given handle.  The object previously
     * associated with the handle is forgotten.  This method has no effect
     * if the given handle already has an exception associated with it.
     * This method may be called at any time after the handle is assigned.
     */
    void setObject(int handle, JObject* obj);

    /**
     * Marks given handle as finished, meaning that no new dependencies
     * will be marked for handle. Calls to the assign and finish methods
     * must occur in LIFO order.
     */
    void finish(int handle);

    /**
     * Returns number of handles registered in table.
     */
    int getSize();

    /**
     * Looks up and returns object associated with the given handle.
     * Returns null if the given handle is NULL_HANDLE, or if it has an
     * associated ClassNotFoundException.
     */
    JObject* lookupObject(int handle);

    /**
     * Resets table to its initial state.
     */
    void clear();
 };

#endif // HANDLETABLE_H
