#ifndef _DAMERAU_LEVENHSTHEIN_H_
#define _DAMERAU_LEVENHSTHEIN_H_
#endif

void		usage(void);
int		min(const int, const int);
unsigned int	levensteinDistance(const char *, const size_t, const char *,
				   const size_t);
void		convertlowercase(char *, const size_t);
void		comparefile(const char *, const char *, const size_t);
