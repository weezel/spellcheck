CC=		clang
CFLAGS=		-pedantic -Wall -std=c99 -Wformat=2 -g
LDFLAGS=
OS=		$(shell uname)

ifeq ($(OS), Linux)
	LDFLAGS += -lbsd
endif

.PHONY: all clean damerau dice ngram

all: damerau

damerau:
	${CC} $(CFLAGS) -o damerau_levenshtein damerau_levenshtein.c $(LDFLAGS)
dice:
	${CC} $(CFLAGS) -o dicecoeff dicecoefficient.c $(LDFLAGS)
ngram:
	${CC} $(CFLAGS) -o ngram ngram.c $(LDFLAGS)
clean:
	rm -f damerau_levenshtein dice ngram *.o
