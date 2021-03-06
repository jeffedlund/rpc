#ifndef OUTPUTHANDLETABLE_H
#define OUTPUTHANDLETABLE_H

#include "JObject.h"
#include <map>
#include "Object.h"
using namespace std;
using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class OutputHandleTable{
        private:
            jint handle;
            map<JObject*, jint>*  handleByObject;

        public:
            OutputHandleTable();
            jint assign(JObject *obj);
            jint size();
            void clear();
            jint lookup(JObject* obj);
            ~OutputHandleTable();
        };
    }
}

#endif // OUTPUTHANDLETABLE_H
