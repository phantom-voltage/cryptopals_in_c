#include "aes_cbc.h"

/* Encrypts or decrypts string src, of length l. 
   If encrypting, src is plain text
   If decrypting, src is cipher text
   iv should be the same length as blocksize
   String length l
   Block size n
   1 || 0 :: encrypt || decrypt
*/
int aes_cbc(uint8_t* dest, uint8_t* src, size_t l, size_t n, uint8_t* iv, AES_KEY key, int encrypt)
{

    /* Check if input is padded to the blocksize */
    if(l%n)
    {
        return 0;
    }

    /* Create temporary block to write ECB results to */
    uint8_t* tempBlock = (uint8_t*)malloc(sizeof(uint8_t)*n);

    /* Repeat for entire length of src */
    for(int i = 0; i < l/n; i++)
    {
        
        /* Apply XOR to plaintext */
        if(encrypt)
        {
            xor_string(src+i*n, n, iv, n);
        }

        /* Encrypt or Decrypt block */
        AES_ecb_encrypt(src+i*n, tempBlock, &key, encrypt);
        
        /* Copy result to destination */
        memcpy(dest+i*n, tempBlock, n);

        /* If encrypting, iv takes on the cipher text value */
        if(encrypt)
        {
            memcpy(iv, tempBlock, n);
        }
        
        /* If decrypting, xor string with previous cipher text,
           and assign to iv after */
        else
        {
            xor_string(dest+i*n, n, iv, n);
            memcpy(iv, src+i*n, n);
        }
    }

    free(tempBlock);
    return 1;
}
