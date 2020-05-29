#!/usr/bin/env bash
#
BACKUP=backup.tar.gz
if [ ! -f backup.tar.gz ]; then
    echo "ERROR: No such file or directory ($BACKUP)"
    exit 1
fi

# Confirm
echo -n "Restore '$BACKUP' into this dir [y|N] ? "
read -n 1 reply
if [ "$reply" != "y" ]; then
    echo -e "\nOperation aborted\n"
    exit 1
fi

# Remove archive files from this dir, if any
echo -e "\n\nplease wait..."
FILELIST=`tar -tzf backup.tar.gz |sed 's/\/.*//' |uniq`
for FILE in $FILELIST; do
    rm -rf $FILE 2>/dev/null
done

# Decompress archive
tar -zxf backup.tar.gz
echo -e "Restore completed\n"
