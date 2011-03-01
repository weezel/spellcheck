##Damerau-Levenstein spellchecker

#Compare two words
	damerau_levenstein -w cat bat

and the result should be like this:
	dog          dgo  1

#Compare word "possible" against words found from a file
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

There might be silly bugs laying around because its non maturity. Feel free to
report them.

This program is BSD licensed.

Better documentation coming near future?
