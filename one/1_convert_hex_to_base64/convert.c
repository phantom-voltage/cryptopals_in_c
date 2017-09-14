#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../header/conversion.h"

/* The majority of the work here was done in the conversion.h header */

int main(int argc, char** argv)
{

    if(argc < 2)
    {

        printf("Usage: convert [hex encoded string]\n");
        return EXIT_FAILURE;

    }


    char* hex = argv[1]; 
    unsigned char* bytes;


    int len = strlen(hex);

    bytes = (unsigned char*)malloc(sizeof(unsigned char)*len/2);

    char* radix64 = (char*)malloc(sizeof(char)*3/2*len);

    /* Convert hex to binary */
    htob(hex, bytes, len);

    /* Convert binary to radix64 */
    btor64(bytes, radix64, len/2);

    
    printf("%s\n", radix64);

    free(bytes);
    free(radix64);
    

}
