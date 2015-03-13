
.PHONY: build test clean

build: libmax.so

libmax.so: max.o
	gcc -o $@  -shared $<

max.o: max.c
	gcc -c -fPIC $<

test: a.out

a.out: test.c libmax.so
	gcc test.c -L. -lmax
	LD_LIBRARY_PATH=. ./a.out

clean:
	rm -f *.o *.so a.out
