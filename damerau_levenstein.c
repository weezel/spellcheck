#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
min(const int a, const int b)
{
	return a <= b ? a : b;
}

int
levensteinDistance(const char *s1, const int s1len, const char *s2, const int s2len)
{
	int cost, i , j, result;
	int **resultable;

	cost = i = j = 0;

	if ((resultable = (int **)calloc(s1len+1, sizeof(int *))) == NULL)
		err(10, NULL);

	for (i=0; i < s1len+1; i++) {
		if ((resultable[i] = (int *)calloc(s2len+1, sizeof(int))) == NULL)
			err(10, NULL);
	}

	for (i=0; i <= s1len; i++)
		resultable[i][0] = i;
	for (j=0; j <= s2len; j++)
		resultable[0][j] = j;

	for (i=1; i < s1len; i++) {
		for (j=1; j < s2len; j++) {
			if (s1[i] == s2[j])
				cost = 0;
			else
				cost = 1;
			resultable[i][j] = min(
					min(resultable[i-1][j]+1, /* deletion */
					resultable[i][j-1]+1), /* insertion */
					resultable[i-1][j-1]+cost);	/* substitution */
			if (i > 1 && j > 1 && s1[i] == s2[j-1] &&
					s1[i-1] == s2[j]) {
				resultable[i][j] = min(resultable[i][j],
						resultable[i-2][j-2]+cost);	  /* transposition */
			}
		}
	} 

	result = resultable[s1len-1][s2len-1];

	for (i=0; i < s1len+1; i++)
		free(resultable[i]);
	free(resultable);

	return result;
}

int
main(int argc, const char *argv[])
{
	int result;

	if (argc < 3) {
		fprintf(stderr, "Need two words as parameters");
		exit(1);
	}

	result = levensteinDistance(argv[1], strlen(argv[1]), argv[2], strlen(argv[2]));
	fprintf(stdout, "%s %s %d\n", argv[1], argv[2], result);

	return (0);
}
