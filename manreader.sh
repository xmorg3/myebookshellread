#This script is a dedicated to the creator of ebook-speaker
#Jos Lemmens / http://jlemmens.nl/ This Script takes no code
#from the original but intends to provide quick and easy way
#of outputing text to speach and saving the progress of a
#text file via a bookmark. it intends to be extreemly portable,
#only requring a shell, awk, seq, and espeak ideally you can
#replace espeak with any other tts which excepts pipe input.

#tested in bash, sh, yash, dash

#limitations, its not curses, or termcap so it cant accept
#keyboard interupts (yet), like going back, etc.

#count the lines / wc
#output lines, one by one to stdout awk
#pipe output to espeak awk | espeak
#print line numbers echo variable

#TODO: bookmarking more than one "converted" book
#will probably overwrite teh previous bookmark.

PS2TXT="/usr/bin/ps2txt" #ghostscript
PDF2TXT="/usr/bin/pdf2txt" #python pdf miner
PS2ASCII="/usr/bin/ps2ascii" #fallback if you have ghostscript.
EBPUB2TXT="/usr/bin/epub2txt" #https://github.com/kevinboone/epub2txt2
HTML2TXT="/usr/bin/html2text" #https://linux.die.net/man/1/html2text ? a package?
#http://userpage.fu-berlin.de/~mbayer/tools/html2text.html
GZIP2TXT="/bin/gunzip -c" #needs gunzip, part of most linux os distros
BZIP2TXT="/usr/bin/bunzip2 -c"
XZ2TXT="/usr/bin/unxz -c"
DETEX="/usr/bin/detex" #install Latex suite
ODT2TXT="/usr/bin/odt2txt" #install odt2txt, check your package manager?
RANDOMTMPFILE="234rqwer2342qrwer423tmp.txt"
#Variables
#ESPEAKCOMMAND="/usr/bin/flite"
ESPEAKCOMMAND="/usr/bin/espeak" #you can add voices with -v <voice name>

if test -f $ESPEAKCOMMAND; then
    ESPEAKFOUND=1 #found espeak!
else
    echo "DEBUG no espeak command, check your ESPEAK variable."
    echo "try whereis espeak, you may need to isntall (usually /usr/bin/espeak)"
    exit
fi

FILEARG=$1 #$2=bookmark $3man? man page

if test -f '/usr/bin/man'; then  #[[ $# > 2 ]]; then #if [ $# -lt 3 ]; then #did you say man?
    #man page out, requires man!
    man -Tascii $FILEARG > $RANDOMTMPFILE
    FILENAME=$RANDOMTMPFILE
    trap 'rm $RANDOMTMPFILE; exit' INT
fi

BMEXT=".bookmark" #new file created with .bookmark appended to name
if [ $# -eq 0 ]; then
    echo "Usage: " $0 ": FILE line-number"
    exit
fi

if [ $# -eq 1 ]; then #new code, trying to solve multi-converted
   if test -f $FILEARG$BMEXT; then #bookmarks
       echo "DEBUG: no args, but found bookmark"
       BOOKMARK=$(cat $FILEARG$BMEXT)
   else
       echo "DEBUG: no args or bookmark, starting form beginning"
       BOOKMARK=1
   fi
else
    echo "DEBUG: starting from arg bookmark"
    BOOKMARK=$2
fi
FILESIZE=$(wc -l $FILENAME | awk '{print $1;}')

echo "bookmark line:"$BOOKMARK"    Exit with C-c"
echo "file lines:"$FILESIZE

#for i in {$a..$z..1} #{(($BOOKMARK))..(($FILESIZE))}
#seq $BOOKMARK $FILESIZE
#OUTMARK=$BOOKMARK
for i in $(seq $BOOKMARK $FILESIZE)
do
    #read -rsn1 -t 0.01 input  #nonfucntional
    #if [ "$input" = "h" ]; then
    #    $i=$i-1
    #fi
    echo $i $(awk -v BM=$i 'NR==BM' $FILENAME)
    awk -v BM=$i 'NR==BM' $FILENAME | $ESPEAKCOMMAND
    #debug creates a bookmark file which outputs the line number
    #last read.
    echo $i > $FILEARG".bookmark" #protect your files!
    #The above statement  uses a ">" very close to your filename
    #and if it somehow overwrites
    #your files dont blame me! I have tested it and it *shouldnt*
    #overwrite.
done

rm $RANDOMTMPFILE # warning i hope you have no tmp.txt in this dir :)
