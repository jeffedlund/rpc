#include "JSampleObject.h"
#include <sstream>

class JSampleObjectClass : public JClass{
  public:
    JSampleObjectClass(){
        this->canonicalName="SampleObject";
        this->name="SampleObject";
        this->simpleName="SampleObject";
        this->serialVersionUID=40;
    }

    JClass* getSuperclass(){
        return JObject::getClazz();
    }

    JObject* newInstance(){
        return new JSampleObject();
    }
};

static JClass* clazz;

JClass* JSampleObject::getClazz(){
    if (clazz==NULL){
        clazz=new JSampleObjectClass();
    }
    return NULL;
}

JSampleObject::JSampleObject():JObject(getClazz()){
}

JPrimitiveBoolean* JSampleObject::getBool1(){
    return bool1;
}

void JSampleObject::setBool1(JPrimitiveBoolean* bool1){
    this->bool1=bool1;
}

JPrimitiveByte* JSampleObject::getByte1(){
    return byte1;
}

void JSampleObject::setByte1(JPrimitiveByte* byte1){
    this->byte1=byte1;
}

JPrimitiveChar* JSampleObject::getC1(){
    return c1;
}

void JSampleObject::setC1(JPrimitiveChar* c1){
    this->c1=c1;
}

JPrimitiveDouble* JSampleObject::getD1(){
    return d1;
}

void JSampleObject::setD1(JPrimitiveDouble* d1){
    this->d1=d1;
}

JPrimitiveFloat* JSampleObject::getF1(){
    return f1;
}

void JSampleObject::setF1(JPrimitiveFloat* f1){
    this->f1=f1;
}

JPrimitiveLong* JSampleObject::getL1(){
    return l1;
}

void JSampleObject::setL1(JPrimitiveLong* l1){
    this->l1=l1;
}

JPrimitiveShort* JSampleObject::getS1(){
    return s1;
}

void JSampleObject::setS1(JPrimitiveShort* s1){
    this->s1=s1;
}

JPrimitiveInt* JSampleObject::getI1(){
    return i1;
}

void JSampleObject::setI1(JPrimitiveInt* i1){
    this->i1=i1;
}

string JSampleObject::toString(){
    stringstream ss;
    ss<<"bool1="<<bool1<<"\r\n";
    ss<<"byte1="<<byte1<<"\r\n";
    ss<<"c1="<<c1<<"\r\n";
    ss<<"d1="<<d1<<"\r\n";
    ss<<"f1="<<f1<<"\r\n";
    ss<<"l1="<<l1<<"\r\n";
    ss<<"s1="<<s1<<"\r\n";
    ss<<"i1="<<i1<<"\r\n";
    return ss.str();
}

JSampleObject::~JSampleObject(){
    delete bool1;
    delete byte1;
    delete c1;
    delete d1;
    delete f1;
    delete l1;
    delete s1;
    delete i1;
}
