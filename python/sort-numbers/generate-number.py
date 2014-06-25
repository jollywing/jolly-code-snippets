
import random

MAX = 100000
l = []

for i in range(0, MAX):
    l.append(i)

random.shuffle(l)

f = open('in.data', 'w')
for i in l:
    f.write('{}\n'.format(i))
f.close()
