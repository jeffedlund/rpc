#include "OutputHandleTable.h"

namespace jcpp{
    namespace io{
        OutputHandleTable::OutputHandleTable(){
            this->handleByObject=new map<JObject*, qint32>();
            handle = 0;
            clear();
        }

        qint32 OutputHandleTable::assign(JObject *obj){
            handleByObject->insert(pair<JObject*,qint32>(obj,handle));
            return handle++;
        }

        void OutputHandleTable::clear(){
            handleByObject->clear();
        }

        int OutputHandleTable::size(){
            return handleByObject->size();
        }

        qint32 OutputHandleTable::lookup(JObject* obj){
            if (handleByObject->count(obj)==1){
                return handleByObject->at(obj);
            }else{
                return -1;
            }
        }

        OutputHandleTable::~OutputHandleTable(){
            delete handleByObject;
        }
    }
}
