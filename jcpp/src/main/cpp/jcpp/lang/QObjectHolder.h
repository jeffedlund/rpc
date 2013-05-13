#ifndef QOBJECTHOLDER_H
#define QOBJECTHOLDER_H

#include "JThread.h"
#include "JCPP.h"

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT QObjectHolder : public JThread{
        protected:
            class Present{
            public:
                bool p;
                QThread* thread;

                Present(){
                    p=true;
                    thread=NULL;
                }
            };

            map<QObject*,Present*>* objects;
            QObjectHolder();

        public:
            static QObjectHolder* getQObjectHolder();
            void releaseOwner(QObject* obj);
            void takeOwner(QObject* obj);
            void deleteObject(QObject* obj);
            virtual void run();
        };
    }
}


#endif // QOBJECTHOLDER_H
