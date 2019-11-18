CC = gcc

all: rsa

rsa:
	$(CC) -o rsa rsa.c -lm

