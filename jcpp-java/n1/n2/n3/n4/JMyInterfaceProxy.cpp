//include declaration
#include "JMyInterfaceProxy.h"

//namespace declaration
namespace n1{
    namespace n2{
        namespace n3{
            namespace n4{

        JMyInterfaceProxy::JMyInterfaceProxyClass::JMyInterfaceProxyClass():JProxyClass(){
            this->canonicalName="n1.n2.n3.n4.MyInterfaceProxy";
            this->name="n1.n2.n3.n4.MyInterfaceProxy";
            this->simpleName="MyInterfaceProxy";
            this->bIsProxy=true;
            addInterface(JMyInterface::getClazz());
        }

        JClass* JMyInterfaceProxy::JMyInterfaceProxyClass::getSuperclass(){
            return JProxy::getClazz();
        }

        JObject* JMyInterfaceProxy::JMyInterfaceProxyClass::newInstance(){
            return new JMyInterfaceProxy();
        }

        static JClass* clazz;

        JClass* JMyInterfaceProxy::getClazz(){
            if (clazz==NULL){
                clazz=new JMyInterfaceProxyClass();
            }
            return clazz;
        }

        JMyInterfaceProxy::JMyInterfaceProxy():JProxy(getClazz()){
        }

            void JMyInterfaceProxy::m1(JP1* p0, JP2* p1 ){
                vector<JObject*> args;
                args.push_back(p0);
args.push_back(p1);
                invoke("m1",&args);
                return NULL;
            }
            JR1 JMyInterfaceProxy::m2(JP1* p0, JP2* p1 ){
                vector<JObject*> args;
                args.push_back(p0);
args.push_back(p1);
                JR1* r=invoke("m2",&args);
                return r;
            }

        JMyInterfaceProxy::~JMyInterfaceProxy(){
        }

            }
        }
    }
}

//                