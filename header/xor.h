#ifndef XOR_H_INCLUDED
#define XOR_H_INCLUDED 1

#include <ctype.h>

/* This header function is used to help do some crypto related XOR operations on 
   encoded strings */

/* Function definitions */
int xor_score(unsigned char* msg, int len);
int xor_string(unsigned char* target, int target_len, unsigned char* key, int key_len);


#endif
