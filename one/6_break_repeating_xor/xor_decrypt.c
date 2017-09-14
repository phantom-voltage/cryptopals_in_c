#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#include "../header/conversion.h"
#include "../header/hamming.h"
#include "../header/xor.h"

/* New functions written for this challenge in hamming.h */

/* Set the maximum keysize to guess */
int KEYSIZE_MAX = 47;

int main(int argc, char** argv)
{

    FILE *fp;

    char* line = NULL;
    size_t n = 0;
    ssize_t read = 0;

    fp = fopen("6.txt", "r");

    if(fp == NULL)
    {
        printf("There was an error with opening the file.\n");
        return EXIT_FAILURE;
    }


    int count = 0;

    while(fgetc(fp) != EOF )
    {

        count++;

    }

    
    
    /* The functions used to check do not account for keysizes larger
       than the encoded text, so I exit to avoid undefined behavior  */ 
    if(count < KEYSIZE_MAX)
    {
        
        printf("Encoded input is smaller than max defined keysize (%d)\n", KEYSIZE_MAX);
        fclose(fp);
        return EXIT_FAILURE;

    }

    rewind(fp);

    char* input = (char*)calloc(count, sizeof(char)*count);

    while( (read = getline(&line, &n, fp)) != -1 )
    {
        strncat(input, line, strlen(line)-1);
    }

    fclose(fp);

    printf("Successfully read in %d characters.\n", strlen(input));
    

    /* Convert the text to binary bytes */
    size_t numBytes = strlen(input)*3/4;
    unsigned char* bytes = (unsigned char*)malloc(sizeof(unsigned char)*numBytes);

    r64tob(input, bytes, strlen(input));

    int k; 
    printf("Guessing keysizes...\n\n");

    float weights[KEYSIZE_MAX];

    /* Get average hamming distance over all desired keysizes over entire input */
    for(k = 2; k < KEYSIZE_MAX; k++)
    {
        weights[k] = 0;
        weights[k] = get_hamming(bytes, strlen(input)*3/4, k);
        
    }


    /* Grab the top 5 best scores */
    int i = 0;
    int j = 0;
    int top_index[5];
    float top_score[5];

    int smallest = 100000;
    int index = 0;

    for(i = 0; i < 5; i ++)
    {
        top_index[i] = 0;
        top_score[i] = 100;
    
    }

    /* Create a top 5 array */
    for( i = 2; i < KEYSIZE_MAX; i++)
    {

        for(j = 0; j < 5; j++)
        {
            if(weights[i] < top_score[j])
            {

                for(k = 4; k > j; k--)
                {

                    top_index[k] = top_index[k-1];
                    top_score[k] = top_score[k-1];

                }

                top_index[j] = i;
                top_score[j] = weights[i];
                break;

            }
        }

    }
        
    printf("The top 5 guesses for key length are...\n");

    for(i = 0; i < 5; i ++)
    {
        printf("Keylength %2d with avg hamming distance --> %f\n", top_index[i], top_score[i]);
        

    }


    /* Process the top guess */
    size_t guessLen = top_index[0];

    printf("\nLet's go with keylength %d\n", guessLen);

    printf("\nThere will be %d strings from transposition\n", guessLen);


    
    /* Create a 2D array to hold transposed strings for each position in guessed keylen */
    unsigned char** trans = (unsigned char**)malloc(sizeof(unsigned char*)*guessLen);
    
    for(i = 0; i < guessLen; i++)
    {
        trans[i] = (unsigned char*)malloc(sizeof(unsigned char)*numBytes/guessLen); 

        for(j = 0; j < numBytes/guessLen; j++)
        {
            trans[i][j] = bytes[i + j*guessLen]; 
        }
    } 


    /* Create pointer to store the temporary XOR'd string */
    unsigned char* xorTemp = (unsigned char*)malloc(sizeof(unsigned char)*numBytes/guessLen);

    /* Set the keysize for the transposed string*/
    unsigned char sKey[1];
    unsigned char* guessKey = (unsigned char*)malloc(sizeof(unsigned char)*guessLen+1);


    int hScore = 0;
    int hIndex = 0;
    int tempScore = 0;
    sKey[0] = 0;


    

    for(i = 0; i < guessLen; i++)
    {
        hScore = 0;
        hIndex = 0;

        /* Score each transposed string with all 256 values 
           Keep the character with the highest score        */
        for(j = 0; j < 256; j++)
        {
            
            memcpy(xorTemp, trans[i], numBytes/guessLen);
            sKey[0] = j;
            xor_string(xorTemp, numBytes/guessLen, sKey, 1);
            tempScore = xor_score(xorTemp, numBytes/guessLen);

            
            if(tempScore > hScore)
            {
                hScore = tempScore;
                hIndex = j;
            }

        
            

        }
        
        guessKey[i] = hIndex;
        

    }

    guessKey[i+1] = '\0';

    printf("\nI think the key is: %s\n\n", guessKey);


    /* Apply the XOR key to the encoded data */
    xor_string(bytes, numBytes-1, guessKey, guessLen);

    printf("%s\n", bytes);


    /* Free dynamically allocated arrays */
    for(i = 0; i < guessLen; i++)
    {
        free(trans[i]);

    }
    

    free(guessKey);
    free(xorTemp);
    free(trans);

    free(bytes);
    free(input);
    free(line);


    return EXIT_SUCCESS;

}
