#ifndef JFILEINPUTSTREAM_H
#define JFILEINPUTSTREAM_H

//include declaration
#include "JFileChannel.h"
#include "JInputStream.h"
#include "JFileDescriptor.h"

//use namespace declaration
using namespace jcpp::io;
using namespace jcpp::nio::channels;

//namespace declaration
namespace jcpp{
    namespace io{

//class declaration
class JFileInputStream : public JInputStream  {
	protected:
		friend class JFileInputStreamClass;
	
	public:
		static JClass* getClazz();
		JFileInputStream();



		//method close
		virtual void  close();
		//method read
		virtual JPrimitiveInt * read();
		//method read
		virtual JPrimitiveInt * read(J[B* p0, JPrimitiveInt* p1, JPrimitiveInt* p2 );
		//method read
		virtual JPrimitiveInt * read(J[B* p0 );
		//method skip
		virtual JPrimitiveLong * skip(JPrimitiveLong* p0 );
		//method available
		virtual JPrimitiveInt * available();
		//method getFD
		virtual JFileDescriptor * getFD();
		//method getChannel
		virtual JFileChannel * getChannel();

		virtual ~JFileInputStream();

};
    }
}

#endif // JFILEINPUTSTREAM_H

//        