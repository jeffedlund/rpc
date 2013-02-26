#ifndef HANDLELIST_H
#define HANDLELIST_H

namespace jcpp{
    namespace io{
        //HandleList
        class HandleList {
            int* list;
            int length;
            int size;
        public:
            HandleList();

            HandleList(const HandleList &h);

            ~HandleList();

            void add(int handle);

            int get(int index);

            int getSize();
        };
    }
}

#endif // HANDLELIST_H
