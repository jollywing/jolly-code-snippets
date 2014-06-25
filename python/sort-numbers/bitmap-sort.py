import time

MAX = 100000
l = [0] * MAX
f = open('in.data')

while True:
    r = f.readline()
    if r != '':
        if r != '\n' and r != '\r\n':
            n = int(r)
            l[n] = 1
    else:
        break

f.close()

f = open('out.data', 'w')
for i in list(range(MAX)):
    if l[i] == 1:
        f.write('{}\n'.format(i))
f.close()

print('time usage: {}'.format(time.process_time()))

