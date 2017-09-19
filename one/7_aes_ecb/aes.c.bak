#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "../header/conversion.h"
 
#include <openssl/aes.h>

/* AES key for decryption */

/* YELLOW SUBMARINE in hex */
const static unsigned char aes_key[]={0x59, 0x45, 0x4c, 0x4c, 0x4f, 0x57, 0x20, 0x53, 0x55, 0x42, 0x4d, 0x41, 0x52, 0x49, 0x4e, 0x45};
 
int main(int argc, char** argv)
{

    FILE* fp;

    char* line = NULL;
    char* input = NULL;
    size_t n = 0;

    fp = fopen("7.txt", "r");

    if(fp == NULL)
    {
        printf("There was an error opening the file.\n");
        return EXIT_FAILURE;
    }


    /* Get the length of string to decode */
    int count = 0;

    while(fgetc(fp) != EOF)
    {
        count++;

    }
    
    input = (char*)calloc(count, sizeof(char*)*count);

    rewind(fp);

    /* Concatenate lines from the file  until EOF */
    while(getline(&line, &n, fp) != -1)
    {
        strncat(input, line, strlen(line)-1);
    }

    free(line);
    fclose(fp);

    /* Create an array to store the bytes, which will be a fraction of the size */
    size_t numBytes = strlen(input)*3/4;
    unsigned char* aes_input = (unsigned char*)malloc(sizeof(unsigned char)*numBytes);
    
    /* Do the conversion */
    r64tob(input, aes_input, strlen(input));
	
	/* Init the vector */
	unsigned char iv[AES_BLOCK_SIZE];
	memset(iv, 0x00, AES_BLOCK_SIZE);
	
    char* dec_out = (char*)malloc(sizeof(char)*numBytes);
    unsigned char* temp = (unsigned char*)malloc(sizeof(unsigned char)*16);

    memset(dec_out, 0x00, numBytes);
	
	/* AES-128 bit CBC Encryption */
	AES_KEY enc_key, dec_key;

	/* AES-128 bit CBC Decryption */
	memset(iv, 0x00, AES_BLOCK_SIZE); // don't forget to set iv vector again, else you can't decrypt data properly
	AES_set_decrypt_key(aes_key, 16*8, &dec_key); // Size of key is in bits

    for(int i = 0; i < (numBytes/16); i++)
    {
        AES_cbc_encrypt(aes_input+i*16, temp, 16, &dec_key, iv, AES_DECRYPT);
        strncat(dec_out, temp, 16);
	    memset(iv, 0x00, AES_BLOCK_SIZE); // don't forget to set iv vector again, else you can't decrypt data properly
        
    }

    printf("%s", dec_out);
	

    free(temp);
    free(input);
    free(aes_input);
    free(dec_out);

	return 0;
}
 
void print_data(const char *tittle, const void* data, int len)
{
	printf("%s : ",tittle);
	const unsigned char * p = (const unsigned char*)data;
	int i = 0;
	
	for (; i<len; ++i)
		printf("%c ", *p++);
	
	printf("\n");
}
