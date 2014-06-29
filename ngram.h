#ifndef	__NGRAM_H__
#define	__NGRAM_H__

#if defined __linux__
#include "lnxport.h"
#endif

#include <sys/queue.h>

struct gram {
	char			*buf;
	SLIST_ENTRY(gram)	 grams;
};

SLIST_HEAD(grams_head, gram)	grams_head;

void		ngram(const char *, size_t, size_t);
struct gram *	init_gram(size_t);
void		free_gramlist(void);

#endif
