#ifndef JTHREADLOCAL_H
#define JTHREADLOCAL_H

#include "JObject.h"
#include "JRunnable.h"
#include <QThread>
#include "QObjectAware.h"
#include "JCPP.h"
#include <QThreadStorage>
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JThreadLocal : public JObject{
        protected:
            QThreadStorage<JObject*>* threadStorage;
            JThreadLocal(JClass* _class);
            JObject* initialValue();

        public:
            JThreadLocal();
            static JClass* getClazz();
            JObject* get();
            virtual void remove();
            virtual void set(JObject* value);
            virtual ~JThreadLocal();
        };
    }
}
#endif // JTHREADLOCAL_H
