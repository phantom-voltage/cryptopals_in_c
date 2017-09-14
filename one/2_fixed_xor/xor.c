#include <stdio.h>
#include <stdlib.h>
#include <string.h>





int main(int argc, char **argv) {

    if(argc < 3)
    {
        printf("Usage: xor [hex encoded string1] [hex encoded string2]\n\n");
        return EXIT_FAILURE;

    }
    char *hex1 = argv[1];
    char *hex2 = argv[2];
    char *pos1 = hex1;
    char *pos2 = hex2;


    if(strlen(hex1) != strlen(hex2))
    {
        return EXIT_FAILURE;
    }
    
    unsigned char* byte1 = (unsigned char*) malloc( sizeof(unsigned char) * strlen(hex1)/2 +1);
    unsigned char* byte2 = (unsigned char*) malloc( sizeof(unsigned char) * strlen(hex1)/2 +1);
    unsigned char* xor = (unsigned char*) malloc( sizeof(unsigned char) * strlen(hex1)/2 +1);
    char* byte = (char*)malloc(sizeof(char) * strlen(hex1));

    int numBytes = strlen(hex1)/2;

    size_t count = 0;
    

    for(count = 0; count < numBytes; count++) {
        sscanf(pos1, "%2hhx", &byte1[count]);
        sscanf(pos2, "%2hhx", &byte2[count]);

        xor[count] = byte1[count]^byte2[count];

        pos1 += 2;
        pos2 += 2;
    }



    printf("0x");
    for(count = 0; count < numBytes; count++)
        printf("%02x", xor[count]);
    printf("\n");


    return EXIT_SUCCESS;
}

