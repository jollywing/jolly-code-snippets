#!/bin/sh
begin=`date -d '-5 minute' '+ %Y/%m/%d %H:%M'`
end=`date '+ %Y/%m/%d %H:%M'`
# replace `/' in `begin' and `end' to `\/'
begin=${begin//\//\\\/}
end=${end//\//\\\/}
logfile=nohup.log
log=`sed -n "/$begin/,/$end/p" $logfile`
echo $log
if [ "$log" = "" ]; then
        echo 1
else
        echo $log
fi
