#myebookshellread

This script is a dedicated to the creator of ebook-speaker
Jos Lemmens / http://jlemmens.nl/ This Script takes no code
from the original but intends to provide quick and easy way
of outputing text to speach and saving the progress of a
text file via a bookmark. it intends to be extreemly portable,
only requring a shell, awk, seq, and espeak ideally you can
replace espeak with any other tts which excepts pipe input.

Currently its just a wrapper for espeak, with bookmarking support,

tested in bash, sh, yash, dash

Usage: ebookreader.sh FILENAME LINENUMBER
	Line Number is optional.  If not supplied it will start at line 1
	if a .bookmark file exists, it will start at the line in the file
	if you specifiy your own line it will start there.
	
Limitations:
	Without TERMCAP or curses, this script cannot accept interactive
	input, like LEFT/RIGHT to go back.  I believe I could create a C
	program with termbox, to emulate this script and add the key
	interactions.

