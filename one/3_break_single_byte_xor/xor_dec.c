#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#include "../header/xor.h"


int main(int argc, char **argv) {

    
    FILE* fp;
    char* line = NULL;
    size_t n = 0;

    fp = fopen("3.txt", "r");

    if(fp == NULL)
    {
        printf("There was an error opening the file.\n");
        return EXIT_FAILURE;

    }

    getline(&line, &n, fp);

    char *pos = line;


    unsigned char* byte = (unsigned char*) malloc( sizeof(unsigned char) * strlen(line)/2 +1);
    unsigned char* xor = (unsigned char*) malloc( sizeof(unsigned char) * strlen(line)/2 +1);

    int numBytes = strlen(line)/2;

    size_t count = 0;
    
    unsigned char c = 0;
    int i = 0;
    int j = 0;
    char l;

    int score[256];

    for(i = 0; i < 256; i++)
    {
        score[i] = 0;
        pos = line;

        for(count = 0; count < numBytes; count++) {
            sscanf(pos, "%2hhx", &byte[count]);

            xor[count] = byte[count] ^ (unsigned char) i ;
            
            l = tolower(xor[count]);

            switch(l)
            {
                case('e'):
                    score[i] += 13;
                    break;

                case('t'):
                    score[i] += 12;
                    break;

                case('a'):
                    score[i] += 11;
                    break;

                case('o'):
                    score[i] += 10;
                    break;

                case('i'):
                    score[i] += 9;
                    break;

                case('n'):
                    score[i] += 8;
                    break;

                case(' '):
                    score[i] += 7;
                    break;

                case('s'):
                    score[i] += 6;
                    break;

                case('h'):
                    score[i] += 5;
                    break;

                case('r'):
                    score[i] += 4;
                    break;

                case('d'):
                    score[i] += 3;
                    break;

                case('l'):
                    score[i] += 2;
                    break;

                case('u'):
                    score[i] += 1;
                    break;
                default:
                    break;

            }

            pos += 2;
        }
        
    }


    int highest_score = 0;
    int highest = 0;
    for(i = 0; i < 256; i++)
    {
        if (score[i] > highest_score)
        {
            highest = i;
            highest_score = score[i];
        }

    }

    printf("the highest is %d\n", highest);

    for(i = 0; i < numBytes; i++)
    {
        printf("%c", byte[i]^highest);

    }
    printf("\n");

    free(byte);
    free(xor);
    return EXIT_SUCCESS;
}

