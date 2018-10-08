#!/bin/sh

if [ -z $1 ]
then
    echo "Usage: v <file_name>"
    exit 1
fi

app=gvim

if test $(file $1 |grep HTML|wc -l) -ne 0 ||\
   test $(file $1 |grep SGML|wc -l) -ne 0 ||\
   test $(file $1 |grep XML|wc -l) -ne 0 
then
    app=firefox
elif test $(file $1 |grep PDF|wc -l) -ne 0 
then
    app=xpdf
elif test $(file $1 |grep image|wc -l) -ne 0
then
    app=gqview
fi

$app $1 &

exit 0

