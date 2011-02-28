CC=clang

all:
	${CC} -ansi -Wall -o damerau_levenstein damerau_levenstein.c
clean:
	rm -f damerau_levenstein *.o
