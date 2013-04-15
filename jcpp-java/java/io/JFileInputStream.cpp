//include declaration
#include "JFileInputStream.h"

//namespace declaration
namespace java{
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
        int * JFileInputStream::read(){
            return NULL;//TODO
        }
        //method read
        int * JFileInputStream::read([B* , int* , int*  ){
            return NULL;//TODO
        }
        //method read
        int * JFileInputStream::read([B*  ){
            return NULL;//TODO
        }
        //method skip
        long * JFileInputStream::skip(long*  ){
            return NULL;//TODO
        }
        //method available
        int * JFileInputStream::available(){
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
        //method mark
        void  JFileInputStream::mark(int*  ){
            return NULL;//TODO
        }
        //method reset
        void  JFileInputStream::reset(){
            return NULL;//TODO
        }
        //method markSupported
        boolean * JFileInputStream::markSupported(){
            return NULL;//TODO
        }
        //method wait
        void  JFileInputStream::wait(long* , int*  ){
            return NULL;//TODO
        }
        //method wait
        void  JFileInputStream::wait(long*  ){
            return NULL;//TODO
        }
        //method wait
        void  JFileInputStream::wait(){
            return NULL;//TODO
        }
        //method equals
        boolean * JFileInputStream::equals(JObject*  ){
            return NULL;//TODO
        }
        //method toString
        JString * JFileInputStream::toString(){
            return NULL;//TODO
        }
        //method hashCode
        int * JFileInputStream::hashCode(){
            return NULL;//TODO
        }
        //method getClass
        JClass * JFileInputStream::getClass(){
            return NULL;//TODO
        }
        //method notify
        void  JFileInputStream::notify(){
            return NULL;//TODO
        }
        //method notifyAll
        void  JFileInputStream::notifyAll(){
            return NULL;//TODO
        }

        JFileInputStream::~JFileInputStream(){
        }

    }
}

//        