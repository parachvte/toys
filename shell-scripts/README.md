This directory include some useful shell scripts

### Find 5 files that have their sizes greater than 1024K

find . -mount -size +1024k -type f -exec ls -lah {} \; | sort -rnb -k 5
