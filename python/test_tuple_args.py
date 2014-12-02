
def sum23(a, b, c = 0):
    return a + b + c

a1 = (1, 3)
a2 = [2.5, 10000, 99]

print sum23(*a1) # a1 will be expanded into 2 args
print sum23(*a2) # a2 will be expanded into 3 args

d = {'a':100, 'b':33, 'c': 33 }

print sum23(**d) # d will be expanded into 3 args
