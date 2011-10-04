CC=clang

all:
	${CC} -g -ansi -Wall -o damerau_levenshtein damerau_levenshtein.c
clean:
	rm -f damerau_levenshtein *.o
