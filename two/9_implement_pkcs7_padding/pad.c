#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "../header/conversion.h"

/************************************************************

########
PROBLEM:
########
Implement PKCS#7 padding

A block cipher transforms a fixed-sized block (usually 8 or 
16 bytes) of plaintext into ciphertext. But we almost never 
want to transform a single block; we encrypt irregularly-sized 
messages.

One way we account for irregularly-sized messages is by 
padding, creating a plaintext that is an even multiple of 
the blocksize. The most popular padding scheme is called 
PKCS#7.

So: pad any block to a specific block length, by appending 
the number of bytes of padding to the end of the block. 
For instance,

"YELLOW SUBMARINE"

... padded to 20 bytes would be:

"YELLOW SUBMARINE\x04\x04\x04\x04"

#########
SOLUTION:
#########

I'm assuming that \x04\x04\x04\x04 is the hex representation
of the string in binary, otherwise that would be padded to 
more than 20 bytes.


The function for this has been generalized in header/pad.h

*************************************************************/

int main(int argc, char** argv)
{

    if( argc < 3)
    {
        printf("Usage: pad [input string] [blocksize]\n");
        return EXIT_FAILURE;

    }


    char* input = argv[1];
    long blockSize = strtol(argv[2], NULL, 10);

    if(blockSize > 255)
    {
        printf("The blocksize for this exercise is bigger than expected\n");
        return EXIT_FAILURE;

    }

    int padding = 0;
    int len = strlen(input);

    printf("%s is the string\n", input);
    printf("%d is the length\n", len);

    if(len % blockSize != 0)
    {
        padding = blockSize - (len  % blockSize);

    }

    printf("%d is the padding\n", padding);

    unsigned char* paddedInput = (unsigned char*)calloc(sizeof(unsigned char)*len+padding+1, len+padding+1);

    strncpy(paddedInput, input, len);


    int i;
    for(i = 0; i < padding; i++)
    {

        *(paddedInput+len+i) = padding;

    }

    *(paddedInput+len+i+1) = '\0';

    printf("\n");
    for(i =0; i <len+padding; i++)
    {
        printf("%02d ", paddedInput[i]);

    }

    printf("\n0x");

    print_hex(paddedInput, len+padding);

    free(paddedInput);
    

}
