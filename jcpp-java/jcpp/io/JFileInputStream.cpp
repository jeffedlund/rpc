//include declaration
#include "JFileInputStream.h"

//namespace declaration
namespace jcpp{
    namespace io{

    class JFileInputStreamClass : public JClass{
        protected:


        public:
            JFileInputStreamClass(){
                this->canonicalName="java.io.FileInputStream";
                this->name="java.io.FileInputStream";
                this->simpleName="FileInputStream";
                this->serialVersionUID=0ULL;

                //interfaces

                //fields
            }

            JClass* getSuperclass(){
                return JInputStream::getClazz();
            }

            JObject* newInstance(){
                return new JFileInputStream();
            }
        };

        static JClass* clazz;

        JClass* JFileInputStream::getClazz(){
            if (clazz==NULL){
                clazz=new JFileInputStreamClass();
            }
            return clazz;
        }

        JFileInputStream(){
            //TODO
        }


        //method close
        void  JFileInputStream::close(){
            return NULL;//TODO
        }
        //method read
        JPrimitiveInt * JFileInputStream::read(){
            return NULL;//TODO
        }
        //method read
        JPrimitiveInt * JFileInputStream::read(J[B* p0, JPrimitiveInt* p1, JPrimitiveInt* p2 ){
            return NULL;//TODO
        }
        //method read
        JPrimitiveInt * JFileInputStream::read(J[B* p0 ){
            return NULL;//TODO
        }
        //method skip
        JPrimitiveLong * JFileInputStream::skip(JPrimitiveLong* p0 ){
            return NULL;//TODO
        }
        //method available
        JPrimitiveInt * JFileInputStream::available(){
            return NULL;//TODO
        }
        //method getFD
        JFileDescriptor * JFileInputStream::getFD(){
            return NULL;//TODO
        }
        //method getChannel
        JFileChannel * JFileInputStream::getChannel(){
            return NULL;//TODO
        }

        JFileInputStream::~JFileInputStream(){
        }

    }
}

//        