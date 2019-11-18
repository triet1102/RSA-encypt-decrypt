CC = gcc
CFLAGS= -g -Wall

all: rsa

rsa:
$(CC) $(CFLAGS) -o rsa rsa.c -lm

