#include "JSocketTest.h"

namespace jcpp{
    namespace net{
        JSocketTest::JSocketTest():JTest(){
        }

        class ServerSocketRunnable : public JRunnable{
        public:
            JServerSocket* server;
            ServerSocketRunnable(string host, int port){
                this->server=new JServerSocket(new JString(host), new JPrimitiveInt(port),new JPrimitiveInt(200));
                server->connect();
            }

            void run(){
                JSocket* socket=server->accept();
                JObjectOutputStream* oos=new JObjectOutputStream(socket->getOutputStream());
                JObjectInputStream* ois=new JObjectInputStream(socket->getInputStream());
                while (true){
                    cout<<"before reading \r\n";
                    cout.flush();
                    JObject* obj=ois->readObject();
                    cout<<obj->toString();
                    cout.flush();
                    cout<<"after reading \r\n";
                    cout.flush();

                    cout<<"before writing \r\n";
                    cout.flush();
                    oos->writeObject(obj);
                    cout<<"after writing \r\n";
                    cout.flush();
                    //JThread::sleep(1000);
                }
            }

            ~ServerSocketRunnable(){
            }
        };

        class ClientSocketRunnable : public JRunnable{
        public:
            JSocket* socket;
            ClientSocketRunnable(string host,int port){
                JThread::sleep(5);
                this->socket=new JSocket(new JString(host),new JPrimitiveInt(port),0);
            }

            void run(){
                JObjectOutputStream* oos=new JObjectOutputStream(socket->getOutputStream());
                JObjectInputStream* ois=new JObjectInputStream(socket->getInputStream());
                while (true){
                    cout<<"before writing \r\n";
                    cout.flush();
                    oos->writeObject(new JString("hello "));
                    oos->flush();
                    cout<<"after writing \r\n";
                    cout.flush();

                    cout<<"before reading \r\n";
                    cout.flush();
                    JObject* obj=ois->readObject();
                    cout<<obj->toString();
                    cout.flush();
                    cout<<"after reading \r\n";
                    cout.flush();
                    JThread::sleep(1);
                }
            }

            ~ClientSocketRunnable(){
            }
        };

        void JSocketTest::test(){
            ServerSocketRunnable* ssr=new ServerSocketRunnable("localhost",12345);
            JThread* th=new JThread(ssr);
            th->move(ssr->server);
            th->start();
            ClientSocketRunnable* csr=new ClientSocketRunnable("localhost",12345);
            JThread* th2=new JThread(csr);
            th2->move(csr->socket);
            th2->start();
            JThread::sleep(100000);
        }

        JSocketTest::~JSocketTest(){
        }
    }
}



