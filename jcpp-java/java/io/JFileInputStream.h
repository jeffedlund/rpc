#ifndef JFILEINPUTSTREAM_H
#define JFILEINPUTSTREAM_H

//include declaration
#include "JClass.h"
#include "JString.h"
#include "JFileChannel.h"
#include "JFileDescriptor.h"
#include "JObject.h"
#include "JInputStream.h"

//use namespace declaration
using namespace java::io;
using namespace java::nio::channels;
using namespace java::lang;

//namespace declaration
namespace java{
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
		virtual int * read();
		//method read
		virtual int * read([B* , int* , int*  );
		//method read
		virtual int * read([B*  );
		//method skip
		virtual long * skip(long*  );
		//method available
		virtual int * available();
		//method getFD
		virtual JFileDescriptor * getFD();
		//method getChannel
		virtual JFileChannel * getChannel();
		//method mark
		virtual void  mark(int*  );
		//method reset
		virtual void  reset();
		//method markSupported
		virtual boolean * markSupported();
		//method wait
		virtual void  wait(long* , int*  );
		//method wait
		virtual void  wait(long*  );
		//method wait
		virtual void  wait();
		//method equals
		virtual boolean * equals(JObject*  );
		//method toString
		virtual JString * toString();
		//method hashCode
		virtual int * hashCode();
		//method getClass
		virtual JClass * getClass();
		//method notify
		virtual void  notify();
		//method notifyAll
		virtual void  notifyAll();

		virtual ~JFileInputStream();

};
    }
}

#endif // JFILEINPUTSTREAM_H

//        