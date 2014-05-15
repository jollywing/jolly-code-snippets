
from card import *
from role import *
from player import *

JOINING = True
GAME_RUNNING = False

magicList = []
cardList = []
roleList = []
playerList = []

availRoles = []
availCards = []

def assign_roles(avail_roles, player_list):
    for p in player_list:
        ran = randrange(len(avail_roles))
        r = avail_roles[ran]
        p.assign_role( r, roleList )
        del avail_roles[ran]


def resupply_cards(avail_cards):
    global cardList
    avail_cards.extend( range(0, len(cardList)) )
    shuffle(avail_cards)

def handout_cards(avail_cards, player_list):
    for p in player_list:
        for i in range(2):
            p.handCards.append( avail_cards[0] )
            del avail_cards[0]
            if len(avail_cards) == 0:
                resupply_cards(avail_cards)


def init_game():
    load_magics(magicList)
    load_cards(cardList)
    load_roles(roleList, availRoles)
    load_msg('msg.txt', msgList)
    load_symbol('symbol.dat', symList)
    assign_roles(availRoles, playerList)
    resupply_cards(availCards)
    handout_cards(availCards, playerList)

