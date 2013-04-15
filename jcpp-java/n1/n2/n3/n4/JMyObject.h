#ifndef JMYOBJECT_H
#define JMYOBJECT_H

//include declaration
#include "JI2.h"
#include "JI1.h"
#include "JList.h"
#include "JToto.h"
#include "JArrayList.h"
#include "JMyParent.h"
#include "JR1.h"
#include "JCollection.h"

//use namespace declaration
using namespace i1::i2::i3;
using namespace java::util;
using namespace p1::p2::p3;
using namespace n1::n2::n3;
using namespace n1::n2::n3::n4::n5;

//namespace declaration
namespace n1{
    namespace n2{
        namespace n3{
            namespace n4{

//class declaration
class JMyObject : public JMyParent  , public JI1  , public JI2  {
	protected:
		JR1* f1;
		JCollection* f2;
		friend class JMyObjectClass;
	
	public:
		static JClass* getClazz();
		JMyObject();

		//field f1
		JR1* getF1();
		void setF1(JR1* f1);

		//field f2
		JCollection* getF2();
		void setF2(JCollection* f2);




		virtual ~JMyObject();

};
            }
        }
    }
}

#endif // JMYOBJECT_H

//                