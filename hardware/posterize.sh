# Create a poster from a big image

# File name
FILENAME=$1

# Image size on page
PAGEX=800
PAGEY=450

# Margin size
MARGIN=50

# Border size
#BORDER=""
#BORDER="-frame 1x1+0+0 -mattecolor white"
BORDER="-bordercolor gray -border 1"

# Additional options (if any)
OPTIONS=""

# Output file
OUTFILE=poster-
OUTFILE_EXT=.png

if [ "$FILENAME" == "" ]; then
    FILENAME=keyboard-frame.png
fi
if [ ! -f $FILENAME ]; then
    echo "$FILENAME not found"
    exit 1
fi

DIMENSIONS=`magick identify $FILENAME | cut -d " " -f 3`
echo "$FILENAME: $DIMENSIONS  (Page: ${PAGEX}x${PAGEY})"
read -r FILEX FILEY <<<$(echo "$DIMENSIONS" | sed 's/x/ /')

COUNT=1
rm -f $OUTFILE*
for (( x=0; x<$FILEX; x=x+PAGEX-MARGIN )); do
    for (( y=0; y<$FILEY; y=y+PAGEY-MARGIN )); do
        OUTIMAGE="$OUTFILE$COUNT$OUTFILE_EXT"
        echo " -> $OUTIMAGE"
        convert $FILENAME +repage -crop ${PAGEX}x${PAGEY}+${x}+${y} $BORDER $OPTIONS "$OUTIMAGE"
        COUNT=$((COUNT+1))
    done
done
