#include "JBufferedInputStream.h"
#include "Object.h"
#include "JNullPointerException.h"
#include "JIndexOutOfBoundsException.h"
#include "Collections.h"
#include "JIOException.h"
#include "JInstantiationException.h"
#include "JEOFException.h"
using namespace jcpp::util;

namespace jcpp{
    namespace io{
        class JBufferedInputStreamClass : public JClass{
        public:
            JBufferedInputStreamClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.io.BufferedInputStream";
                name="java.io.BufferedInputStream";
                simpleName="BufferedInputStream";
            }

            JClass* getSuperclass(){
                return JFilterInputStream::getClazz();
            }
        };

        static JClass* clazz;

        JClass* JBufferedInputStream::getClazz(){
            if (clazz==NULL){
                clazz=new JBufferedInputStreamClass();
            }
            return clazz;
        }

        JBufferedInputStream::JBufferedInputStream(JInputStream* in,jint size):JFilterInputStream(in,getClazz()){
            count=0;
            pos=0;
            markpos=-1;
            marklimit=0;
            buf=new vector<jbyte>();
            length=size;
        }

        JInputStream* JBufferedInputStream::getInIfOpen(){
            JInputStream* input = in;
            if (input == NULL){
                throw new JIOException("Stream closed");
            }
            return input;
        }

        vector<jbyte>* JBufferedInputStream::getBufIfOpen(){
            vector<jbyte>* buffer = buf;
             if (buffer == NULL){
                 throw new JIOException("Stream closed");
             }
             return buffer;
        }

        void JBufferedInputStream::fill(){
            vector<jbyte>* buffer = getBufIfOpen();
            if (markpos < 0){
                pos = 0;
            }else if (pos >= length){
                if (markpos > 0) {
                    jint sz = pos - markpos;
                    arraycopy(buffer, markpos, buffer, 0, sz);
                    pos = sz;
                    markpos = 0;
                } else if (length >= marklimit) {
                    markpos = -1;
                    pos = 0;
                } else {
                    jint nsz = pos * 2;
                    if (nsz > marklimit){
                        nsz = marklimit;
                    }
                    vector<jbyte>* nbuf = new vector<jbyte>();
                    length=nsz;
                    arraycopy(buffer, 0, nbuf, 0, pos);
                    delete buffer;
                    buffer = nbuf;
                }
                count = pos;
                jint n = getInIfOpen()->read(&((*buffer)[pos]), 0, length - pos);
                if (n > 0){
                    count = n + pos;
                }
            }
        }

        jint JBufferedInputStream::read(){
            if (pos >= count) {
                fill();
                if (pos >= count){
                    return -1;
                }
            }
            return getBufIfOpen()->at(pos++) & 0xff;
        }

        jint JBufferedInputStream::read1(jbyte b[], jint off, jint len){
            jint avail = count - pos;
            if (avail <= 0) {
                if (len >= length && markpos < 0) {
                    return getInIfOpen()->read(b, off, len);
                }
                fill();
                avail = count - pos;
                if (avail <= 0){
                    return -1;
                }
            }
            jint cnt = (avail < len) ? avail : len;
            arraycopy(getBufIfOpen(), pos, b, off, cnt);
            pos += cnt;
            return cnt;
        }

        jint JBufferedInputStream::read(jbyte b[], jint off, jint len){
            getBufIfOpen();
            if (len == 0) {
                return 0;
            }
            jint n = 0;
            for (;;) {
                jint nread = read1(b, off + n, len - n);
                if (nread <= 0){
                    return (n == 0) ? nread : n;
                }
                n += nread;
                if (n >= len){
                    return n;
                }
                JInputStream* input = in;
                if (input != NULL && input->available() <= 0){
                    return n;
                }
            }
        }

        jlong JBufferedInputStream::skip(jlong n){
            getBufIfOpen();
            if (n <= 0) {
                return 0;
            }
            jlong avail = count - pos;
            if (avail <= 0) {
                if (markpos <0) {
                    return getInIfOpen()->skip(n);
                }
                fill();
                avail = count - pos;
                if (avail <= 0){
                    return 0;
                }
            }
            jlong skipped = (avail < n) ? avail : n;
            pos += skipped;
            return skipped;
        }

        jint JBufferedInputStream::available(){
            return getInIfOpen()->available() + (count - pos);
        }

        jint JBufferedInputStream::peek(){
            if (pos >= count) {
                fill();
                if (pos >= count){
                    return -1;
                }
            }
            return getBufIfOpen()->at(pos) & 0xff;
        }

        void JBufferedInputStream::mark(jint readlimit) {
            marklimit = readlimit;
            markpos = pos;
        }

        void JBufferedInputStream::reset(){
            getBufIfOpen();
            if (markpos < 0){
                throw new JIOException("Resetting to invalid mark");
            }
            pos = markpos;
        }

        jbool JBufferedInputStream::markSupported() {
            return true;
        }

        void JBufferedInputStream::close(){
            in->close();
        }

        JBufferedInputStream::~JBufferedInputStream() {
            delete buf;
            delete in;
        }
    }
}

