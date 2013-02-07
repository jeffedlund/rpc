#ifndef OUTPUTHANDLETABLE_H
#define OUTPUTHANDLETABLE_H

#include "JObject.h"
#include <map>
using namespace std;

//TODO getClazz
class OutputHandleTable{
private:
    qint32 handle;
    map<JObject*, qint32>*  handleByObject;

public:
    OutputHandleTable();

    qint32 assign(JObject *obj);
    int size();
    void clear();
    qint32 lookup(JObject* obj);
    ~OutputHandleTable();
};

#endif // OUTPUTHANDLETABLE_H
