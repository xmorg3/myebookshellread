#easily read a cbz comic book file, with a minimal tool
#like a command line image viewer.  No need for a
#separate app.

#in fact , you dont even need this script! you can
#mkdir tmp ; unzip test.cbz -d tmp; feh tmp/ ; rm -r tmp
IMGVIEWER="/usr/bin/sxiv"
SXIV="/usr/bin/sxiv"
FEH="/usr/bin/feh"
NSXIV="/usr/bin/nsxiv"


if test -f $IMGVIEWER ; then
    echo "Image viewer is $IMGVIEWER (IMGVIEWER in your script)"
else
    if test -f $NSXIV ; then
	echo "Image viwer set to nsxiv"
	IMGVIEWER="/usr/bin/nsxiv"
    elif test -f $SXIV ; then
	echo "Image viwer set to sxiv (fallback)"
	IMGVIEWER="/usr/bin/sxiv"
    elif test -f $FEH; then
	echo "Image viwer set to feh (fallback)"
	IMGVIEWER="/usr/bin/feh"
    fi
fi
    
mkdir tmp                                                                                                                                                                                     
unzip $1 -d tmp2857234085734                                                                                                                                                                  
$IMGVIEWER tmp2857234085734/                                                                                                                                                                  
rm -r tmp2857234085734                                                                                                                                                                        
echo "done. "$2   
