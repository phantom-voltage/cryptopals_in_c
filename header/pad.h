#ifndef PAD_H_INCLUDED
#define PAD_H_INCLUDED 1

#include <stdio.h>
#include <stdlib.h>
#include "conversion.h"
#include <string.h>

int double_pad(char** dest, char* src, size_t len, int f, int b);
int pad(unsigned char** dest, char* src, size_t n, size_t p);
size_t get_pad(char* input, size_t b);
int rand_pad(char* dest, char* src);

#endif
