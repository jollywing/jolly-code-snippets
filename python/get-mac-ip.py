# 2016-01-22 Fri

import uuid, socket

def get_localhost_mac():
    hex_string = uuid.UUID(int = uuid.getnode()).hex[-12:]
    return ":".join([hex_string[e:e+2] for e in range(0, 11, 2)])

def get_localhost_ip():
    hname = socket.gethostname()
    fqdn = socket.getfqdn(hname)
    return socket.gethostbyname(fqdn)

if __name__ == "__main__":
    print "local host mac address: ", get_localhost_mac()
    print "local host ip address: ", get_localhost_ip()
