#ifndef JMYINTERFACE_H
#define JMYINTERFACE_H

//include declaration
#include R1
#include I1
#include P2
#include I2
#include MyParent
#include P1
#include "JObject.h"

//use namespace declaration
using namespace i1.i2.i;
using namespace p1.p2.p;
using namespace f1.f2.f;

//namespace declaration
namespace n1{
namespace n2{
namespace n3{
namespace n{

//class declaration
class JMyInterface : public MyParent  , public I1  , public I2  {
	
	public:
		static JClass* getClazz();

		//methods declaration


		virtual ~JMyInterface();

};

}
}
}
}

#endif // JMYINTERFACE_H
