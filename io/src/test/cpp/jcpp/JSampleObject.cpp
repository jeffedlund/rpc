#include "JSampleObject.h"
#include <sstream>
#include "JField.h"

class JBool1Field : public JField{
public:
    JBool1Field():JField("bool1",JPrimitiveBoolean::getClazz()){
    }

    JObject* get(JObject *object){
        JSampleObject* sampleObject=(JSampleObject*)object;
        return sampleObject->getBool1();
    }

    void set(JObject *object, JObject *value){
        JSampleObject* sampleObject=(JSampleObject*)object;
        sampleObject->setBool1((JPrimitiveBoolean*)value);
    }
};

class JByte1Field : public JField{
public:
    JByte1Field():JField("byte1",JPrimitiveByte::getClazz()){
    }

    JObject* get(JObject *object){
        JSampleObject* sampleObject=(JSampleObject*)object;
        return sampleObject->getByte1();
    }

    void set(JObject *object, JObject *value){
        JSampleObject* sampleObject=(JSampleObject*)object;
        sampleObject->setByte1((JPrimitiveByte*)value);
    }
};

class JChar1Field : public JField{
public:
    JChar1Field():JField("c1",JPrimitiveChar::getClazz()){
    }

    JObject* get(JObject *object){
        JSampleObject* sampleObject=(JSampleObject*)object;
        return sampleObject->getC1();
    }

    void set(JObject *object, JObject *value){
        JSampleObject* sampleObject=(JSampleObject*)object;
        sampleObject->setC1((JPrimitiveChar*)value);
    }
};

class JDouble1Field : public JField{
public:
    JDouble1Field():JField("d1",JPrimitiveDouble::getClazz()){
    }

    JObject* get(JObject *object){
        JSampleObject* sampleObject=(JSampleObject*)object;
        return sampleObject->getD1();
    }

    void set(JObject *object, JObject *value){
        JSampleObject* sampleObject=(JSampleObject*)object;
        sampleObject->setD1((JPrimitiveDouble*)value);
    }
};

class JFloat1Field : public JField{
public:
    JFloat1Field():JField("f1",JPrimitiveFloat::getClazz()){
    }

    JObject* get(JObject *object){
        JSampleObject* sampleObject=(JSampleObject*)object;
        return sampleObject->getF1();
    }

    void set(JObject *object, JObject *value){
        JSampleObject* sampleObject=(JSampleObject*)object;
        sampleObject->setF1((JPrimitiveFloat*)value);
    }
};

class JLong1Field : public JField{
public:
    JLong1Field():JField("l1",JPrimitiveLong::getClazz()){
    }

    JObject* get(JObject *object){
        JSampleObject* sampleObject=(JSampleObject*)object;
        return sampleObject->getL1();
    }

    void set(JObject *object, JObject *value){
        JSampleObject* sampleObject=(JSampleObject*)object;
        sampleObject->setL1((JPrimitiveLong*)value);
    }
};

class JShort1Field : public JField{
public:
    JShort1Field():JField("s1",JPrimitiveShort::getClazz()){
    }

    JObject* get(JObject *object){
        JSampleObject* sampleObject=(JSampleObject*)object;
        return sampleObject->getS1();
    }

    void set(JObject *object, JObject *value){
        JSampleObject* sampleObject=(JSampleObject*)object;
        sampleObject->setS1((JPrimitiveShort*)value);
    }
};

class JInt1Field : public JField{
public:
    JInt1Field():JField("i1",JPrimitiveInt::getClazz()){
    }

    JObject* get(JObject *object){
        JSampleObject* sampleObject=(JSampleObject*)object;
        return sampleObject->getI1();
    }

    void set(JObject *object, JObject *value){
        JSampleObject* sampleObject=(JSampleObject*)object;
        sampleObject->setI1((JPrimitiveInt*)value);
    }
};

class JSampleObjectClass : public JClass{
  public:
    JSampleObjectClass(){
        this->canonicalName="SampleObject";
        this->name="SampleObject";
        this->simpleName="SampleObject";
        this->serialVersionUID=40;
        addField(new JBool1Field());
        addField(new JByte1Field());
        addField(new JChar1Field());
        addField(new JDouble1Field());
        addField(new JFloat1Field());
        addField(new JLong1Field());
        addField(new JShort1Field());
        addField(new JInt1Field());
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
    return clazz;
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
    ss<<"bool1="<<bool1->toString()<<"\r\n";
    ss<<"byte1="<<byte1->toString()<<"\r\n";
    ss<<"c1="<<c1->toString()<<"\r\n";
    ss<<"d1="<<d1->toString()<<"\r\n";
    ss<<"f1="<<f1->toString()<<"\r\n";
    ss<<"l1="<<l1->toString()<<"\r\n";
    ss<<"s1="<<s1->toString()<<"\r\n";
    ss<<"i1="<<i1->toString()<<"\r\n";
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
