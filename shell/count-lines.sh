
#! /usr/bin/bash

extensions="c h"
excluded_dirs="win32"

lines=0

is_excluded()
{
    for dir in excluded_dirs; do
        if [ $dir = $1 ]; then
            echo 1
            return
        fi
    done
    echo 0
}

for ex in $extensions; do
    for src in `find . -name "*.$ex"`; do
        if [ $(is_excluded $src) = 0 ]; then
            echo $src
            lines=$((lines+`wc -l  $src|awk '{print $1}'`))
        fi
    done
done

echo "total lines: $lines"
