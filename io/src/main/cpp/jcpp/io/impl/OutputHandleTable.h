#ifndef OUTPUTHANDLETABLE_H
#define OUTPUTHANDLETABLE_H

#include "JObject.h"
#include <map>
using namespace std;

class OutputHandleTable{
private:
    qint32 handle;
    map<JObject*, qint32>*  handleByObject;

public:
    OutputHandleTable();

    qint32 assign(JObject *obj);
    void clear();
    qint32 lookup(JObject* obj);
    ~OutputHandleTable();
};

#endif // OUTPUTHANDLETABLE_H
