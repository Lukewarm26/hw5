# Makefile
# Lucas Eifert
# COSC 3750 Spring 22
# Homework 4
# Modified 2/19/21
#
# Makefile to compile wyls.c program
CC=gcc
CFLAGS=-Wall -g
RM=/bin/rm -f

.PHONY: clean

wycat: wyls.c 
	${CC} ${CFLAGS} wyls.c -o wyls

clean: 
	${RM} wyls
