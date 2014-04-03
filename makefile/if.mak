# To make this work on unix, you need gmake instead of make
CC=gcc

ALL:
# condition-directive can not be started with TAB
ifeq ($(CC),gcc)
	echo "your compiler is gcc."
else
	echo "your compiler is not gcc."
endif
