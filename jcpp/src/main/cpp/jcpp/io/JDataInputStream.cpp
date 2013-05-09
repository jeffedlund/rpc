#include "JDataInputStream.h"
#include "JIndexOutOfBoundsException.h"
#include "JEOFException.h"
#include "JUTFDataFormatException.h"
#include "Object.h"
#include "Collections.h"
#include "JBits.h"
#include "JPushbackInputStream.h"
#include "JSystem.h"
#include "JClassLoader.h"
using namespace jcpp::util;
using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class JDataInputStreamClass : public JClass{
        public:
            JDataInputStreamClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.io.DataInputStream";
                name="java.io.DataInputStream";
                simpleName="DataInputStream";
                addInterface(JDataInput::getClazz());
            }

            JClass* getSuperclass(){
                return JFilterInputStream::getClazz();
            }

            JObject* newInstance(){
                return new JDataInputStream();
            }
        };

        static JClass* clazz;

        JClass* JDataInputStream::getClazz(){
            if (clazz==NULL){
                clazz=new JDataInputStreamClass();
            }
            return clazz;
        }

        JDataInputStream::JDataInputStream():JFilterInputStream(NULL,getClazz()){
        }

        JDataInputStream::JDataInputStream(JInputStream *in):JFilterInputStream(in,getClazz()){
        }

        void JDataInputStream::setInputStream(JInputStream *in){
            this->in=in;
        }

        void JDataInputStream::readFully(jbyte b[], jint off, jint len) {
            if (len < 0){
                throw new JIndexOutOfBoundsException;
            }
            jint n = 0;
            while (n < len) {
                jint count = in->read(b, off + n, len - n);
                if (count < 0){
                    throw new JEOFException;
                }
                n += count;
            }
        }

        jint JDataInputStream::skipBytes(jint n){
            jint total = 0;
            jint cur = 0;

            while ((total<n) && ((cur = (jint) in->skip(n-total)) > 0)) {
                total += cur;
            }
            return total;
        }

        JString JDataInputStream::readUTF() {
            jshort utflen = readUnsignedShort();
            jbyte *bytearr = new jbyte[utflen*2];
            jchar *chararr = new jchar[utflen*2];

            jint c, char2, char3;
            jint count = 0;
            jint chararr_count = 0;

            readFully(bytearr, 0, utflen);

            while (count < utflen) {
                c = (jint) bytearr[count] & 0xff;
                if (c > 127) break;
                count++;
                chararr[chararr_count++] = (jchar)c;
            }

            while (count < utflen) {
                c = (jint) bytearr[count] & 0xff;
                switch (c >> 4) {
                case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7:
                    /* 0xxxxxxx*/
                    count++;
                    chararr[chararr_count++] = (jchar)c;
                    break;
                case 12: case 13:
                    /* 110x xxx  10xx xxx*/
                    count += 2;
                    if (count > utflen){
                        throw new JUTFDataFormatException("malformed input: partial character at end");
                    }
                    char2 = (jint) bytearr[count-1];
                    if ((char2 & 0xC0) != 0x80){
                        throw new JUTFDataFormatException("malformed input around byte ");
                    }
                    chararr[chararr_count++] = (jchar)(((c & 0x1F) << 6) | (char2 & 0x3F));
                    break;
                case 14:
                    /* 1110 xxxx  10xx xxxx  10xx xxxx */
                    count += 3;
                    if (count > utflen){
                        throw new JUTFDataFormatException("malformed input: partial character at end");
                    }
                    char2 = (jint) bytearr[count-2];
                    char3 = (jint) bytearr[count-1];
                    if (((char2 & 0xC0) != 0x80) || ((char3 & 0xC0) != 0x80))
                        throw new JUTFDataFormatException("malformed input around byte ");
                    chararr[chararr_count++] = (jchar) (((c     & 0x0F) << 12) |
                                                       ((char2 & 0x3F) << 6)  |
                                                       ((char3 & 0x3F) << 0));
                    break;
                default:
                    /* 10xx xxxx,  1111 xxxx */
                    throw new JUTFDataFormatException("malformed input around byte ");
                }
            }

            // The number of chars produced may be less than utflen
            char* cs=new char[chararr_count+1];
            for (jint i=0;i<chararr_count;i++){
                cs[i]=(char)chararr[i];
            }
            cs[chararr_count] = '\0';
            JString str(cs);//TODO
            delete[] bytearr;
            delete[] chararr;
            delete cs;
            return str;
        }

        jint JDataInputStream::available() {
            return in->available();
        }

        jint JDataInputStream::read(jbyte b[], jint off, jint len) {
            return in->read(b,off,len);
        }

        jbyte JDataInputStream::readByte() {
            jint b=in->read();
            if (b<0){
                throw new JEOFException();
            }
            return (jbyte)b;
        }

        jint JDataInputStream::readUnsignedByte() {
            jint b=in->read();
            if (b<0){
                throw new JEOFException();
            }
            return b;
        }

        jint JDataInputStream::peek() {
            return in->peek();
        }

        jshort JDataInputStream::readShort() {
            jint ch1 = in->read();
            jint ch2 = in->read();
            if ((ch1 | ch2) < 0){
                throw new JEOFException();
            }
            return (jshort)((ch1 << 8) + (ch2 << 0));
        }

        jint JDataInputStream::readUnsignedShort() {
            jint ch1 = in->read();
            jint ch2 = in->read();
            if ((ch1 | ch2) < 0){
                throw new JEOFException();
            }
            return ((ch1 << 8) + (ch2 << 0));
        }

        jint JDataInputStream::readInt() {
            jint ch1 = in->read();
            jint ch2 = in->read();
            jint ch3 = in->read();
            jint ch4 = in->read();
            if ((ch1 | ch2 | ch3 | ch4) < 0){
                throw new JEOFException();
            }
            return ((ch1 << 24) + (ch2 << 16) + (ch3 << 8) + (ch4 << 0));
        }

        jlong JDataInputStream::readLong() {
            jbyte* readBuffer = new jbyte[8];
            readFully(readBuffer, 0, 8);
            jlong l=( ((jlong)readBuffer[0] << 56) + ((jlong)(readBuffer[1] & 255) << 48) +
                      ((jlong)(readBuffer[2] & 255) << 40) + ((jlong)(readBuffer[3] & 255) << 32) +
                      ((jlong)(readBuffer[4] & 255) << 24) + ((readBuffer[5] & 255) << 16) +
                      ((readBuffer[6] & 255) <<  8) + ((readBuffer[7] & 255) <<  0));
            delete[] readBuffer;
            return l;
        }

        jfloat JDataInputStream::readFloat() {
            jbyte* b=new jbyte[4];
            for (jint i=0;i<4;i++){
                b[i]=(jbyte)in->read();
            }
            jfloat jf=JBits::getFloat(b,0);
            delete[] b;
            return jf;
        }

        jdouble JDataInputStream::readDouble() {
            jbyte* b=new jbyte[8];
            for (jint i=0;i<8;i++){
                b[i]=(jbyte)in->read();
            }
            jdouble jd=JBits::getDouble(b,0);
            delete[] b;
            return jd;
        }

        jchar JDataInputStream::readChar() {
            jint ch1 = in->read();
            jint ch2 = in->read();
            if ((ch1 | ch2) < 0){
                throw new JEOFException();
            }
            return (jchar)((ch1 << 8) + (ch2 << 0));
        }

        jbool JDataInputStream::readBool() {
            jint b=in->read();
            if (b<0){
                throw new JEOFException();
            }
            return b!=0;
        }

        JPrimitiveByte* JDataInputStream::readPrimitiveByte(){
            return new JPrimitiveByte(readByte());
        }

        JPrimitiveChar* JDataInputStream::readPrimitiveChar(){
            return new JPrimitiveChar(readChar());
        }

        JPrimitiveDouble* JDataInputStream::readPrimitiveDouble(){
            return new JPrimitiveDouble(readDouble());
        }

        JPrimitiveFloat* JDataInputStream::readPrimitiveFloat(){
            return new JPrimitiveFloat(readFloat());
        }

        JPrimitiveInt* JDataInputStream::readPrimitiveInt(){
            return new JPrimitiveInt(readInt());
        }

        JPrimitiveLong* JDataInputStream::readPrimitiveLong(){
            return new JPrimitiveLong(readLong());
        }

        JPrimitiveShort* JDataInputStream::readPrimitiveShort(){
            return new JPrimitiveShort(readShort());
        }

        JPrimitiveBoolean* JDataInputStream::readPrimitiveBool(){
            return new JPrimitiveBoolean(readBool());
        }

        void JDataInputStream::close() {
            in->close();
        }

        JDataInputStream::~JDataInputStream() {
        }
    }
}
