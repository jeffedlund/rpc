#ifndef HANDLELIST_H
#define HANDLELIST_H

//HandleList
class HandleList {
    int* list;
    int length;
    int size;
    bool operator==(const HandleList &h);

public:
    HandleList();

    HandleList(const HandleList &h);

    ~HandleList();

    void add(int handle);

    int get(int index);

    int getSize();
};

#endif // HANDLELIST_H
