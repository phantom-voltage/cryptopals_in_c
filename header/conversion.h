#ifndef CONVERSION_H_INCLUDED
#define CONVERSION_H_INCLUDED 1

#include <stdlib.h>
#include <stdio.h>

/* Function declarations */
void btor64(unsigned char* src, char* dest, size_t n);
void btor64_conversion(unsigned char* srcChunk, char* destPos, int padding);

void r64tob(char* src, unsigned char* dest, size_t n);
void r64tob_conversion(char* srcChunk, unsigned char* destPos);

void htob(char* hex, unsigned char* bytes, int len);

void print_hex(unsigned char* bytes, size_t n);

/* Definitions for various conversions and lookups */

/* 256 array of Decimal values of the base64 characters 
   Organized by ASCII value */

extern int r64Lookup[256];

/* Byte mask for converting hex to base64 */
extern unsigned char mask[3];
/* Character set of base64 */
extern char base64set[65];

#endif
