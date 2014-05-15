from random import *

from util import symList
# type of magic
# 0: change hp
#   keep, object, points
# 1: immue    
#   keep, object, type
#   magic type
class Magic(object):
    def __init__(self, type, arg):
        self.type = type
        self.arg = arg


def load_magics(magic_list):
    f = open('magic.dat', 'r')
    for eachLine in f:
        line = eachLine.split()
        m = Magic(int(line[0]), int(line[1]) )
        magic_list.append(m)
    f.close()

#symbols = ['HongTao', 'HeiTao', 'FangPian', 'MeiHua']
# symbol: 0 - HongTao; 1- HeiTao; 2- FangPian; 3- MeiHua
class Card(object):
    def __init__(self, name,symbol, number, magic):
        self.name = name
        self.symbol = symbol
        self.number = number
        self.magic = magic

    def draw(self):
        smartPrint(self.name, 'utf-8', 0)
        print symList[self.symbol],
        print self.number,

    def desc(self):
        return self.name + ' ' + symList[self.symbol] +' ' + str(self.number)



def load_cards(card_list):
    f = open('card.dat', 'r')
    for eachLine in f:
        line = eachLine.split()
        c = Card(line[0], int(line[1]), int(line[2]), int(line[3]) )
        card_list.append(c)
    f.close()



