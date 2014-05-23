
import sys

def test_sys_argv():
    '''Print the arguments.

    one in each line.'''
    for i in sys.argv:
        print(i)

def test_sys_path():
    '''Print the path for python to look up modules.

    one in each line.'''
    for p in sys.path:
        print(p)

print('Test module {0}:'.format(sys.__name__))
test_sys_argv()
test_sys_path()

# You can use del to delete a name from current module.
# name includes: variable, function, class
del test_sys_argv
