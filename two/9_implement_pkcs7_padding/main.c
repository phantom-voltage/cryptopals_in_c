#include <stdio.h>
#include <stdlib.h>

#include "../header/pad.h"

int main(int argc, char** argv)
{


    if(argc < 3)
    {
        printf("Useage: pad [input string] [blocksize]\n");
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

    padding = get_pad(input, blockSize);

    printf("\npadding is %d\n", padding);

    unsigned char* paddedInput;
        
    pad(&paddedInput, input, len, padding);


    printf("%s\n", paddedInput);
    printf("0x");
    print_hex(paddedInput, len+padding);


    free(paddedInput);









}
