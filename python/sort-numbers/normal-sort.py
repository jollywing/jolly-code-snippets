import time

l = []

f = open('in.data')
while True:
    r = f.readline()
    if r == '':
        break
    else:
        if r != '\n' and r != '\r' and r != '\r\n':
            n = int(r)
            l.append(n)
f.close()

l.sort()
f = open('out.data', 'w')
for i in l:
    f.write('{}\n'.format(i))
f.close()

print('time usage: {}'.format(time.process_time()))
    
