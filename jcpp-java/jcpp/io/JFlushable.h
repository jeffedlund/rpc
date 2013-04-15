#ifndef JFLUSHABLE_H
#define JFLUSHABLE_H

//include declaration
#include "JInterface.h"

//use namespace declaration
using namespace jcpp::lang;

//namespace declaration
namespace jcpp{
    namespace io{

//class declaration
class JFlushable : public JInterface  {
	protected:
		friend class JFlushableClass;
	
	public:
		static JClass* getClazz();
		JFlushable();



		//method flush
		virtual void  flush();

		virtual ~JFlushable();

};
    }
}

#endif // JFLUSHABLE_H

//        