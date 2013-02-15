#ifndef JBITS_H
#define JBITS_H

#include "Object.h"

namespace jcpp{
    namespace util{
        class JBits {
        public:

            static void putBoolean(jbyte b[], int off, bool val) {
                b[off] = (jbyte) (val ? 1 : 0);
            }

            static void putChar(jbyte b[], int off, jushort val) {
                b[off + 1] = (jubyte) (val >> 0);
                b[off + 0] = (jubyte) (val >> 8);
            }

            static void putShort(jbyte b[], int off, jshort val) {
                b[off + 1] = (jubyte) (val >> 0);
                b[off + 0] = (jubyte) (val >> 8);
            }

            static void putInt(jbyte b[], int off, jint val) {
                b[off + 3] = (jubyte) (val >> 0);
                b[off + 2] = (jubyte) (val >> 8);
                b[off + 1] = (jubyte) (val >> 16);
                b[off + 0] = (jubyte) (val >> 24);
            }

            static void putFloat(jbyte b[], int off, float val) {
                jint* i = reinterpret_cast<jint*>(&val);
                b[off + 3] = (jubyte) (*i >> 0);
                b[off + 2] = (jubyte) (*i >> 8);
                b[off + 1] = (jubyte) (*i >> 16);
                b[off + 0] = (jubyte) (*i >> 24);
            }

            static void putLong(jbyte b[], int off, jlong val) {
                b[off + 7] = (jubyte) (val >> 0);
                b[off + 6] = (jubyte) (val >> 8);
                b[off + 5] = (jubyte) (val >> 16);
                b[off + 4] = (jubyte) (val >> 24);
                b[off + 3] = (jubyte) (val >> 32);
                b[off + 2] = (jubyte) (val >> 40);
                b[off + 1] = (jubyte) (val >> 48);
                b[off + 0] = (jubyte) (val >> 56);
            }

            static void putDouble(jbyte b[], int off, double val) {
                jlong* j = reinterpret_cast<jlong*>(&val);
                b[off + 7] = (jubyte) (*j >> 0);
                b[off + 6] = (jubyte) (*j >> 8);
                b[off + 5] = (jubyte) (*j >> 16);
                b[off + 4] = (jubyte) (*j >> 24);
                b[off + 3] = (jubyte) (*j >> 32);
                b[off + 2] = (jubyte) (*j >> 40);
                b[off + 1] = (jubyte) (*j >> 48);
                b[off + 0] = (jubyte) (*j >> 56);
            }

            static bool getBool(jbyte *b, int off) {
                return (b[off] != 0);
            }

            static jshort getShort(jbyte* b, int off) {
                return (jshort) (((b[off + 1] & 0xFF) << 0) +
                                ((b[off + 0]) << 8));
            }

            static jint getInt(jbyte* b, int off) {
                return ((b[off + 3] & (jint) 0xFF) << 0) +
                       ((b[off + 2] & (jint) 0xFF) << 8) +
                       ((b[off + 1] & (jint) 0xFF) << 16) +
                       (((jint) b[off + 0]) << 24);
            }

            static float getFloat(jbyte* b, int off) {
                jint i = ((b[off + 3] & (jint) 0xFF) << 0) +
                        ((b[off + 2] & (jint) 0xFF) << 8) +
                        ((b[off + 1] & (jint) 0xFF) << 16) +
                        (((jint) b[off + 0]) << 24);
                return *(reinterpret_cast<float*> (&i));
            }

            static jlong getLong(jbyte *b, int off) {
                    return ((b[off + 7] & (jlong) 0xFF) << 0) +
                           ((b[off + 6] & (jlong) 0xFF) << 8) +
                           ((b[off + 5] & (jlong) 0xFF) << 16) +
                           ((b[off + 4] & (jlong) 0xFF) << 24) +
                           ((b[off + 3] & (jlong) 0xFF) << 32) +
                           ((b[off + 2] & (jlong) 0xFF) << 40) +
                           ((b[off + 1] & (jlong) 0xFF) << 48) +
                           (((jlong) b[off + 0]) << 56);
            }

            static double getDouble (jbyte *b, int off) {
                jlong j = ((b[off + 7] & (jlong) 0xFF) << 0) +
                        ((b[off + 6] & (jlong) 0xFF) << 8) +
                        ((b[off + 5] & (jlong) 0xFF) << 16) +
                        ((b[off + 4] & (jlong) 0xFF) << 24) +
                        ((b[off + 3] & (jlong) 0xFF) << 32) +
                        ((b[off + 2] & (jlong) 0xFF) << 40) +
                        ((b[off + 1] & (jlong) 0xFF) << 48) +
                        (((jlong) b[off + 0]) << 56);
                return *(reinterpret_cast<double*> (&j));
            }
        };
    }
}

#endif // JBITS_H
