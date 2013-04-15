//include declaration
#include "JFlushable.h"

//namespace declaration
namespace jcpp{
    namespace io{

    class JFlushableClass : public JClass{
        protected:


        public:
            JFlushableClass(){
                this->canonicalName="java.io.Flushable";
                this->name="java.io.Flushable";
                this->simpleName="Flushable";
                this->serialVersionUID=0ULL;

                //interfaces

                //fields
            }

            JClass* getSuperclass(){
                return JInterface::getClazz();
            }

            JObject* newInstance(){
                return new JFlushable();
            }
        };

        static JClass* clazz;

        JClass* JFlushable::getClazz(){
            if (clazz==NULL){
                clazz=new JFlushableClass();
            }
            return clazz;
        }

        JFlushable(){
            //TODO
        }


        //method flush
        void  JFlushable::flush(){
            return NULL;//TODO
        }

        JFlushable::~JFlushable(){
        }

    }
}

//        