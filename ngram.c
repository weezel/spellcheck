#include <ctype.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/queue.h>

#include "ngram.h"

void
ngram(const char *word, size_t len, size_t gramsize)
{
	char		*c = 0;
	size_t		 i = 0;
	struct gram	*prevgram = NULL;

	SLIST_INIT(&grams_head);

	c = (char *) word;

	while (iscntrl(*c) == 0) {
		struct gram	*newgram = init_gram(gramsize);

		i = 0;

		while (i < gramsize && iscntrl(*c) == 0)
			newgram ->buf[++i] = *c++;
		newgram->buf[i] = '\0';

		if (prevgram == NULL)
			SLIST_INSERT_HEAD(&grams_head, newgram, grams);
		else
			SLIST_INSERT_AFTER(prevgram, newgram, grams);
		prevgram = newgram;
	}
}

struct gram *
init_gram(size_t gramsize)
{
	struct gram	*tmp;

	if ((tmp = calloc(1, sizeof(struct gram))) == NULL)
		err(1, NULL);
	if ((tmp->buf = calloc(gramsize + 1, sizeof(char))) == NULL)
		err(1, NULL);

	return tmp;
}

void
free_gramlist(void)
{
	struct gram	*tmp;

	while (!SLIST_EMPTY(&grams_head)) {
		tmp = SLIST_FIRST(&grams_head);
		SLIST_REMOVE_HEAD(&grams_head, grams);
		free(tmp->buf);
		free(tmp);
	}
}

int
main(int argc, const char *argv[])
{
	char		 testword[] = "Testi";
	struct gram	*np = NULL;

	ngram(testword, sizeof(testword), 2);
	SLIST_FOREACH(np, &grams_head, grams)
		fprintf(stdout, "%s\n", np->buf);

	free_gramlist();

	return 0;
}

