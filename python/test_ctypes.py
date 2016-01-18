from ctypes import *
# from ctypes.util import find_library
# find_library("c") will return libc.so.6

# libc.so.6 is located at /lib/x86_64-linux-gnu/libc.so.6

libc = CDLL("libc.so.6")
message = "Hello, world!\n"
libc.printf("Test: %s", message)
