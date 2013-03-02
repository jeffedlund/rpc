#include "JDataInputStream.h"
#include "JIndexOutOfBoundsException.h"
#include "JEOFException.h"
#include "JUTFDataFormatException.h"
#include "Object.h"
#include "Collections.h"
#include "JBits.h"
using namespace jcpp::util;

namespace jcpp{
    namespace io{
        //TODO implement skipBytes,readUnsignedByte,readLine
        class JDataInputStreamClass : public JClass{
        public:
            JDataInputStreamClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.io.DataInputStream";
                name="java.io.DataInputStream";
                simpleName="DataInputStream";
            }

            JClass* getSuperclass(){
                return JInputStream::getClazz();
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

        JDataInputStream::JDataInputStream():JInputStream(getClazz()){
        }

        JDataInputStream::JDataInputStream(JInputStream *in):JInputStream(getClazz()){
            this->in = in;
        }

        void JDataInputStream::setInputStream(JInputStream *in){
            this->in=in;
        }

        void JDataInputStream::readFully(jbyte b[], jint off, jint len) {
            if (len < 0){
                throw new JIndexOutOfBoundsException;
            }
            int n = 0;
            while (n < len) {
                jint count = read(b, off + n, len - n);
                if (count < 0){
                    throw new JEOFException;
                }
                n += count;
            }
        }

        string JDataInputStream::readUTF() {
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
            char* cs=new char[arrayLength(chararr)+1];
            JBits::fromJChartoChar(chararr,cs,0,arrayLength(chararr));
            cs[arrayLength(chararr)] = '\0';
            string str(cs);
            delete[] bytearr;
            delete[] chararr;
            delete cs;
            return str;
        }

        jlong JDataInputStream::available() {
            return in->available();
        }

        bool JDataInputStream::waitForReadyRead(int timeout) {
            return in->waitForReadyRead(timeout);
        }

        jbyte JDataInputStream::read() {
            return readByte();
        }

        jint JDataInputStream::read(jbyte b[], int off, int len) {
            return in->read(b,off,len);
        }

        jbyte JDataInputStream::readByte() {
            return in->read();
        }

        jbyte JDataInputStream::peekByte() {
            return in->peekByte();
        }

        jshort JDataInputStream::readShort() {
            jbyte ch1 = readByte();
            jbyte ch2 = readByte();
            if ((ch1 | ch2) < 0){
                throw new JEOFException();
            }
            return (jshort)((ch1 << 8) + (ch2 << 0));
        }

        jshort JDataInputStream::readUnsignedShort() {
            return readShort();
        }

        jint JDataInputStream::readInt() {
            jbyte ch1 = readByte();
            jbyte ch2 = readByte();
            jbyte ch3 = readByte();
            jbyte ch4 = readByte();
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
            delete readBuffer;
            return l;
        }

        jfloat JDataInputStream::readFloat() {
            jbyte* b=new jbyte[4];
            for (int i=0;i<4;i++){
                b[i]=readByte();
            }
            jfloat jf=JBits::getFloat(b,0);
            delete b;
            return jf;
        }

        jdouble JDataInputStream::readDouble() {
            jbyte* b=new jbyte[8];
            while (available() < 8) {
                waitForReadyRead(-1);//TODO
            }
            for (int i=0;i<8;i++){
                b[i]=readByte();
            }
            jdouble jd=JBits::getDouble(b,0);
            delete b;
            return jd;
        }

        jchar JDataInputStream::readChar() {
            jbyte ch1 = readByte();
            jbyte ch2 = readByte();
            if ((ch1 | ch2) < 0){
                throw new JEOFException();
            }
            return (jchar)((ch1 << 8) + (ch2 << 0));
        }

        jbool JDataInputStream::readBool() {
            jbyte b=readByte();
            if (b<0){
                throw new JEOFException();
            }
            return b!=0;
        }

        void JDataInputStream::close() {
            in->close();
        }

        JDataInputStream::~JDataInputStream() {
        }
    }
}
