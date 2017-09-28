/* Header file is used to computer hamming distance 
   This number represents the number of differing bits between
   two binary numbers.
*/

#ifndef HAMMING_H_INCLUDED
#define HAMMING_H_INCLUDED 1


extern int hammingWeights[256];

float get_hamming(unsigned char* input, int len, int keysize);
int compute_hamming(unsigned char* word1, unsigned char* word2, int len);



#endif
