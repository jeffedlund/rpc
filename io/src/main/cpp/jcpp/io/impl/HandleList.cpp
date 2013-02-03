#include "HandleList.h"
#include "memory.h"
#include "JIndexOutOfBoundsException.h"
#include <sstream>

//HandleList
bool HandleList::operator==(const HandleList &h){
    return false;
}

HandleList::HandleList() {
    length = 4;
    list = new int[length];
    for (int i = 0; i < length ; ++i) {
        list[i] = 0;
    }
    size = 0;
}

HandleList::HandleList(const HandleList &h) {
    length = h.length;
    list = new int[length];
    size = h.size;
    memcpy(list,h.list,sizeof(int) * size);
}

HandleList::~HandleList() {
    delete[] list;
}

void HandleList::add(int handle) {
    if (size >= length) {
        int* newList = new int[length = length << 1];
        memcpy(newList,list,sizeof(int) * size);
        delete[] list;
        list = newList;
    }
    list[size++] = handle;
}

int HandleList::get(int index) {
    if (index >= size || index < 0) {
        stringstream ss;
        ss<<"size:"<<size<<" index:"<<index;
        throw new JIndexOutOfBoundsException(ss.str());
    }
    return list[index];
}

int HandleList::getSize(){
    return size;
}

