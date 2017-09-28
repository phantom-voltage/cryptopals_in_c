#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/aes.h>

#include "../header/conversion.h"
#include "../header/hamming.h"


/*

############
CHALLENGE 8:
############

Detect AES in ECB mode

In this file are a bunch of hex-encoded ciphertexts.

One of them has been encrypted with ECB.

Detect it.

Remember that the problem with ECB is that it is stateless
and deterministic; the same 16 byte plaintext block will always 
produce the same 16 byte ciphertext.                            

*/

/*

#########
SOLUTION:
#########

If the same 16 byte planetext block produces the same cipher text,
then this means you should probably look for the same 16 byte chunks.

I also figured I could use the the hamming code from Challenge 6.

Same 16 byte block, means the hamming distance should be 0.

This may be a bit slower, but can eliminate other entries that
just so *HAPPEN* to have the same 16 bytes in a block.


*/


int main(int argc, char** argv)
{


    /* File stuff */
    FILE *fp;
    char* line = NULL;
    size_t n = 0;
    int count = 0;

    fp = fopen("8.txt", "r");

    if(fp == NULL)
    {
        printf("There was an error opening the file.\n");
        return EXIT_FAILURE;

    }


    unsigned char* temp = NULL;
    char* enc = NULL;

    size_t len = 0;

    int lowestIndex = 0;
    float lowestWeight = 200;
    float dist = 0;


    /* Read file to EOF */
    /* This code is a bit generalized in case you'd like to look at
       strings of varying length.                                   */

    while( getline(&line, &n, fp) != -1)
    {

        count++;

        /* Reallocate memory iff the size of the current line is longer
           than previously allocated                                    */

        if(len< n/2)
        {
            len = n/2;

            if(temp)
            {
                free(temp);
            }

            if(enc)
            {
                free(enc);
            }

            /* Allocate memory for the longer line, and the longer encoded string */
            enc = (char*)malloc(sizeof(char)*n);
            temp = (unsigned char*)malloc(sizeof(unsigned char)*len);

        }
        
        /* Convert hex to binary */
        htob(line, temp, n);
        
        /* Get the avg. hamming distance */
        dist = get_hamming(temp, len, 16);
    
        /* Save the best looking one */
        if(dist < lowestWeight)
        {
            strncpy(enc, line, n);
            lowestIndex = count;
            lowestWeight = dist;
        }


    }
    

    printf("Line %d has the lowest avg. hamming distance --> %f\n\n", lowestIndex, lowestWeight);
    printf("%s\n", enc);

    free(enc);
    free(line);
    free(temp);

    fclose(fp);
}
