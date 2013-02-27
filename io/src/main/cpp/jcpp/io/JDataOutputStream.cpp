#include <iostream>
#include "JDataOutputStream.h"
#include "JBits.h"
#include "JUTFDataFormatException.h"
#include <sstream>
#include "Object.h"
using namespace jcpp::util;

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
        }

        JDataOutputStream::JDataOutputStream(JOutputStream *out):JOutputStream(getClazz()){
            this->out =out;
        }

        void JDataOutputStream::incCount(jint value){
            jint temp = written + value;
            if (temp < 0) {
                temp = 0x7fffffff;
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
            out->write(v ? 1 : 0);
            incCount(1);
        }

        void JDataOutputStream::writeByte(jbyte v){
            out->write(v);
            incCount(1);
        }

        void JDataOutputStream::writeShort(jshort v){
            out->write(((juint)v >> 8) & 0xFF);
            out->write(((juint)v >> 0) & 0xFF);
            incCount(2);
        }

        void JDataOutputStream::writeChar(jchar v){
            out->write(((juint)v >> 8) & 0xFF);
            out->write(((juint)v >> 0) & 0xFF);
            incCount(2);
        }

        void JDataOutputStream::writeInt(jint v){
            out->write(((juint)v >> 24) & 0xFF);
            out->write(((juint)v >> 16) & 0xFF);
            out->write(((juint)v >>  8) & 0xFF);
            out->write(((juint)v >>  0) & 0xFF);
            incCount(4);
        }

        void JDataOutputStream::writeLong(jlong v){
            writeBuffer[0] = (jubyte)(v >> 56);
            writeBuffer[1] = (jubyte)(v >> 48);
            writeBuffer[2] = (jubyte)(v >> 40);
            writeBuffer[3] = (jubyte)(v >> 32);
            writeBuffer[4] = (jubyte)(v >> 24);
            writeBuffer[5] = (jubyte)(v >> 16);
            writeBuffer[6] = (jubyte)(v >>  8);
            writeBuffer[7] = (jubyte)(v >>  0);
            out->write(writeBuffer, 0, 8);
            incCount(8);
        }

        void JDataOutputStream::writeFloat(jfloat v){/* unresolved issue. */
            jbyte b[4];
            JBits::putFloat(b, 0, v);
            jint* val = (jint*)b;
            writeInt(*val);
            incCount(4);
        }

        void JDataOutputStream::writeDouble(jdouble v){ /* unresolved issue. */
            jbyte b[8];
            JBits::putDouble(b, 0, v);
            double* val = (double*)b;
            writeLong(*val);
            incCount(8);
        }

        void JDataOutputStream::writeBytes(string s){
            jint len = s.length();
            for (jint i = 0 ; i < len ; i++) {
                out->write((jbyte)s.c_str()[i]);
            }
            incCount(len);
        }

        void JDataOutputStream::writeChars(string s){
            jint len = s.length();
            for (jint i = 0 ; i < len ; i++) {
                jint v = s.c_str()[i];
                out->write(((juint)v >> 8) & 0xFF);
                out->write(((juint)v >> 0) & 0xFF);
            }
            incCount(len * 2);
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
            if(dos->bytearr == NULL || (sizeof(dos->bytearr) < (unsigned )(utflen+2))){
                dos->length  = (utflen*2) + 2;
                if (dos->bytearr!=NULL){
                    delete dos->bytearr;
                }
                dos->bytearr = new jbyte[dos->length];
            }
            length = dos->length;
            jbyte* bytearr = dos->bytearr;

            bytearr[count++] = (jbyte) (((jubyte)utflen >> 8) & 0xFF);
            bytearr[count++] = (jbyte) (((jubyte)utflen >> 0) & 0xFF);

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
            out->write(bytearr, 0, utflen+2);
            return utflen + 2;

        }

        jint JDataOutputStream::size(){
            return written;
        }

        JDataOutputStream::~JDataOutputStream(){
            delete out;
            delete[] bytearr;
            delete[] writeBuffer;
        }
    }
}
