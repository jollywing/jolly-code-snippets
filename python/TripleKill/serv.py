# Triple kill server

from socket import *
from time import ctime, sleep
import time
import thread
import re

from game import *
from card import *
from util import *


def heartbeat():
    hbSock = socket(AF_INET, SOCK_DGRAM)
    addr = ('', HB_PORT)
    hbSock.bind(addr)
    hbSock.settimeout(1)

    while(True):
        if (len(playerList) ):
            try:
                data,addr = hbSock.recvfrom(5)
                if data == 'LIVE':
                    live_player(addr[0], playerList)
            except:
                live_player( '', playerList )

        else:
            sleep(1)

serSock = socket(AF_INET, SOCK_DGRAM)
serSock.bind( ('', SERV_PORT) )

def inform(msg, codec, player):
    u_msg = unicode(msg, codec).encode(CODEC)
    serSock.sendto(u_msg, (player.ip, CLIENT_PORT) )

def broadcast(msg, codec):
    for p in playerList:
        inform(msg, codec, p)

def wait_reply(p):
    while True:
        data,addr = serSock.recvfrom(BUFSIZE)
        if data and addr[0] == p.ip:
            return int(data)

def handle_msg(msg, p):
    data = msg.split()

    if data[0] == 'CASTCARD':
        if data[1] == 'END':
            p.stage +=1
        else:
            card = int(data[1])
            p.cast_card(card)
    elif data[0] == 'DROPCARD':
        if data[1] == 'END':
            p.stage +=1
        else:
            card = int(data[1])
            if p.drop_card(card) == True:
                p.stage +=1



print 'waiting for joining of clients ....'
thread.start_new_thread(heartbeat, ())

while( JOINING ):
    data, addr = serSock.recvfrom(BUFSIZE)
    p = get_player(addr[0], playerList)

    msg = data.split()
    if msg[0] == 'JOIN':
        print '%s joined.' % msg[1]
        serSock.sendto('JOIN_OK', addr)

        add_player(msg[1], addr[0], time.time(), playerList)
        print_player(playerList)

    elif msg[0] == 'START':
        if len(playerList) < 2:
            inform ('the number of players is not enough!', 'utf-8',
                    p)
        else:
            broadcast('%s start the game !!!!'% p.name, 'utf-8')
            JOINING = False
    else:
        for p in playerList:
            if (p.ip != addr[0]):
                serSock.sendto(data, (p.ip, CLIENT_PORT) );

GAME_RUNNING = True
print 'game start ....'


init_game()

# PICKCARD
# CASTCARD
# DROPCARD

turn = 0 
state = 'SELECT_CARD'

while(GAME_RUNNING):
    #global availCards, turn, playerList

    #stage 1 TODO: decide
    if playerList[turn].stage == 0:
        for p1 in playerList:
            other_str = ""
            for p2 in playerList:
                if p2 != p1:
                    other_str += p2.desc(False, roleList, cardList)
            self_str = p1.desc(True, roleList, cardList)
            inform( self_str + other_str, 'utf-8', p1)

        playerList[turn].stage +=1
    #stage 2: pick card
    elif playerList[turn].stage == 1:
        temp_msg = []
        temp_msg.append(msgList[1])
        for n in range(2):
            playerList[turn].handCards.append( availCards[0] )
            temp_msg.append('%d %s'% (n+1,
                cardList[availCards[0]].desc()) )
            del availCards[0]
            
            if len(availCards) <= 0:
                resupply_cards(availCards)

        print '%s picked 2 cards.'%playerList[turn].name
        print 'available cards: %d.'% len(availCards)


        msg_str = listToStr(temp_msg)

        i = 0
        for p in playerList:
            if i == turn:
                inform(msg_str, 'utf-8', p)
            else:
                inform(msgList[0] % 
                        playerList[turn].name, 'utf-8', p )
            i+=1

        playerList[turn].stage +=1

    # stage 3: cast cards
    elif playerList[turn].stage == 2:
        print 'It is turn for %s to cast cards.'% playerList[turn].name

        if state == 'SELECT_CARD':
            i=0
            for p in playerList:
                if i == turn:
                    inform(msgList[3], 'utf-8', p)
                else:
                    inform(msgList[2]%playerList[turn].name, 'utf-8', p)
                i += 1

            inform( playerList[turn].list_handcards(cardList), 'utf-8',
                    playerList[turn])
        
            sel = wait_reply(playerList[turn]) - 1
            if sel >= 0 and sel < len(playerList[turn].handCards):
                card_str = cardList[playerList[turn].handCards[sel]
                        ].desc()
                i=0
                for p in playerList:
                    if i == turn:
                        inform(msgList[7]%card_str, 'utf-8', p)
                    else:
                        inform(msgList[6]%(playerList[turn].name,
                            card_str), 'utf-8', p)
                    i+=1

                playerList[turn].cast_card(playerList[turn].handCards[sel])
                continue
            elif sel == len(playerList[turn].handCards):
                i=0
                for p in playerList:
                    if i == turn:
                        inform(msgList[5], 'utf-8', p)
                    else:
                        inform(msgList[4]%playerList[turn].name, 'utf-8',
                                p)
                    i += 1
                playerList[turn].stage += 1

        #handle_msg(msg)

    # stage 4: drop cards
    elif playerList[turn].stage == 3:
        print 'It is turn for %s to drop cards.'%playerList[turn].name
        #msg = wait_reply(playerList[turn])
        #handle_msg(msg)
        i=0
        for p in playerList:
            if i == turn:
                inform(msgList[9], 'utf-8', p)
            else:
                inform(msgList[8]%playerList[turn].name, 'utf-8', p)
            i += 1
        playerList[turn].stage += 1
    else:
        playerList[turn].stage = 0
        turn += 1
        turn = turn % len(playerList)

