#include "JTransportTest.h"
#include "JITransportDispatcher.h"

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace transport{
                    JTransportTest::JTransportTest():JTest(){
                    }

                    class MyTransportRouter : public JITransportRouter{
                    public:
                        JRoute* findRoute(JString*, JEndPoint*){
                            return NULL;
                        }
                        ~MyTransportRouter(){
                        }
                    };

                    class MyTransportDispatcher : public JITransportDispatcher{
                    public:
                        void dispatch(JEndPoint* fromEndPoint, JEndPoint* toEndpoint,JConnection*){
                            cout<<fromEndPoint->toString()<<"\r\n";
                            cout<<toEndpoint->toString()<<"\r\n";
                        }
                        ~MyTransportDispatcher(){
                        }
                    };

                    void JTransportTest::test(){
                        JEndPoint* localEndPoint=new JEndPoint();
                        localEndPoint->getAddress()->setHostName("localhost");
                        localEndPoint->getAddress()->setPort(9999);
                        localEndPoint->setSite(new JString("site1"));

                        JTransportConfiguration* transportConfiguration=new JTransportConfiguration();
                        JTransport* transport=new JTransport(localEndPoint,new MyTransportRouter(),new MyTransportDispatcher(),new JThreadPoolExecutor(),new JScheduledThreadPoolExecutor(),transportConfiguration);
                        transport->startExport();
                        JThread::sleep(100000);
                    }

                    JTransportTest::~JTransportTest(){
                    }
                }
            }
        }
    }
}




