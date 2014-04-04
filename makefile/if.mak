# To make this work on unix, you need gmake instead of make
CC=gcc
host_os:=freebsd10.0			#When you refer host_os, host_os will be expanded immediately.

ALL:
	echo $(findstring freebsd, $(host_os))
# condition-directive can not be started with TAB
ifeq ($(CC),gcc)
	echo "your compiler is gcc."
else
	echo "your compiler is not gcc."
endif
