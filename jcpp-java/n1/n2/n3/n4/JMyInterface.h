#ifndef JMYINTERFACE_H
#define JMYINTERFACE_H

//include declaration
#include "JCollection.h"
#include "JR1.h"
#include "JList.h"
#include "JToto.h"
#include "JP1.h"
#include "JI2.h"
#include "JP2.h"
#include "JArrayList.h"
#include "JI1.h"
#include "JMyParent.h"

//use namespace declaration
using namespace n1::n2::n3::n4::n5;
using namespace f1::f2::f3;
using namespace p1::p2::p3;
using namespace i1::i2::i3;
using namespace java::util;

//namespace declaration
namespace n1{
    namespace n2{
        namespace n3{
            namespace n4{

//class declaration
class JMyInterface : public JMyParent  , public JI1  , public JI2  {
	
	public:
		static JClass* getClazz();

		//methods declaration
		virtual void  m1(JP1* , JP2*  )=0;
		virtual JR1 * m2(JP1* , JP2*  )=0;

		virtual ~JMyInterface();

};
            }
        }
    }
}

#endif // JMYINTERFACE_H

//                