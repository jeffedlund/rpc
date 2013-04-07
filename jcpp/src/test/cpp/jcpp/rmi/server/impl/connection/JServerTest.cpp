#include "JServerTest.h"
#include "JTransportRouter.h"
#include "JProxy.h"
#include "JIRemoteSample.h"
#include "JRemoteSample.h"
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
                        localEndPoint1->getAddress()->setPort(9876);
                        localEndPoint1->setSite(new JString("site1"));
                        JTransportRouter* router1=new JTransportRouter();
                        JConnectionConfiguration* cc1=new JConnectionConfiguration();
                        /*JServer* server1=new JServer(localEndPoint1,router1,cc1);
                        JRemoteSample* rs=new JRemoteSample();
                        JPrimitiveArray* i=new JPrimitiveArray(JClass::getClazz(),1);
                        i->set(0,JIRemoteSample::getClazz());
                        server1->getIRegistry()->bind(JString::intern(JIRemoteSample::getClazz()->getName()),rs,i);
                        */

                        JEndPoint* localEndPoint2=new JEndPoint();
                        localEndPoint2->getAddress()->setHostName("localhost");
                        localEndPoint2->getAddress()->setPort(9998);
                        localEndPoint2->setSite(new JString("site1"));
                        JTransportRouter* router2=new JTransportRouter();
                        JConnectionConfiguration* cc2=new JConnectionConfiguration();
                        JServer* server2=new JServer(localEndPoint2,router2,cc2);
                        JRemoteSample* rs2=new JRemoteSample();
                        JPrimitiveArray* i2=new JPrimitiveArray(JClass::getClazz(),1);
                        i2->set(0,JIRemoteSample::getClazz());
                        server2->getIRegistry()->bind(JString::intern(JIRemoteSample::getClazz()->getName()),rs2,i2);

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
                        for (int i=0;i<100;i++){
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
                        }

                        JObject* remoteObject=server2->lookup(localEndPoint1,JIRemoteSample::getClazz());
                        cout<<remoteObject->getClass()->getName();
                        cout<<"\r\n";
                        cout<<remoteObject->toString();
                        cout<<"\r\n";
                        cout.flush();
                        JIRemoteSample* remoteSample=dynamic_cast<JIRemoteSample*>(remoteObject);
                        JSampleObject* so=remoteSample->getSampleObject();
                        cout<<so->toString();
                        cout<<"\r\n";
                        cout.flush();
                        cout<<remoteSample->getRemoteSample();
                        cout<<"\r\n";
                        cout.flush();
                        JIRemoteSample* rsample=remoteSample->getRemoteSample();
                        JObject* remoteSampleObject=(JObject*)(rsample);
                        cout<<remoteSampleObject->toString();
                        cout<<"\r\n";
                        cout.flush();
                        cout<<so->getRemoteSample()->getRemoteSample();
                        cout<<"\r\n";
                        cout.flush();
                        so->getRemoteSample()->checkRemoteSample(so->getRemoteSample());
                        cout<<"check with pointer as param worked.";
                        cout.flush();
                        JIRemoteSample* irs2=so->getRemoteSample();
                        JIRemoteSample* localrs2=(JIRemoteSample*)(rs2);
                        JObject* oo2=(JObject*)(irs2);
                        cout<<oo2->getClass()->toString();
                        cout<<"\r\n";
                        cout.flush();
                        oo2=(JObject*)(rs2);
                        cout<<oo2->getClass()->toString();
                        cout<<"\r\n";
                        cout.flush();
                        cout<<remoteSample->getSampleObject();;
                        cout<<"\r\n";
                        cout.flush();
                        remoteSample->checkCallback(rs2);
                        JThread::sleep(10000);
                    }

                    JServerTest::~JServerTest(){
                    }
                }
            }
        }
    }
}





