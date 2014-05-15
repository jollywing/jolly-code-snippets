
import sys

BUFSIZE = 1024
SERV_IP= '202.197.22.18'
SERV_PORT=21000
CLIENT_PORT = 21555
HB_PORT = 21566
HB_INTERVAL = 0.3
HB_TIMEOUT = 0.5
MAX_SILENT = 2

in_codec = sys.stdin.encoding
out_codec = sys.stdout.encoding
CODEC = 'utf-8'

msgList = []
symList = []

def smartPrint( string, codec, newline ):
    if newline == 1:
        print string.decode(codec).encode(out_codec)
    else:
        print string.decode(codec).encode(out_codec),

def listToStr( list ):
    temp = ""
    for s in list:
        temp += s
        temp += '\n'
    return temp

def load_msg(filename, msg_list):
    f = open(filename, 'r')
    for eachLine in f:
        msg_list.append(eachLine)
    f.close

def load_symbol(filename, sym_list):
    f = open(filename, 'r')
    for eachLine in f:
        sym_list.append(eachLine[:-1])
    f.close

