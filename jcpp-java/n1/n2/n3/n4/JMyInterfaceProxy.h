#ifndef JMYINTERFACE_HPROXY
#define JMYINTERFACE_HPROXY

//include declaration
#include "JProxy.h"

//use namespace declaration
using namespace jcpp::lang::reflect;

//namespace declaration
namespace n1{
    namespace n2{
        namespace n3{
            namespace n4{

//class declaration
class JMyInterfaceProxy : public JProxy  , public JMyInterface  {
	protected:
		class JMyInterfaceProxyClass : public JProxyClass{
		public:
			JMyInterfaceProxyClass();
			virtual JClass* getSuperclass();
			virtual JObject* newInstance();
		};

	public:
		JMyInterfaceProxy();
		static JClass* getClazz();

		//methods declaration
		virtual void  m1(JP1* , JP2*  );
		virtual JR1 * m2(JP1* , JP2*  );

		virtual ~JMyInterfaceProxy();

};
            }
        }
    }
}

#endif // JMYINTERFACE_HPROXY
