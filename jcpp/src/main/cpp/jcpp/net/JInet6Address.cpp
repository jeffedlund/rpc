#include "JInet6Address.h"
#include <QHostInfo>

namespace jcpp{
    namespace net{
        class JInet6AddressClass : public JClass{
        public:
          JInet6AddressClass(){
              this->canonicalName="java.net.Inet6Address";
              this->name="java.lang.6InetAddress";
              this->simpleName="Inet6Address";
              this->serialVersionUID=6880410070516793377ULL;
          }

          JClass* getSuperclass(){
              return JInetAddress::getClazz();
          }

          JObject* newInstance(){
              return new JInet6Address();
          }
        };

        static JClass* clazz;

        JClass* JInet6Address::getClazz(){
            if (clazz==NULL){
                clazz=new JInet6AddressClass();
            }
            return clazz;
        }

        JInet6Address::JInet6Address():JInetAddress(getClazz()){
        }

        JInet6Address::~JInet6Address(){
        }
    }
}
