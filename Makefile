CC	= clang
CFLAGS	= -pedantic -Wall -std=c99 -Wformat=2 -g
#CLIBS	= -lbsd

.PHONY: all clean damerau

all: damerau

damerau:
	${CC} $(CFLAGS) -o damerau_levenshtein damerau_levenshtein.c $(CLIBS)
dice:
	${CC} $(CFLAGS) -o dicecoeff dicecoefficient.c $(CLIBS)
ngram:
	${CC} $(CFLAGS) -o ngram ngram.c $(CLIBS)
clean:
	rm -f damerau_levenshtein dice ngram *.o
