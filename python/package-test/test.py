import hello
# import hello.tmd
from hello import tmd

print tmd.add(11, 12)

if hasattr(tmd, 'good_morning'):
    morning_func = getattr(tmd, 'good_morning')
    morning_func()

if hasattr(hello, 'version'):
    ver_func = getattr(hello, 'version')
    ver_func()
