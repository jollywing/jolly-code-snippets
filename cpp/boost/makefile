cflags = -I"e:/jollywing/job/Client-master/lib/boost"
lflags = -L"e:/jollywing/job/Client-master/lib/boost/stage/lib/win32"
test_boost: test_boost.o
	g++ -o test_boost test_boost.o $(lflags)

%.o: %.cc
	g++ -c $(cflags) $<
