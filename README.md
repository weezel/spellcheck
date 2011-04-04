##Damerau-Levenstein spellchecker

Compare two words
	damerau_levenstein -w dog dgo

and the result should be like this:
	dog          dgo  1

Compare word "possible" against words found from a file
	damerau_levenstein -i -d 1 -f web2 possible
and the results
	missible   possible  1
	passible   possible  1
	possible   possible  0
	possibly   possible  1

Attention!
It is assumed that the initial of a word is correct, therefore these strings
are seens as the same:
	diff siff -> 0

##Use cases?
Well, my first though was to make a shell spell checker / auto corrector /
quick switch cwd tool that could deal with typos. With the current
implementation you can give a shell history as a parameter and it can propose
correction. Still many important things lacking for appropriate use.

##Other info
There might be silly bugs laying around because its non maturity. Feel free to
report them.

This program is BSD licensed.

Better documentation coming near future.

##TODO
Apparently my Vim configuration in Linux had the wrong settings because the C
code looks so ugly. Sorry for headache.

Separate .c to .c and .h probably.

Store words to tree for more efficient search and save it to disk.
