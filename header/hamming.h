/* Header file is used to computer hamming distance 
   This number represents the number of differing bits between
   two binary numbers.
*/

/* Function definitions */
float get_hamming(unsigned char* input, int len, int keysize);
int compute_hamming(unsigned char* word1, unsigned char* word2, int len);

/* Hamming weight represents the number of 1 bits in a binary number
   This look up table up to 255 reduces computation time */
int hammingWeights[]  = { 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8};


/* This function does the computation of the hamming distance between two
   byte encoded strings.                                                 */
int compute_hamming(unsigned char* word1, unsigned char* word2, int len)
{

    int d = 0;

    for(int i = 0; i < len; i++)
    {

        d += hammingWeights[word1[i] ^ word2[i]];

    }

    return d;
    

}

/* This computes the average hamming distance for each keysized chunk of bytes
   with every other keysized chunk in the string of bytes  */
float get_hamming(unsigned char* input, int len, int keysize)
{

    float weight = 0;
    int count = 0;

    int i, j;

    for(i = 0; i*keysize < len ; i++)
    {

        for(j = 1; j*keysize < len; j++) 
        {
        
            if( i != j)
            {
                weight += compute_hamming(input+i*keysize, input+j*keysize, keysize);
                count++;
            }
        }
    
    }

    weight = weight / (float)keysize;
    weight = weight / (float)count;

    return weight;

}
