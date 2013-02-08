#include "QtDataOutputStream.h"
#include "JIndexOutOfBoundsException.h"
#include "JNullPointerException.h"

class QtDataOutputStreamClass : public JClass{
public:
    QtDataOutputStreamClass():JClass(JClassLoader::getBootClassLoader()){
        canonicalName="java.io.QtDataOutputStream";//not usefull...
        name="java.io.QtDataOutputStream";
        simpleName="QtDataOutputStream";
    }

    JClass* getSuperclass(){
        return JOutputStream::getClazz();
    }

    JObject* newInstance(){
        return new QtDataOutputStream();
    }
};

static JClass* clazz;

JClass* QtDataOutputStream::getClazz(){
    if (clazz==NULL){
        clazz=new QtDataOutputStreamClass();
    }
    return clazz;
}

QtDataOutputStream::QtDataOutputStream():JOutputStream(getClazz()){
}

QtDataOutputStream::QtDataOutputStream(QDataStream* out):JOutputStream(getClazz()){
    this->out=out;
}

QDataStream* QtDataOutputStream::getStream(){
    return out;
}

void QtDataOutputStream::setStream(QDataStream* out){
    this->out=out;
}

void QtDataOutputStream::write(qint32 b){
    (*out)<<((qint8)b);
}

void QtDataOutputStream::write(qint8 b[]){
    qint32 length = sizeof(b);
    for (int i=0;i<length;i++){
        (*out)<<b[i];
    }
}

void QtDataOutputStream::write(qint8 b[], int off, int len){
    if (b == NULL) {
        throw new JNullPointerException();
    } else {
        int length = len;
        if ((off < 0) || (off > length) || (len < 0) || ((off + len) > length) || ((off + len) < 0)) {
            throw new JIndexOutOfBoundsException();
        } else if (len == 0) {
            return;
        }
        for (int i = 0 ; i < len ; i++) {
            (*out)<<(b[off + i]);
        }
    }
}

void QtDataOutputStream::flush(){
    //TODO
}

void QtDataOutputStream::close(){
    out->device()->close();
}

void QtDataOutputStream::writeBoolean(bool v){
    (*out)<<v;
}

void QtDataOutputStream::writeByte(qint8 v){
    (*out) << v;
}

void QtDataOutputStream::writeDouble(double v){
    (*out) << v;
}

void QtDataOutputStream::writeChar(quint16 v){
    (*out) << v;
}

void QtDataOutputStream::writeFloat(float v){
    (*out) << v;
}

void QtDataOutputStream::writeInt(qint32 v){
    (*out) << v;
}

void QtDataOutputStream::writeLong(qint64 v){
    (*out) << v;
}

void QtDataOutputStream::writeShort(qint16 v){
    (*out) << v;
}

QtDataOutputStream::~QtDataOutputStream(){
}