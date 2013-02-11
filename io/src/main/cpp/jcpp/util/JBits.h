#ifndef JBITS_H
#define JBITS_H

#include <QtGlobal>

namespace jcpp{
    namespace util{
        class JBits {
        public:

            static void putBoolean(qint8 b[], int off, bool val) {
                b[off] = (qint8) (val ? 1 : 0);
            }

            static void putChar(qint8 b[], int off, quint16 val) {
                b[off + 1] = (quint8) (val >> 0);
                b[off + 0] = (quint8) (val >> 8);
            }

            static void putShort(qint8 b[], int off, qint16 val) {
                b[off + 1] = (quint8) (val >> 0);
                b[off + 0] = (quint8) (val >> 8);
            }

            static void putInt(qint8 b[], int off, qint32 val) {
                b[off + 3] = (quint8) (val >> 0);
                b[off + 2] = (quint8) (val >> 8);
                b[off + 1] = (quint8) (val >> 16);
                b[off + 0] = (quint8) (val >> 24);
            }

            static void putFloat(qint8 b[], int off, float val) {
                qint32* i = reinterpret_cast<qint32*>(&val);
                b[off + 3] = (quint8) (*i >> 0);
                b[off + 2] = (quint8) (*i >> 8);
                b[off + 1] = (quint8) (*i >> 16);
                b[off + 0] = (quint8) (*i >> 24);
            }

            static void putLong(qint8 b[], int off, qint64 val) {
                b[off + 7] = (quint8) (val >> 0);
                b[off + 6] = (quint8) (val >> 8);
                b[off + 5] = (quint8) (val >> 16);
                b[off + 4] = (quint8) (val >> 24);
                b[off + 3] = (quint8) (val >> 32);
                b[off + 2] = (quint8) (val >> 40);
                b[off + 1] = (quint8) (val >> 48);
                b[off + 0] = (quint8) (val >> 56);
            }

            static void putDouble(qint8 b[], int off, double val) {
                qint64* j = reinterpret_cast<qint64*>(&val);
                b[off + 7] = (quint8) (*j >> 0);
                b[off + 6] = (quint8) (*j >> 8);
                b[off + 5] = (quint8) (*j >> 16);
                b[off + 4] = (quint8) (*j >> 24);
                b[off + 3] = (quint8) (*j >> 32);
                b[off + 2] = (quint8) (*j >> 40);
                b[off + 1] = (quint8) (*j >> 48);
                b[off + 0] = (quint8) (*j >> 56);
            }

            static bool getBool(qint8 *b, int off) {
                return (b[off] != 0);
            }

            static qint16 getShort(qint8* b, int off) {
                return (qint16) (((b[off + 1] & 0xFF) << 0) +
                                ((b[off + 0]) << 8));
            }

            static qint32 getInt(qint8* b, int off) {
                return ((b[off + 3] & (qint32) 0xFF) << 0) +
                       ((b[off + 2] & (qint32) 0xFF) << 8) +
                       ((b[off + 1] & (qint32) 0xFF) << 16) +
                       (((qint32) b[off + 0]) << 24);
            }

            static float getFloat(qint8* b, int off) {
                qint32 i = ((b[off + 3] & (qint32) 0xFF) << 0) +
                        ((b[off + 2] & (qint32) 0xFF) << 8) +
                        ((b[off + 1] & (qint32) 0xFF) << 16) +
                        (((qint32) b[off + 0]) << 24);
                return *(reinterpret_cast<float*> (&i));
            }

            static qint64 getLong(qint8 *b, int off) {
                    return ((b[off + 7] & (qint64) 0xFF) << 0) +
                           ((b[off + 6] & (qint64) 0xFF) << 8) +
                           ((b[off + 5] & (qint64) 0xFF) << 16) +
                           ((b[off + 4] & (qint64) 0xFF) << 24) +
                           ((b[off + 3] & (qint64) 0xFF) << 32) +
                           ((b[off + 2] & (qint64) 0xFF) << 40) +
                           ((b[off + 1] & (qint64) 0xFF) << 48) +
                           (((qint64) b[off + 0]) << 56);
            }

            static double getDouble (qint8 *b, int off) {
                qint64 j = ((b[off + 7] & (qint64) 0xFF) << 0) +
                        ((b[off + 6] & (qint64) 0xFF) << 8) +
                        ((b[off + 5] & (qint64) 0xFF) << 16) +
                        ((b[off + 4] & (qint64) 0xFF) << 24) +
                        ((b[off + 3] & (qint64) 0xFF) << 32) +
                        ((b[off + 2] & (qint64) 0xFF) << 40) +
                        ((b[off + 1] & (qint64) 0xFF) << 48) +
                        (((qint64) b[off + 0]) << 56);
                return *(reinterpret_cast<double*> (&j));
            }
        };
    }
}

#endif // JBITS_H
