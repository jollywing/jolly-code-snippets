#! /bin/bash
# Description: record time usage
# create: 2010-12-05
# last change: 2010-12-05
# maintainer: Jiqing Wu (jiqingwu@gmail.com)
# version: 0.1

start_time=0
end_time=0
pass_time=0

while [ $? -ne 202 ]; do
    if [ $pass_time -ge 60 ]; then
        let pass_time/=60
        result="time usage: $pass_time minutes."
    else
        result="time usage: $pass_time seconds."
    fi
    xmessage -center -buttons NEW:200,EXIT:202 $result
    if [ $? -eq 200 ]; then
        let start_time=`date '+%s'`
    else
        break
    fi
    xmessage -center -buttons STOP:201,EXIT:202 "time recording ..."
    if [ $? -eq 201 ]; then
        let end_time=`date '+%s'`
        let pass_time=$end_time-$start_time
    fi
done