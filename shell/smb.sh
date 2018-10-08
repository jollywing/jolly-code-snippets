#!/bin/sh

#author: jiqing
#mount and umount samba service
#version: 2.1
#release: 2009-03-31
#update: 2009-10-30

hostname=202.197.22.11
servicename=public
objdirname=/home/jiqing/smb

if test ! -z $1
then
    servicename=$1
fi

if test -d $objdirname
then
    # if the objdir is empty
    if test $(ls -Al $objdirname|wc -l) -eq 1
    then
        echo "mounting $hostname/$servicename ..."
        smbmount //$hostname/$servicename $objdirname -o iocharset=utf8 #codepage=cp936
    else
        echo "!!! umounting samba service ..."
        smbumount $objdirname
    fi
else
    echo 'mount object dir is not exist.'
    exit 1
fi
        
exit 0
