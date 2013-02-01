#include "JStackTraceElement.h"
#include "JClass.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class JStackTraceElementClass : public JClass{
  public:
    JStackTraceElementClass(){
        this->canonicalName="java.lang.StackTraceElement";
        this->name="java.lang.StackTraceElement";
        this->simpleName="StackTraceElement";
        this->serialVersionUID=6992337162326171013L;
    }

    JClass* getSuperclass(){
        return JObject::getClazz();
    }

    JObject* newInstance(){
        return new JStackTraceElement();
    }
};

static JClass* clazz;

JClass* JStackTraceElement::getClazz(){
    if (clazz==NULL){
        clazz=new JStackTraceElementClass();
    }
    return clazz;
}

JStackTraceElement::JStackTraceElement():JObject(getClazz()){
}

string JStackTraceElement::getDeclaringClass(){
    return declaringClass;
}

void JStackTraceElement::setDeclaringClass(string declaringClass){
    this->declaringClass=declaringClass;
}

string JStackTraceElement::getMethodName(){
    return methodName;
}

void JStackTraceElement::setMethodName(string methodName){
    this->methodName=methodName;
}

string JStackTraceElement::getFileName(){
    return fileName;
}

void JStackTraceElement::setFileName(string fileName){
    this->fileName=fileName;
}

int JStackTraceElement::getLineNumber(){
    return lineNumber;
}

void JStackTraceElement::setLineNumber(int lineNumber){
    this->lineNumber=lineNumber;
}

string JStackTraceElement::toString(){
    stringstream ss;
    ss<<getDeclaringClass()<<"."<<getMethodName();
    ss<<"("<<getFileName()<<":"<<getLineNumber()<<")";
    return ss.str();
}

JStackTraceElement::~JStackTraceElement(){
}

