#ifndef JMYCLASS
#define JMYCLASS

//include declaration
#include "inc1.h"
#include "inc2.h"
#include "inc3.h"
#include "JObject.h"

//use namespace declaration
using namespace use_n1;
using namespace use_n2;
using namespace use_n3;


//namespace declaration
namespace n1{
namespace n2{
namespace n3{

//class declaration
class JMyClass : public JParentClass  , public JI1  , public JI2  , public JI3  {
	protected:
		//field declaration
		t1* f1;
		t2* f2;
		t3* f3;

		//constructor
		JMyClass(JClass* clazz);
	
	public:
		//default constructor
		JMyClass();
		static JClass* getClazz();

		//field declaration

		//field f1
		virtual t1* getF1();
		virtual void setF1(t1* f1);

		//field f2
		virtual t2* getF2();
		virtual void setF2(t2* f2);

		//field f3
		virtual t3* getF3();
		virtual void setF3(t3* f3);


		virtual ~JMyClass();

};

}
}
}

#endif // JMYCLASS
