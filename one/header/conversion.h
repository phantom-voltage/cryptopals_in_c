/* Function definitions */
void btor64(unsigned char* src, char* dest, size_t n);
void btor64_conversion(unsigned char* srcChunk, char* destPos, int padding);

void r64tob(char* src, unsigned char* dest, size_t n);
void r64tob_conversion(char* srcChunk, unsigned char* destPos);

void htob(char* hex, unsigned char* bytes, int len);

void print_hex(unsigned char* bytes, size_t n);

/* Definitions for various conversions and lookups */

/* 256 array of Decimal values of the base64 characters 
   Organized by ASCII value */
int r64Lookup[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 62, 0, 0, 0, 63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 0, 0, 0, 0, 0, 0, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

/* Byte mask for converting hex to base64 */
unsigned char mask[] = {   3, /* 00000011 */
                          15, /* 00001111 */
                          63  /* 00111111 */
                       };
/* Character set of base64 */
char base64set[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


/* Functions*/


/* Converts binary unsigned char string to base64 encoded char string
   n is size in bytes                                                */
void btor64(unsigned char* src, char* dest, size_t n)
{

    int count = 0;
    int padding = n % 3;
    
    while(count < n / 3)
    {
        
        btor64_conversion(src + 3*count, dest + 4*count, 0);
        count++;
        
    }
    

    if ( padding )
    {
        src[n] = 0;
        
        if (padding == 1)
        {
            src[n+1] = 0;
        }
     
        btor64_conversion(src + 3*count, dest + 4*count, padding);
        count++;
    }

    *(dest+4*count) = '\0';


    return;

}

/* Computation function for binary to base64 conversion */

void btor64_conversion(unsigned char *srcChunk, char* destPos, int padding)
{

    *destPos = base64set[srcChunk[0] >> 2];
    *(destPos+1) = base64set[((srcChunk[0] & mask[0]) << 4) + (srcChunk[1] >> 4) ];

    if(padding == 1)
        *(destPos+2) = '=';
    else 
        *(destPos+2) = base64set[((srcChunk[1] & mask[1]) << 2) + (srcChunk[2] >> 6)];

    if(padding)
        *(destPos+3) = '=';
    else
        *(destPos+3) = base64set[srcChunk[2] & mask[2]];
    
    
    return;

}

/* Convert base64 (radix64) to binary
   Takes signed char string and writes to unsigned char string
   n is size of base64 string in characters */

void r64tob(char* src, unsigned char* dest, size_t n)
{

    int i = 0;

    while(i < (n/4) ) 
    {
        
        r64tob_conversion(src+(4*i), dest+(3*i));
        i++;

    }

    return;
}



/* Computation function for base64 to binary conversion */

void r64tob_conversion(char* srcChunk, unsigned char* destPos)
{

    int r1 = r64Lookup[srcChunk[0]];
    int r2 = r64Lookup[srcChunk[1]];
    int r3 = r64Lookup[srcChunk[2]];
    int r4 = r64Lookup[srcChunk[3]];

    destPos[0] = (r1 << 2) + (r2 >>4);
    destPos[1] = (r2 << 4) + (r3 >>2);
    destPos[2] = (r3 << 6) + r4;

    return;

}

/* Function that prints result in hex, doesn't do conversion,
   because this is so easy to write to and from in binary */

void print_hex(unsigned char* bytes, size_t n)
{

    for(int i = 0; i < n; i++)
    {
        printf("%02x", bytes[i]);

    }

    printf("\n");


}


/* Convert hex string to bytes in unsigned char array 
   Len is in length of hex string                    */
void htob(char* hex, unsigned char* bytes, int len)
{

    for(int i = 0; i < len/2; i++)
    {
        sscanf(hex, "%2hhx", &bytes[i]);
        hex +=2;

    }

}
