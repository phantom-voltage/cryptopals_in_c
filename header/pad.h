#include "conversion.h"
#include <string.h>

int pad(unsigned char** dest, char* src, size_t n, size_t p);

size_t get_pad(char* input, size_t b);


/* Gets the padding in bytes for string input for blocksize b */
size_t get_pad(char* input, size_t b)
{
    
    int len = strlen(input);
    
    if(len % b)
    {
        return (b - (len %b));

    }

    else
    {
        return 0;
    }

}

/* Copies n bytes from src to dest, and pads p bytes to dest */
int pad(unsigned char** dest, char* src, size_t n, size_t p)
{

    int i;

    *dest = (unsigned char*)calloc(n+p+1, sizeof(unsigned char));

    if(dest == NULL)
    {
        return -1;
    }

    if(!strncpy(*dest, src, n))
    {
        return -1;
    }


    for(i = 0; i < p; i++)
    {
        *((*dest)+n+i) = p;
    }
    
    *((*dest)+n+i+1) = '\0';
    
    return 1;

}
