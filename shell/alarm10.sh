#! /bin/bash
# Description: a  timer to count down
# Last Change: 2009-12-02
# Maintainer: Jiqing Wu (jiqingwu@gmail.com)
# Version: 0.1
# Version: 0.2 use xmessage instead of feh

#alarm_pic=$HOME/blog/bin/timeup.jpg

times=0

while true
do
    let total_min=times*10
    echo "Total working time: $total_min minutes." 
    let times++
    echo "Turn $times: work hard!"
    sleep 10m
    #feh $alarm_pic
    xmessage 'TIME UP, RELAX!!'
done

