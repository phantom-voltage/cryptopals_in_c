#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include "pad.h"
#include "aes_cbc.h"
#include "pcg_basic.h"

static const size_t BLOCKSIZE = 16;

void print_dec(char* title, uint8_t* data, size_t n);

void gen_aes_key(uint8_t* key, int keySize);

int main(int argc, char** argv)
{



    if(argc < 2)
    {

        printf("Usage: main [input plaintext]\n");
        return EXIT_FAILURE;

    }
    

    char* input = argv[1];


    int rounds = 1;
    pcg32_random_t rng;
    

    pcg32_srandom_r(&rng, time(NULL) ^ (intptr_t)&printf, (intptr_t)&rounds);

    


    
    int fPad = 5+pcg32_boundedrand_r(&rng, 6);
    int bPad = 5+pcg32_boundedrand_r(&rng, 6);



    
    
    /* Generate a random key */
    uint8_t key[BLOCKSIZE];

    gen_aes_key(key, BLOCKSIZE);

    print_dec("Key:", key, BLOCKSIZE);


    /* Double pad, i.e. pad the front and back of the string 
       with between 5-10 bytes                              */
    char* padded;
    double_pad(&padded, input, strlen(input), fPad, bPad);
    print_dec("Padded:", padded, strlen(padded));


    /* Now pad to the appropriate blocksize */
    int p = 0;
    unsigned char* final;
    
    if( p = get_pad(padded, BLOCKSIZE))
    {
        pad(&final, padded, strlen(padded), p);
    }
    else
    {
        final = (char*)malloc(sizeof(char)*strlen(padded));
        strncpy(final, padded, strlen(padded));
    }
    free(padded);


    print_dec("Final padded:", final, strlen(final));
    free(final);

}

void gen_aes_key(uint8_t* key, int keySize)
{

    pcg32_random_t rng;
    uint32_t temp;

    pcg32_srandom_r(&rng, time(NULL) ^ (intptr_t)&printf, (intptr_t)&temp);


    for(int i = 0; i < keySize; i+=4)
    {
        temp = pcg32_random_r(&rng);

       // *(uint32_t *)&key[i] = temp;
        *(uint32_t *)(key+i) = temp;

    }


}

void print_dec(char* title, uint8_t* data, size_t n)
{

    printf("\n%s\n", title);

    for(int i = 0; i < n; i++)
    {
        printf("%03d ", data[i]);

    }
    printf("\n");

}
