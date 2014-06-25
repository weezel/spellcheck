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
	size_t	 off = 0;

	SLIST_INIT(&grams_head);

	/*while (off < len || off != 0)*/ {
		struct gram	*tmp = init_gram(gramsize);

		off = strlcpy(tmp->buf, word, sizeof(tmp->buf));
		SLIST_INSERT_HEAD(&grams_head, tmp, grams);
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
	char		 testword[] = "Test";
	struct gram	*np = NULL;

	ngram(testword, sizeof(testword), 2);
	SLIST_FOREACH(np, &grams_head, grams)
		fprintf(stdout, "%s\n", np->buf);

	free_gramlist();

	return 0;
}

