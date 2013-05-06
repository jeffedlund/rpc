#include "HandleList.h"
#include "memory.h"
#include "JIndexOutOfBoundsException.h"
#include <sstream>

namespace jcpp{
    namespace io{
        HandleList::HandleList() {
            length = 4;
            list = new jint[length];
            for (jint i = 0; i < length ; ++i) {
                list[i] = 0;
            }
            size = 0;
        }

        HandleList::HandleList(const HandleList &h) {
            length = h.length;
            list = new jint[length];
            size = h.size;
            memcpy(list,h.list,sizeof(jint) * size);
        }

        HandleList::~HandleList() {
            delete[] list;
        }

        void HandleList::add(jint handle) {
            if (size >= length) {
                jint* newList = new jint[length = length << 1];
                memcpy(newList,list,sizeof(jint) * size);
                delete[] list;
                list = newList;
            }
            list[size++] = handle;
        }

        jint HandleList::get(jint index) {
            if (index >= size || index < 0) {
                stringstream ss;
                ss<<"size:"<<size<<" index:"<<index;
                throw new JIndexOutOfBoundsException(ss.str());
            }
            return list[index];
        }

        jint HandleList::getSize(){
            return size;
        }
    }
}
