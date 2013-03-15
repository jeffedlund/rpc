#include "JServerTest.h"
#include "JTransportRouter.h"
#include "JProxy.h"
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    JServerTest::JServerTest():JTest(){
                    }

                    void JServerTest::test(){
                        JEndPoint* localEndPoint1=new JEndPoint();
                        localEndPoint1->getAddress()->setHostName("localhost");
                        localEndPoint1->getAddress()->setPort(9999);
                        localEndPoint1->setSite(new JString("site1"));
                        JTransportRouter* router1=new JTransportRouter();
                        JConnectionConfiguration* cc1=new JConnectionConfiguration();
                        JServer* server1=new JServer(localEndPoint1,router1,cc1);

                        JEndPoint* localEndPoint2=new JEndPoint();
                        localEndPoint2->getAddress()->setHostName("localhost");
                        localEndPoint2->getAddress()->setPort(9998);
                        localEndPoint2->setSite(new JString("site1"));
                        JTransportRouter* router2=new JTransportRouter();
                        JConnectionConfiguration* cc2=new JConnectionConfiguration();
                        JServer* server2=new JServer(localEndPoint2,router2,cc2);

                        JObject* obj=server2->lookup(localEndPoint1,JIRegistry::getClazz());
                        cout<<obj->getClass()->getName();
                        cout.flush();
                        JProxy* proxy=(JProxy*)obj;
                        JObject* result=proxy->invoke("list",NULL);
                        cout<<result->getClass()->getName();
                        cout.flush();
                        JPrimitiveArray* ar=(JPrimitiveArray*)result;
                        for (int i=0;i<ar->size();i++){
                            cout<<i<<"="<<ar->get(i)->toString()<<"\r\n";
                            cout<<i<<"="<<ar->get(i)->getClass()->getName()<<"\r\n";
                            cout.flush();
                        }


                        JIRegistry* regProxy=dynamic_cast<JIRegistry*>(obj);
                        result=regProxy->list();
                        cout<<"using a cast to a Proxy interface"<<"\r\n";
                        cout<<result->getClass()->getName()<<"\r\n";
                        cout.flush();
                        ar=(JPrimitiveArray*)result;
                        for (int i=0;i<ar->size();i++){
                            cout<<i<<"="<<ar->get(i)->toString()<<"\r\n";
                            cout<<i<<"="<<ar->get(i)->getClass()->getName()<<"\r\n";
                            cout.flush();
                        }
                        JThread::sleep(10000);
                    }

                    JServerTest::~JServerTest(){
                    }
                }
            }
        }
    }
}





