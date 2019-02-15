rm -f keyboard-frame.png
# Convert and remove alpha channel as well
convert -colorspace rgb keyboard-frame.eps -alpha off keyboard-frame.png && identify keyboard-frame.png

