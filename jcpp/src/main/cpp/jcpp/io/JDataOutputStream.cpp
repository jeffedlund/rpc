#include <iostream>
#include "JDataOutputStream.h"
#include "JBits.h"
#include "JUTFDataFormatException.h"
#include <sstream>
#include "Object.h"
#include "Collections.h"
#include "JInteger.h"
using namespace jcpp::util;
using namespace jcpp::lang;

namespace jcpp{
    namespace io{
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
            written=0;
            this->length=0;
            this->bytearr=NULL;
            this->out=NULL;
        }

        JDataOutputStream::JDataOutputStream(JOutputStream *out):JOutputStream(getClazz()){
            this->out =out;
            written=0;
            this->length=0;
            this->bytearr=NULL;
        }

        void JDataOutputStream::incCount(jint value){
            jint temp = written + value;
            if (temp < 0) {
                temp = JInteger::MAX_VALUE;
            }
            written = temp;
        }

        void JDataOutputStream::write(jbyte b){
            out->write(b);
            incCount(1);
        }

        void JDataOutputStream::write(jbyte b[], int off, int len){
            out->write(b, off, len);
            incCount(len);
        }

        void JDataOutputStream::flush(){
            out->flush();
        }

        void JDataOutputStream::close(){
            out->close();
        }

        void JDataOutputStream::writeBoolean(jbool v){
            write(v ? (jbyte)1 : (jbyte)0);
        }

        void JDataOutputStream::writeByte(jbyte v){
            write(v);
        }

        void JDataOutputStream::writeShort(jshort v){
            write((jbyte)(v >> 8) & 0xFF);
            write((jbyte)(v >> 0) & 0xFF);
        }

        void JDataOutputStream::writeChar(jchar v){
            write((jbyte)(v >> 8) & 0xFF);
            write((jbyte)(v >> 0) & 0xFF);
        }

        void JDataOutputStream::writeInt(jint v){
            write((jbyte)(v >> 24) & 0xFF);
            write((jbyte)(v >> 16) & 0xFF);
            write((jbyte)(v >>  8) & 0xFF);
            write((jbyte)(v >>  0) & 0xFF);
        }

        void JDataOutputStream::writeLong(jlong v){
            writeBuffer[0] = (v >> 56);
            writeBuffer[1] = (v >> 48);
            writeBuffer[2] = (v >> 40);
            writeBuffer[3] = (v >> 32);
            writeBuffer[4] = (v >> 24);
            writeBuffer[5] = (v >> 16);
            writeBuffer[6] = (v >>  8);
            writeBuffer[7] = (v >>  0);
            write(writeBuffer, 0, 8);
        }

        void JDataOutputStream::writeFloat(jfloat v){/* unresolved issue. */
            jbyte b[4];
            JBits::putFloat(b, 0, v);
            jint* val = (jint*)b;
            writeInt(*val);
        }

        void JDataOutputStream::writeDouble(jdouble v){ /* unresolved issue. */
            jbyte b[8];
            JBits::putDouble(b, 0, v);
            jlong* val = (jlong*)b;
            writeLong(*val);
        }

        void JDataOutputStream::writeBytes(string s){
            jint len = s.length();
            jbyte b;
            for (jint i = 0 ; i < len ; i++) {
                JBits::fromCharToJByte(&b,s.c_str()[i]);
                write(b);
            }
        }

        void JDataOutputStream::writeChars(string s){
            jint len = s.length();
            for (jint i = 0 ; i < len ; i++) {
                jint v = s.c_str()[i];
                write((jbyte)(v >> 8) & 0xFF);
                write((jbyte)(v >> 0) & 0xFF);
            }
        }

        void JDataOutputStream::writeUTF(string str){
            writeUTF(str, this);
        }

        jint JDataOutputStream::writeUTF(string str, JOutputStream *out){
            jint strlen = str.length();
            jint utflen = 0;
            jint c, count = 0;

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

            if (utflen > 65535){
                stringstream ss;
                ss<<"encoded string too long "<<utflen;
                throw new JUTFDataFormatException(ss.str());
            }

            JDataOutputStream* dos = (JDataOutputStream*)out;
            if(dos->bytearr == NULL || (dos->length < (utflen+2))){
                dos->length  = (utflen*2) + 2;
                if (dos->bytearr!=NULL){
                    delete dos->bytearr;
                }
                dos->bytearr = new jbyte[dos->length];
            }
            jbyte* bytearr = dos->bytearr;

            bytearr[count++] = (jbyte) ((utflen >> 8) & 0xFF);
            bytearr[count++] = (jbyte) ((utflen >> 0) & 0xFF);

            jint i=0;
            for (i=0; i < strlen; i++) {
               c = str.c_str()[i];
               if (!((c >= 0x0001) && (c <= 0x007F))) break;
               bytearr[count++] = (jbyte) c;
            }
            for (;i < strlen; i++){
               c = str.c_str()[i];
                if ((c >= 0x0001) && (c <= 0x007F)) {
                    bytearr[count++] = (jbyte) c;

                } else if (c > 0x07FF) {
                    bytearr[count++] = (jbyte) (0xE0 | ((c >> 12) & 0x0F));
                    bytearr[count++] = (jbyte) (0x80 | ((c >>  6) & 0x3F));
                    bytearr[count++] = (jbyte) (0x80 | ((c >>  0) & 0x3F));
                } else {
                    bytearr[count++] = (jbyte) (0xC0 | ((c >>  6) & 0x1F));
                    bytearr[count++] = (jbyte) (0x80 | ((c >>  0) & 0x3F));
                }
            }
            write(bytearr, 0, utflen+2);
            return utflen + 2;

        }

        jint JDataOutputStream::size(){
            return written;
        }

        JDataOutputStream::~JDataOutputStream(){
            delete[] bytearr;
        }
    }
}
