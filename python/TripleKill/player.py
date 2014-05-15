import time

from util import *


class Player(object):
    def __init__(self, name, ip, time):
        self.name = name
        self.ip = ip
        self.active = time

        self.hp = 0
        self.role = 0
        self.stage = 0

        self.handCards = []
        self.decideCards = []
        self.equipCards = []

    def assign_role(self, role_index, role_list):
        self.role = role_index
        self.hp = role_list[role_index].hp

    def draw(self):
        print '%s [%s]'%(self.name, self.ip)
        roleList[self.role].draw()
        print " HP: ",
        print self.hp

    def desc(self, detail, role_list, card_list):
        temp = symList[7] + '\n'
        temp += '%s [%s]  HP: %d\n'%(self.name,
                role_list[self.role].name, self.hp)

        if detail == True:
            temp += '%s  '% symList[8]
            for c in self.handCards:
                temp += ' [%s] '% card_list[c].desc()
            temp += '\n'

        temp += '%s  '% symList[5]
        for c in self.equipCards:
            temp += ' [%s] '% card_list[c].desc()
        temp += '\n'

        temp += '%s  '% symList[6]
        for c in self.decideCards:
            temp += ' [%s] '% card_list[c].desc()
        temp += '\n'

        temp += '%s\n'% symList[7]

        #smartPrint( temp, CODEC, 1)
        return temp

    

    def list_handcards(self, card_list):
        temp_str = ""
        i = 0
        for c in self.handCards:
            temp_str += '[%d] '% (i+1,)
            temp_str += card_list[c].desc()
            temp_str += '\n'
            i += 1
        temp_str += '[%d] End\n' %(i+1,)
        return temp_str

    def cast_card(self, card):
        self.handCards.remove(card)
#        self.list_handcards()
#        sel = raw_input('$ ')
        return 


        
def get_player( ip, player_list ):
    for p in player_list:
        if p.ip == ip:
            return p

    return None

def add_player( name, ip, time, player_list ):
    p = Player(name, ip, time)
    player_list.append(p)

def print_player( player_list ):
    print 'player number: %d' % len(player_list)
    for i in range(0, len(player_list)):
        print '%d %s [%s]' % (i+1, player_list[i].name, player_list[i].ip)

def live_player( ip, player_list ):
    for p in player_list:
        if p.ip == ip:
            p.active = time.time()

        if time.time() - p.active > MAX_SILENT:
            print '%s disconnected from server.' % p.ip
            player_list.remove(p)
            print_player(player_list)

