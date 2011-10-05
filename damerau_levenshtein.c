#include <ctype.h>
#include <err.h>
#include <getopt.h>
#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined __linux__
#define u_char unsigned char
#include <bsd/stdio.h>
#include <bsd/stdlib.h>
#endif

#define LINEBUFFER 1024

int iflag;
int dflag;
int tflag;
int wdist;

void usage(void);
int min(const int, const int);
unsigned int levensteinDistance(const char *, const size_t, const char *, const size_t);
void convertlowercase(char *, const size_t);
void comparefile(const char *, const char *, const size_t);

int
main(int argc, const char *argv[])
{
	int		 fflag;
	int		 wflag;
	int		 ch;
	char		*fname;
	const char	*errstr;
	char		*word1;
	char		*word2;


	dflag = fflag = iflag = wflag = ch = 0;
	fname = word1 = word2 = NULL;

	if (argc < 3)
		usage();

	while ((ch = getopt(argc, (char *const *)argv, "d:f:iw:")) != -1) {
		switch ((char)ch) {
		case 'd': /* difference can be wdist <= distance */
			dflag = 1;
			wdist = strtonum(optarg, 0, 128, &errstr);
			if (errstr)
				errx(1, "Error: %s\nOut of range: %s", errstr, optarg);
			break;
		case 'f':
			fflag = 1;
			fname = optarg;
			break;
		case 'i':
			iflag = 1;
			break;
		case 'w':
			wflag = 1;
			word1 = optarg;
			break;
		case '?':
			if (optopt == 'f')
				(void)fprintf(stderr, "Missing file argument\n");
			else if (optopt == 'w')
				(void)fprintf(stderr, "Missing word argument\n");
			exit(1);
		default:
			usage();
		}
	}

	word2 = (char *const)argv[argc-1];

	if (iflag) {
		if (!fflag)
			convertlowercase(word1, strlen(word1));
		convertlowercase(word2, strlen(word2));
	}

	if (fflag)
		comparefile(fname, word2, strlen(word2));
	else if (wflag) {
		int diff;

		diff = levensteinDistance(word1, strlen(word1), word2, strlen(word2));

		if (!dflag)
			(void)fprintf(stdout, "%-10s %5s %2d\n", word1, word2, diff);
		else if (diff <= wdist)
			(void)fprintf(stdout, "%-10s %5s %2d\n", word1, word2, diff);
	}
	else
		usage();

	return (0);
}

void
usage(void)
{
	extern char *__progname;

	(void)fprintf(stderr, "usage: %s [-d NUM] [-f file] [-i] [-w word] word\n", __progname);
	exit(1);
}


int
min(const int a, const int b)
{
	return a <= b ? a : b;
}

unsigned int
levensteinDistance(const char *s1, const size_t s1len, const char *s2, const size_t s2len)
{
	int cost, i , j, result, sumofall;
	int **resultable;

	cost = i = j = sumofall = 0;

	if ((resultable = calloc(s1len+1, sizeof(int *))) == NULL)
		err(10, "malloc");

	for (i=0; i < s1len+1; i++) {
		if ((resultable[i] = calloc(s2len+1, sizeof(int))) == NULL)
			err(10, "malloc");
	}

	for (i=0; i <= s1len; i++)
		resultable[i][0] = i;
	for (j=0; j <= s2len; j++)
		resultable[0][j] = j;

	for (i=1; i <= s1len; i++) {
		for (j=1; j <= s2len; j++) {
			cost = (s1[i-1] == s2[j-1]) ?  0 : 1;

			sumofall = min(min(
					   resultable[i-1][j] + 1,		/* deletion */
					   resultable[i][j-1] + 1		/* insertion */
					   ),
					   resultable[i-1][j-1] + cost);	/* substitution */


			/*
			if (i > 1 && j > 1) {
				int transpos = resultable[i-1][j-2] + 1;

				if (s1[i-2] != s2[j-1])
					transpos++;
				if (s1[i-1] != s2[j-2])
					transpos++;
				if (sumofall > transpos)
					sumofall = transpos;
			}
			*/
			resultable[i][j] = sumofall;
		}
	}

	result = resultable[s1len][s2len];

	for (i=0; i < s1len+1; i++)
		free(resultable[i]);
	free(resultable);

	return result;
}

void
convertlowercase(char *s, const size_t len)
{
	int i;

	for (i=0; i < len; i++)
		s[i] = tolower(s[i]);
}

void
comparefile(const char *fname, const char *s, const size_t len)
{
	FILE *fp;
	char linebuf[LINEBUFFER];

	if ((fp = fopen(fname, "r")) == NULL)
		err(1, "%s", fname);

	while ((fgets(linebuf, sizeof(linebuf), fp)) != NULL) {
		int diff = 0;

		if (linebuf[strlen(linebuf)-1] == '\n')
			linebuf[strlen(linebuf)-1] = '\0';

		if (iflag)
			convertlowercase(linebuf, strlen(linebuf));

		diff = levensteinDistance(linebuf, strlen(linebuf), s, strlen(s));

		if (!dflag)
			(void)fprintf(stdout, "%-10s %5s %2d\n", linebuf, s, diff);
		else if (diff <= wdist)
			(void)fprintf(stdout, "%-10s %5s %2d\n", linebuf, s, diff);
	}
	fclose(fp);
}

