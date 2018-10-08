
class ClassA(object):
    l = []

a = ClassA()
print len(a.l)
a.l.append(1)
print len(a.l)
b = ClassA()
print len(b.l)
a.l.remove(1)
print len(b.l)
