
print '\nraw input:'
a = int(raw_input('input a integer:'))
b = a + 5

print '\nwhile and if statement:'
name = 'jiqing'
while a < b:
    if a < 10:
        print '  ', a, ': hello,', name
    elif a < 100:
        print ' ', a, ': hello,', name
    else:
        print a, ': hello,', name
    a = a + 1

print '\n function and default args:'
def fuck(somebody = 'Yang'):
    print 'fuck %s!!!' % (somebody)
fuck('Zhao')
fuck()

print '\nlist extend'
li = ['cat', 'dog', 'monky', 'chicken', 'pig']
animals = []
animals.extend(li)
print animals

print '\nlist: sort and pop'
animals.sort()
print animals
print animals.pop()
print animals

# function definition
def hello( somebody ):
    print 'hello, %s' % (somebody)

print '\nfor statement and range method:'
for animal in animals:
    hello(animal)
# range, also you can use range(a, b)
for i in range(len(li)):
    print i, li[i]

print '\ntouple:'
t = ('Beijing', 'Shanghai', 'Guangzhou')
print t
print t[0]

print '\ndictionary:'
d = {100:'dog', 200:'cat', 300:'pig'}
for index in d.keys():
    print d[index]
del d[200]
print d.keys()

print 100 in d
