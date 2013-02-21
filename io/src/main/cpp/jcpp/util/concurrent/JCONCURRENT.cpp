#include "JCONCURRENT.h"
#include "JCPP.h"

namespace jcpp{
    namespace util{
        namespace concurrent{
            JCONCURRENT::JCONCURRENT():JPackage("jcpp.util.concurrent",JPackage::getClazz()){
                classes->push_back(JAbstractExecutorService::getClazz());
                classes->push_back(JCallable::getClazz());
                classes->push_back(JDelayed::getClazz());
                classes->push_back(JExecutor::getClazz());
                classes->push_back(JExecutorService::getClazz());
                classes->push_back(JFuture::getClazz());
                classes->push_back(JFutureTask::getClazz());
                classes->push_back(JRunnableFuture::getClazz());
                classes->push_back(JRunnableScheduledFuture::getClazz());
                classes->push_back(JScheduledExecutorService::getClazz());
                classes->push_back(JScheduledFuture::getClazz());
                classes->push_back(JScheduledFutureTask::getClazz());
                classes->push_back(JScheduledThreadPoolExecutor::getClazz());
                classes->push_back(JThreadPoolExecutor::getClazz());
            }

            JPackage* JCONCURRENT::getSuperPackage(){
                return JUTIL::getPackage();
            }

            vector<JPackage*>* JCONCURRENT::getPackages(){
                if (packages->size()==0){
                }
                return packages;
            }

            static JCONCURRENT* jconcurrent=NULL;

            JCONCURRENT* JCONCURRENT::getPackage(){
                if (jconcurrent==NULL){
                    jconcurrent=new JCONCURRENT();
                }
                return jconcurrent;
            }
        }
    }
}
