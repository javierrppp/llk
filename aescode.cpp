#include "aescode.h"

AesCode::AesCode()
{

}

int AesCode::aes_encrypt(unsigned char *in, unsigned char *key ,unsigned char* ivec, unsigned char *out)
{
    if(!in || !key || !out) return 0;
    AES_KEY aes;
    if(AES_set_encrypt_key(key, 256, &aes) < 0)
    {
        return 0;
    }

/**
*   pkcs5padding
**/
    int dateSize = strlen( (char*)in ) + 1;
    int nLen = strlen( (char*)in );
    int nBei = nLen / AES_BLOCK_SIZE + 1;
    int nTotal = nBei * AES_BLOCK_SIZE;
    char *enc_s = (char*)malloc(nTotal);
    int nNumber;
    if (nLen % 16 > 0)
     nNumber = nTotal - nLen;
    else
     nNumber = 16;
    memset(enc_s, nNumber, nTotal);
    memcpy(enc_s, in, nLen);

    AES_cbc_encrypt((unsigned char*)enc_s, out, nTotal, &aes, ivec, AES_ENCRYPT);

    return 1;
}
