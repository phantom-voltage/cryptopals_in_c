#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <openssl/aes.h>

#include "pad.h"
#include "aes_cbc.h"
#include "conversion.h"



void print_dec(char* title, uint8_t* data, size_t n);

/*****************************************************************
 CBC mode is a block cipher mode that allows us to encrypt 
irregularly-sized messages, despite the fact that a block cipher
natively only transforms individual blocks.

In CBC mode, each ciphertext block is added to the next plaintext
block before the next call to the cipher core.

The first plaintext block, which has no associated previous 
ciphertext block, is added to a "fake 0th ciphertext block" 
called the initialization vector, or IV.

Implement CBC mode by hand by taking the ECB function you wrote 
earlier, making it encrypt instead of decrypt (verify this by 
decrypting whatever you encrypt to test), and using your XOR 
function from the previous exercise to combine them.

The file here is intelligible (somewhat) when CBC decrypted 
against "YELLOW SUBMARINE" with an IV of all 
ASCII 0 (\x00\x00\x00 &c) 


#########
SOLUTION:
#########

Majority of the work is located in the header file: aes_cbc.h

******************************************************************/


/* Blocksize in bytes */
const size_t BLOCKSIZE = 16;

/* "YELLOW SUBMARINE" in hex */
const static uint8_t aesKey[] ={0x59, 0x45, 0x4c, 0x4c, 0x4f, 0x57, 0x20, 0x53, 0x55, 0x42, 0x4d, 0x41, 0x52, 0x49, 0x4e, 0x45};

 

int main(int argc, char** argv)
{


    FILE *fp;
    
    fp = fopen("10.txt", "r");

    if(!fp)
    {
        printf("There was an error opening the file\n");
        return EXIT_FAILURE;
    }

    
    /* Count char length */
    int count = 0;

    while(fgetc(fp) != EOF)
    {
        count++;
    }


    /* Allocate memory for the input text */
    char* input = (char*)calloc(count, sizeof(char));

    /* Rewind pointer to read in by line */
    rewind(fp);

    char* line = NULL;
    size_t n = 0;

    ssize_t c;
    
    int l = 0;

    /* Read in the line, and concatenate it to a single string */
    while( (c = getline(&line, &n, fp)) != -1)
    {
        strncat(input, line, c-1);
    
        l += c-1;

    }
    
    fclose(fp);


    /* Used to store return value */
    int rflag;

    /* Allocate memory to store the data in bytes */
    size_t b = l*3/4;
    uint8_t* bytes = (uint8_t*)malloc(sizeof(uint8_t)*b);

    /* Convert radix64 to bytes */
    r64tob(input, bytes, l);

    /* Take a look at these BYTES! */
    print_dec("BYTES:", bytes, b);


    
    /* Allocate memory for plaintext */
    uint8_t* plainText = (uint8_t*)calloc(b+1,sizeof(uint8_t));

    /* Create init vector, 0 it out */
    uint8_t iv[BLOCKSIZE];
    memset(iv, 0x00, BLOCKSIZE);
    
    /* Set the key, not sure 100% difference between *_set_encrypte and *_set_decrypt */
    AES_KEY key;

    AES_set_decrypt_key(aesKey, BLOCKSIZE*8, &key);

    /* If we could convert the data, put a null terminator at the end */
    if(aes_cbc(plainText, bytes, b, BLOCKSIZE, iv, key, AES_DECRYPT))
    {
        plainText[b] = '\0';
        printf("\n%s\n", plainText);
        rflag = EXIT_SUCCESS;
    }

    else
    {
        printf("Error decrypting cipher text!\n");
        rflag = EXIT_FAILURE;

    }

    free(plainText);
    free(bytes);
    free(input);

    return rflag;
    

}
    

/* Prints out the values in decimals, used for debugging */
void print_dec(char* title, uint8_t* data, size_t n)
{

    printf("\n%s\n", title);
    
    for(int i = 0; i < n; i++)
    {
        printf("%03d ", data[i]);

    }
    printf("\n");

}

