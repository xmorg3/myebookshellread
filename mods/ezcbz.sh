#easily read a cbz comic book file, with a minimal tool
#like a command line image viewer.  No need for a
#separate app.

#in fact , you dont even need this script! you can
#mkdir tmp ; unzip test.cbz -d tmp; feh tmp/ ; rm -r tmp
IMGVIEWER="feh"
#IMGVIEWER="sxiv"
#IMGVIEWER="nsxiv"

mkdir tmp
unzip $1 -d tmp2857234085734
$IMGVIEWER tmp2857234085734/
rm -r tmp2857234085734
echo "done. "$2
