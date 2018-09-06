#ifndef AESCODE_H
#define AESCODE_H
#include <QString>


class AesCode
{
public:
    AesCode();
    static QString enCode( QString key, QString ivec, QString code );
    static int aes_encrypt(unsigned char* in,unsigned char* key,unsigned char* ivec,unsigned char* out);
};

#endif // AESCODE_H
