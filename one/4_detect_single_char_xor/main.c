#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "xor.h"

int main(int argc, char **argv) {

   
    

    FILE *fp = fopen("4.txt", "r");


    
    /* Get the number of lines to allocate an array of encoded messages */
    char c;
    int lineCount = 0;

    while(!feof(fp))
    {
        c = fgetc(fp);
        if(c == '\n' || c == EOF)
        {
            lineCount++;
        }
    }
    rewind(fp);


    unsigned char** encodedBytes = (unsigned char**)malloc(sizeof(unsigned char*)*lineCount);
    int* scores = (int*)malloc(sizeof(int)*lineCount);
    int* index = (int*)malloc(sizeof(int)*lineCount);

    size_t lineSize = 0;
    char* tempBuf;

    int charCount;



    int i, j, k;
    int tempScore;
    int numBytes;
    size_t count;
    char* pos;
    char* xorTemp;

    unsigned char key[1];
    key[0] = 0;

    for(i = 0; i < lineCount; i++)
    {
        
        charCount  = getline(&tempBuf, &lineSize, fp);
        numBytes = charCount/2;
        
        encodedBytes[i] = (unsigned char*)malloc(sizeof(unsigned char)*numBytes);
        xorTemp = (unsigned char*)malloc(sizeof(unsigned char)*numBytes);

        pos = tempBuf;

        for(count = 0; count<numBytes; count++)
        {
            sscanf(pos, "%2hhx", &encodedBytes[i][count]);
            pos += 2;
            
            xorTemp[count] = encodedBytes[i][count];
        }


        for(j = 0; j < 256; j++)
        {
            key[0] = j;
            memcpy(xorTemp, encodedBytes[i], numBytes);
            
            xor_string(xorTemp, numBytes, key, 1);
            tempScore = xor_score(xorTemp, numBytes);
            
            if(tempScore > scores[i])
            {
                scores[i] = tempScore;
                index[i] = j;
            }
       
        }

        free(xorTemp);

    }
    

    int highestScore = 0;
    int bestGuess = 0;

    for(i = 0; i < lineCount; i++)
    {

        if(scores[i] > highestScore)
        {
            highestScore = scores[i];
            bestGuess = i;
        }
        

    }
    
    key[0] = index[bestGuess];
    printf("%s %d %d %d\n", encodedBytes[bestGuess], bestGuess, index[bestGuess], scores[bestGuess]);
    xor_string(encodedBytes[bestGuess], numBytes, key, 1);
    printf("%s\n", encodedBytes[bestGuess]);


    fclose(fp);
    free(tempBuf);
    free(scores);
    free(index);

    for(i = 0; i < lineCount; i++)
    {
        free(encodedBytes[i]);
            
    }

    free(encodedBytes);
    
    
    return EXIT_SUCCESS;
} 


