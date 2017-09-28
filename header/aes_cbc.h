#ifndef AES_CBC_H_INCLUDED
#define AES_CBC_H_INCLUDED 1

#include <openssl/aes.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "xor.h"

/* Encrypts or decrypts string src, of length l. 
   If encrypting, src is plain text
   If decrypting, src is cipher text
   iv should be the same length as blocksize
   String length l
   Block size n
   1 || 0 :: encrypt || decrypt
*/
int aes_cbc(uint8_t* dest, uint8_t* src, size_t l, size_t n, uint8_t* iv, AES_KEY key, int encrypt);

#endif
