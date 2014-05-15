from socket import *
import thread
import sys
from time import ctime, sleep

from game import *



def heartbeat():
    hbSock = socket(AF_INET, SOCK_DGRAM)
    addr = (SERV_IP, HB_PORT)
    while(True):
        hbSock.sendto('LIVE', addr)
        sleep(HB_INTERVAL)

def receive():
    recvSock = socket(AF_INET, SOCK_DGRAM)
    addr = ('', CLIENT_PORT)
    recvSock.bind(addr)
    while(True):
        u_data, addr = recvSock.recvfrom(BUFSIZE)
        cmd = u_data.split()
        if cmd[0] == 'PICKCARD':
            pass
            
        elif cmd[0] == 'CASTCARD':
            pass

        smartPrint(u_data, CODEC, 1)


if len(sys.argv) < 2:
    print 'Usage: python client.py username'
    sys.exit()

ADDR = (SERV_IP, SERV_PORT)

cliSock = socket(AF_INET, SOCK_DGRAM)
cliSock.sendto('JOIN %s'% sys.argv[1], ADDR)
print 'connecting game server ... '
data, ADDR=cliSock.recvfrom(BUFSIZE)

if data == 'JOIN_OK':
    print 'join success! wait other players ...'
    print 'You can type START to start the game.'

    thread.start_new_thread(receive, ())
    thread.start_new_thread(heartbeat, ())

    while(JOINING):
        input = raw_input('> ')

        u_input = unicode(input, in_codec).encode(CODEC)
        cliSock.sendto(u_input, ADDR)

    while(GAME_RUNNING):
        sleep(1)




