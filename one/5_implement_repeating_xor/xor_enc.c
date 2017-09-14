#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#include "../header/xor.h"
#include "../header/conversion.h"


/* The work for this challenge primarily consists of
   xor_string in xor.h                               */

int main(int argc, char **argv) {

    FILE* fp;

    /* Read in plain text */
    fp = fopen("5.txt", "r");

    if(fp == NULL)
    {
        printf("There was an error opening the file.\n");
        return EXIT_FAILURE;

    }

    char* line = NULL;
    size_t n = 0;
    
    getline(&line, &n, fp);
    int len = strlen(line);
    
    printf("PLAINTEXT:\n%s\n", line);

    /* KEY is "ICE" */
    unsigned char key[3]; 
    key[0] = 73;
    key[1] = 67;
    key[2] = 69;

   
    int keyLen = 3;

    /* XOR the string with a repeating key */
    xor_string(line, len, key, keyLen);
    
    printf("\nCIPHER TEXT:\n0x");

    /* Print the CIPHER TEXT in hex */
    print_hex(line, len-1);

   
    free(line);

    return EXIT_SUCCESS;

} 


