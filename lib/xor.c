#include <xor.h>

/* XOR a byte encoded string with a repeating (or non-repeating) key */
int xor_string(unsigned char* target, int target_len, unsigned char* key, int key_len )
{

    for(int i = 0; i < target_len; i++)
    {
      target[i] = target[i]^ key[i%key_len];  
    }
    
    return 1;

}

/* Score a string for the number of occurences of the English language's
   most common letters */
int xor_score(unsigned char* msg, int len)
{

    int result = 0;

    for(int i = 0; i < len; i++)
    {
        switch(tolower(msg[i]))
        {
            case('e'):
                result += 13;
                break;

            case('t'):
                result += 12;
                break;

            case('a'):
                result += 11;
                break;

            case('o'):
                result += 10;
                break;

            case('i'):
                result += 9;
                break;

            case('n'):
                result += 8;
                break;

            case(' '):
                result += 7;
                break;

            case('s'):
                result += 6;
                break;

            case('h'):
                result += 5;
                break;

            case('r'):
                result += 4;
                break;

            case('d'):
                result += 3;
                break;

            case('l'):
                result += 2;
                break;

            case('u'):
                result += 1;
                break;
            default:
                break;

        }

    }

    return result;

}

