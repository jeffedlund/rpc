#include "JDataInputStream.h"
#include "JIndexOutOfBoundsException.h"
#include "JEOFException.h"
#include "JUTFDataFormatException.h"
#include "Object.h"

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
                jint count = in->read(b, off + n, len - n);
                if (count < 0){
                    throw new JEOFException;
                }
                n += count;
            }
        }

        string JDataInputStream::readUTF() {
            jushort utflen = in->readUnsignedShort();
            jbyte *bytearr = new jbyte[utflen*2];
            char *chararr = new char[utflen*2+1];

            jint c, char2, char3;
            jint count = 0;
            jint chararr_count = 0;

            readFully(bytearr, 0, utflen);

            while (count < utflen) {
                c = (jint) bytearr[count] & 0xff;
                if (c > 127) break;
                count++;
                chararr[chararr_count++] = (char)c;
            }

            while (count < utflen) {
                c = (jint) bytearr[count] & 0xff;
                switch (c >> 4) {
                case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7:
                    /* 0xxxxxxx*/
                    count++;
                    chararr[chararr_count++] = (char)c;
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
                    chararr[chararr_count++] = (char)(((c & 0x1F) << 6) | (char2 & 0x3F));
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
                    chararr[chararr_count++] = (char) (((c     & 0x0F) << 12) |
                                                       ((char2 & 0x3F) << 6)  |
                                                       ((char3 & 0x3F) << 0));
                    break;
                default:
                    /* 10xx xxxx,  1111 xxxx */
                    throw new JUTFDataFormatException("malformed input around byte ");
                }
            }

            // The number of chars produced may be less than utflen
            chararr[chararr_count] = '\0';
            string str(chararr);
            delete[] bytearr;
            delete[] chararr;
            return str;
        }

        jlong JDataInputStream::available() {
            return in->available();
        }

        bool JDataInputStream::waitForReadyRead(int timeout) {
            return in->waitForReadyRead(timeout);
        }

        jint JDataInputStream::read() {
            return in->read();
        }

        jint JDataInputStream::read(jbyte b[], int off, int len) {
            return in->read(b,off,len);
        }

        jbyte JDataInputStream::peekByte() {
            return in->peekByte();
        }

        jbyte JDataInputStream::readByte() {
            return in->readByte();
        }

        jshort JDataInputStream::readShort() {
            return in->readShort();
        }

        jushort JDataInputStream::readUnsignedShort() {
            return in->readUnsignedShort();
        }

        jint JDataInputStream::readInt() {
            return in->readInt();
        }

        jlong JDataInputStream::readLong() {
            return in->readLong();
        }

        float JDataInputStream::readFloat() {
            return in->readFloat();
        }

        double JDataInputStream::readDouble() {
            return in->readDouble();
        }

        char JDataInputStream::readChar() {
            return in->readChar();
        }

        bool JDataInputStream::readBool() {
            return in->readBool();
        }

        void JDataInputStream::close() {
            in->close();
        }

        JDataInputStream::~JDataInputStream() {
            close();
        }
    }
}
