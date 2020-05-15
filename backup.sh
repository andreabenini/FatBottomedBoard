BACKUP=backup.tar.gz
rm -f $BACKUP
tar -zcf $BACKUP * .gitignore
echo "Backup completed ($BACKUP)"
