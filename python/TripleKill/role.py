from util import *

class Role(object):
    def __init__(self, name, hp):
        self.name = name
        self.hp = hp
        self.range = 1
        self.magics = []

    def draw(self):
        smartPrint(self.name, 'utf-8', 0)


def load_roles(role_list, avail_roles):
    f = open('role.dat', 'r')
    for eachLine in f:
        line = eachLine.split()
        r = Role(line[0], int(line[1]) )
        role_list.append(r)
    f.close()
    avail_roles.extend( range(0, len(role_list) ) )
    print avail_roles

