CC=clang
OPTS=-lbsd
LOPTS=-L/usr/include/bsd

all:
	${CC} -ansi -Wall ${LOPTS} ${OPTS} -o damerau_levenshtein damerau_levenshtein.c
clean:
	rm -f damerau_levenshtein *.o
