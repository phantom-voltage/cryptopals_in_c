# cryptopals_in_c
My attempts at the Cryptopals challengs written in C

I attempted this in C, because I was frustrated with Python3 and how it uses UTF-8 encoding by default. Doing this in C and juggling ~~unsigned chars~~ uint8_t's was a lot more bare metal. I actually really enjoyed doing the first part in C.

A lot of the work was cleaned up and put in header files, after I got them
working in the main program.

## Compiling 

These were all compiled using GCC on an x86_64 architecture. I used
unsigned chars a lot, I might go back and change them to uint8_t at some
point, just for compatibility with other machines.

## Libraries

Besides the standard C libraries, and the ones I've made myself, I've included PCG for a psuedo random number generator.

### Actually Compiling 

I've updated the project to use makefiles, so just cd to the directory and type make. The executable produced will be named main in all problems.


`make`
