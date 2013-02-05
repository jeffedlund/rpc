#include <iostream>
#include "JDataOutputStream.h"
#include "JBits.h"

class JDataOutputStreamClass : public JClass{
public:
    JDataOutputStreamClass():JClass(JClassLoader::getBootClassLoader()){
        canonicalName="java.io.DataOutputStream";
        name="java.io.DataOutputStream";
        simpleName="DataOutputStream";
    }

    JClass* getSuperclass(){
        return JOutputStream::getClazz();
    }

    JObject* newInstance(){
        return new JDataOutputStream();
    }
};

static JClass* clazz;

JClass* JDataOutputStream::getClazz(){
    if (clazz==NULL){
        clazz=new JDataOutputStreamClass();
    }
    return clazz;
}

JDataOutputStream::JDataOutputStream():JOutputStream(getClazz()){
}

JDataOutputStream::JDataOutputStream(JOutputStream *out):JOutputStream(getClazz()){
    this->out =out;
}

void JDataOutputStream::incCount(qint32 value){
    qint32 temp = written + value;
    if (temp < 0) {
        temp = 0x7fffffff;
    }
    written = temp;
}

void JDataOutputStream::write(qint32 b){
    out->write(b);
    incCount(1);
}

void JDataOutputStream::write(qint8 b[], int off, int len){
    out->write(b, off, len);
    incCount(len);
    delete[] b;
}

void JDataOutputStream::flush(){
    out->flush();
}

void JDataOutputStream::close(){
    out->close();
}

void JDataOutputStream::writeBoolean(bool v){
    out->write(v ? 1 : 0);
    incCount(1);
}

void JDataOutputStream::writeByte(qint8 v){
    out->write(v);
    incCount(1);
}

void JDataOutputStream::writeShort(qint16 v){
    out->write(((quint32)v >> 8) & 0xFF);
    out->write(((quint32)v >> 0) & 0xFF);
    incCount(2);
}

void JDataOutputStream::writeChar(quint16 v){
    out->write(((quint32)v >> 8) & 0xFF);
    out->write(((quint32)v >> 0) & 0xFF);
    incCount(2);
}

void JDataOutputStream::writeInt(qint32 v){
    out->write(((quint32)v >> 24) & 0xFF);
    out->write(((quint32)v >> 16) & 0xFF);
    out->write(((quint32)v >>  8) & 0xFF);
    out->write(((quint32)v >>  0) & 0xFF);
    delete[] (qint32*)v;
    incCount(4);
}

void JDataOutputStream::writeLong(qint64 v){
    writeBuffer[0] = (quint8)(v >> 56);
    writeBuffer[1] = (quint8)(v >> 48);
    writeBuffer[2] = (quint8)(v >> 40);
    writeBuffer[3] = (quint8)(v >> 32);
    writeBuffer[4] = (quint8)(v >> 24);
    writeBuffer[5] = (quint8)(v >> 16);
    writeBuffer[6] = (quint8)(v >>  8);
    writeBuffer[7] = (quint8)(v >>  0);
    out->write(writeBuffer, 0, 8);
    incCount(8);
}

void JDataOutputStream::writeFloat(float v){/* unresolved issue. */
    qint8 b[4];
    JBits::putFloat(b, 0, v);
    qint32* val = (qint32*)b;
    writeInt(*val);
    delete[] b;
    incCount(4);
}

void JDataOutputStream::writeDouble(double v){ /* unresolved issue. */
    qint8 b[8];
    JBits::putDouble(b, 0, v);
    double* val = (double*)b;
    writeLong(*val);
    delete[] b;
    incCount(8);
}

void JDataOutputStream::writeBytes(string s){
    qint32 len = s.length();
    for (qint32 i = 0 ; i < len ; i++) {
        out->write((qint8)s.c_str()[i]);
    }
    incCount(len);
}

void JDataOutputStream::writeChars(string s){
    qint32 len = s.length();
    for (qint32 i = 0 ; i < len ; i++) {
        qint32 v = s.c_str()[i];
        out->write(((quint32)v >> 8) & 0xFF);
        out->write(((quint32)v >> 0) & 0xFF);
    }
    incCount(len * 2);
}

void JDataOutputStream::writeUTF(string str){
    writeUTF(str, this);
}

qint32 JDataOutputStream::writeUTF(string str, JOutputStream *out){
    qint32 strlen = str.length();
    qint32 utflen = 0;
    qint32 c, count = 0;

    /* use charAt instead of copying String to char array */
    for (int i = 0; i < strlen; i++) {
        c = str.c_str()[i];
        if ((c >= 0x0001) && (c <= 0x007F)) {
            utflen++;
        } else if (c > 0x07FF) {
            utflen += 3;
        } else {
            utflen += 2;
        }
    }

    if (utflen > 65535)
        throw;

        JDataOutputStream* dos = (JDataOutputStream*)out;
        if(dos->bytearr == NULL || (sizeof(dos->bytearr) < (utflen+2))){
            dos->length  = (utflen*2) + 2;
            dos->bytearr = new qint8[dos->length];
        }
        length = dos->length;
        qint8* bytearr = dos->bytearr;

    bytearr[count++] = (qint8) (((quint8)utflen >> 8) & 0xFF);
    bytearr[count++] = (qint8) (((quint8)utflen >> 0) & 0xFF);

    qint32 i=0;
    for (i=0; i < strlen; i++) {
       c = str.c_str()[i];
       if (!((c >= 0x0001) && (c <= 0x007F))) break;
       bytearr[count++] = (qint8) c;
    }
    for (;i < strlen; i++){
       c = str.c_str()[i];
        if ((c >= 0x0001) && (c <= 0x007F)) {
            bytearr[count++] = (qint8) c;

        } else if (c > 0x07FF) {
            bytearr[count++] = (qint8) (0xE0 | ((c >> 12) & 0x0F));
            bytearr[count++] = (qint8) (0x80 | ((c >>  6) & 0x3F));
            bytearr[count++] = (qint8) (0x80 | ((c >>  0) & 0x3F));
        } else {
            bytearr[count++] = (qint8) (0xC0 | ((c >>  6) & 0x1F));
            bytearr[count++] = (qint8) (0x80 | ((c >>  0) & 0x3F));
        }
    }
    out->write(bytearr, 0, utflen+2);
    return utflen + 2;

}

qint32 JDataOutputStream::size(){
    return written;
}

JDataOutputStream::~JDataOutputStream(){
    delete out;
    delete[] bytearr;
    delete[] writeBuffer;
}
