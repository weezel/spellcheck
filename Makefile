CC=clang
OPTS=-lbsd

all:
	${CC} -ansi -Wall ${OPTS} -o damerau_levenshtein damerau_levenshtein.c
clean:
	rm -f damerau_levenshtein *.o
