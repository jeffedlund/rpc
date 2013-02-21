#ifndef JCONNECTIONHEADERREADER_H
#define JCONNECTIONHEADERREADER_H

#include "JObject.h"
#include "JClass.h"
#include <vector>
#include <iostream>
#include <map>
#include "JSocket.h"
#include "Object.h"
#include "JDataOutputStream.h"
#include "JDataInputStream.h"
#include "JTransport.h"
using namespace std;
using namespace jcpp::lang;
using namespace jcpp::rmi::server::impl::gateway;
using namespace jcpp::net;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace transport{
                    class JConnectionHeaderReader : public JObject, public JRunnable{
                        protected:
                            JSocket* socket;
                            JTransport* transport;

                        public:
                            JConnectionHeaderReader(JSocket* socket, JTransport* transport);
                            static JClass* getClazz();

                            void unexport();
                            virtual void run();
                            ~JConnectionHeaderReader();
                    };
                }
            }
        }
    }
}


#endif // JCONNECTIONHEADERREADER_H
