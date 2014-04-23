#!/bin/bash

for seg in $(ls *.ts)
do
echo "Encrypting $seg ..."
base="$(basename $seg .ts)"
keyfile="${base}.key"
openssl rand 16 > $keyfile
hexKey=`cat $keyfile | hexdump -e '16/1 "%02x"'`
hexIV='0'
echo "hexKey: ${hexKey}"
out="${base}-encrypted.ts"
openssl aes-128-cbc -e -in $seg -out $out -p -nosalt -iv ${hexIV}  -K ${hexKey}
echo "Create $out."
done




