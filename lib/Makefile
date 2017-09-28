CC=gcc
CFLAGS=-I../header/


aes_cbc: aes_cbc.o
	$(CC) -c aes_cbc.c $(CFLAGS) -lcrypto

pad: pad.o
	$(CC) -c pad.c $(CFLAGS)

hamming: hamming.o
	$(CC) -c hamming.c $(CFLAGS)

conversion: conversion.o
	$(CC) -c conversion.c $(CFLAGS)

xor: xor.c
	$(CC) -c xor.c $(CFLAGS)
