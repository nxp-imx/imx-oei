#!/bin/bash

cd `dirname $0`

extentions=( h c hpp cpp cc )
rm -f sf.list

for ext in ${extentions[@]}; do
  find . -name "*.$ext" >> sf.list
done

echo \
"NOINLINE
CONTENT_EXPORT" > ./ignore.list

ctags --sort=1 --c++-kinds=+pf --fields=+imaSft -L sf.list -I ignore.list 
cscope -bqu -i sf.list

rm -f ignore.list sf.list
