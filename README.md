# cryptopals_in_c
My attempts at the Cryptopals challengs written in C

I attempted this in C, because I was frustrated with Python3 and how it uses UTF-8 encoding by default. Doing this in C and juggling ~~unsigned chars~~ uint8_t's was a lot more bare metal. I actually really enjoyed doing the first part in C.

A lot of the work was cleaned up and put in header files, after I got them
working in the main program.

## Compiling 

These were all compiled using GCC on an x86_64 architecture. I used
unsigned chars a lot, I might go back and change them to uint8_t at some
point, just for compatibility with other machines.


### Headers

Headers are in a single header file in the root directory, as much of the
code is reused. Use link.sh to create the symlinks for each challenge set. 

### Actually Compiling 

`gcc -o main main.c`

Challenges 7+ might require

`gcc -o main main.c -lcrypto`


