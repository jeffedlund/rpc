#ifndef JBITS_H
#define JBITS_H

#include "Object.h"
#include "JCPP.h"

namespace jcpp{
    namespace util{
        class JCPP_LIBRARY_EXPORT JBits {
        public:

            static void putBoolean(jbyte b[], int off, bool val) {
                b[off] = (jbyte) (val ? 1 : 0);
            }

            static void fromCharToJByte(jbyte b[], char bc[], int off, int len){
                for (int i=0;i<len;i++){
                    b[off+i]=(jbyte)bc[i];
                }
            }

            static void fromCharToJByte(jbyte b[], char c){
                b[0]=(jbyte)c;
            }

            static void putChar(jbyte b[], int off, jchar val) {
                b[off + 1] = (jbyte) (val >> 0);
                b[off + 0] = (jbyte) (val >> 8);
            }

            static void fromJChartoChar(jchar b[], char dest[], int off, int len) {
                for (int i=0;i<len;i++){
                    dest[off+i]=(char)b[i];
                }
            }

            static void fromCharToJChar(const char str[],jchar dest[],int off,int len){
                for (int i=0;i<len;i++){
                    dest[i+off]=str[i];
                }
            }

            static void fromJBytetoChar(jbyte b[], char dest[], int off, int len) {
                for (int i=0;i<len;i++){
                    dest[off+i]=(char)b[i];
                }
            }

            static void fromCharToJByte(char str[],jbyte dest[],int off,int len){
                for (int i=0;i<len;i++){
                    jbyte* b=(jbyte*)&dest[i+off];
                    b[0]=str[i]>>0;
                }
            }

            static void putShort(jbyte b[], int off, jshort val) {
                b[off + 1] = (jbyte) (val >> 0);
                b[off + 0] = (jbyte) (val >> 8);
            }

            static void putInt(jbyte b[], int off, jint val) {
                b[off + 3] = (jbyte) (val >> 0);
                b[off + 2] = (jbyte) (val >> 8);
                b[off + 1] = (jbyte) (val >> 16);
                b[off + 0] = (jbyte) (val >> 24);
            }

            static void putFloat(jbyte b[], int off, jfloat val) {
                jint* i = reinterpret_cast<jint*>(&val);
                b[off + 3] = (jbyte) (*i >> 0);
                b[off + 2] = (jbyte) (*i >> 8);
                b[off + 1] = (jbyte) (*i >> 16);
                b[off + 0] = (jbyte) (*i >> 24);
            }

            static void putLong(jbyte b[], int off, jlong val) {
                b[off + 7] = (jbyte) (val >> 0);
                b[off + 6] = (jbyte) (val >> 8);
                b[off + 5] = (jbyte) (val >> 16);
                b[off + 4] = (jbyte) (val >> 24);
                b[off + 3] = (jbyte) (val >> 32);
                b[off + 2] = (jbyte) (val >> 40);
                b[off + 1] = (jbyte) (val >> 48);
                b[off + 0] = (jbyte) (val >> 56);
            }

            static void putDouble(jbyte b[], int off, jdouble val) {
                jlong* j = reinterpret_cast<jlong*>(&val);
                b[off + 7] = (jbyte) (*j >> 0);
                b[off + 6] = (jbyte) (*j >> 8);
                b[off + 5] = (jbyte) (*j >> 16);
                b[off + 4] = (jbyte) (*j >> 24);
                b[off + 3] = (jbyte) (*j >> 32);
                b[off + 2] = (jbyte) (*j >> 40);
                b[off + 1] = (jbyte) (*j >> 48);
                b[off + 0] = (jbyte) (*j >> 56);
            }

            static jchar getChar(jbyte* b,jint off){
                return (jchar)(((b[off + 1] & 0xFF) << 0) + ((b[off + 0]) << 8));
            }

            static bool getBool(jbyte *b, jint off) {
                return (b[off] != 0);
            }

            static jshort getShort(jbyte* b, jint off) {
                return (jshort) (((b[off + 1] & 0xFF) << 0) + ((b[off + 0]) << 8));
            }

            static jint getInt(jbyte* b, jint off) {
                return ((b[off + 3] & (jint) 0xFF) << 0) +
                       ((b[off + 2] & (jint) 0xFF) << 8) +
                       ((b[off + 1] & (jint) 0xFF) << 16) +
                       (b[off + 0] << 24);
            }

            static jfloat getFloat(jbyte* b, jint off) {
                jint i = ((b[off + 3] & (jint) 0xFF) << 0) +
                        ((b[off + 2] & (jint) 0xFF) << 8) +
                        ((b[off + 1] & (jint) 0xFF) << 16) +
                        (b[off + 0] << 24);
                return *(reinterpret_cast<jfloat*> (&i));
            }

            static jlong getLong(jbyte *b, jint off) {
                    return ((b[off + 7] & (jlong) 0xFFL) << 0) +
                           ((b[off + 6] & (jlong) 0xFFL) << 8) +
                           ((b[off + 5] & (jlong) 0xFFL) << 16) +
                           ((b[off + 4] & (jlong) 0xFFL) << 24) +
                           ((b[off + 3] & (jlong) 0xFFL) << 32) +
                           ((b[off + 2] & (jlong) 0xFFL) << 40) +
                           ((b[off + 1] & (jlong) 0xFFL) << 48) +
                           (((jlong) b[off + 0]) << 56);
            }

            static jdouble getDouble (jbyte *b, jint off) {
                jlong j = ((b[off + 7] & (jlong)0xFFL) << 0) +
                        ((b[off + 6] & (jlong)0xFFL) << 8) +
                        ((b[off + 5] & (jlong)0xFFL) << 16) +
                        ((b[off + 4] & (jlong)0xFFL) << 24) +
                        ((b[off + 3] & (jlong)0xFFL) << 32) +
                        ((b[off + 2] & (jlong)0xFFL) << 40) +
                        ((b[off + 1] & (jlong)0xFFL) << 48) +
                        (((jlong) b[off + 0]) << 56);
                return *(reinterpret_cast<jdouble*> (&j));
            }
        };
    }
}

#endif // JBITS_H
