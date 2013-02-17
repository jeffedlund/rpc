#include "JInet4Address.h"
#include <QHostInfo>

namespace jcpp{
    namespace net{
        class JInet4AddressClass : public JClass{
        public:
          JInet4AddressClass(){
              this->canonicalName="java.net.Inet4Address";
              this->name="java.lang.4InetAddress";
              this->simpleName="Inet4Address";
              this->serialVersionUID=3286316764910316507ULL;
          }

          JClass* getSuperclass(){
              return JInetAddress::getClazz();
          }

          JObject* newInstance(){
              return new JInet4Address();
          }
        };

        static JClass* clazz;

        JClass* JInet4Address::getClazz(){
            if (clazz==NULL){
                clazz=new JInet4AddressClass();
            }
            return clazz;
        }

        JInet4Address::JInet4Address():JInetAddress(getClazz()){
        }
    }
}
