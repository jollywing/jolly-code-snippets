from socket import *
import string

# new a socket
recv_soc = socket(AF_INET, SOCK_STREAM)
# bind
listen_addr = ('127.0.0.1', 8000)
recv_soc.bind(listen_addr)
# listen
recv_soc.listen(0)
# accept
conn, sender_addr = recv_soc.accept()
print sender_addr, "connected."
# receive
file_head = conn.recv(512)
print file_head
elements = string.split(file_head, ',')
file_name = elements[0]
file_size = int(elements[1])

fp = open(file_name + '.bak', 'wb')

remain = file_size

while True:
    s = conn.recv(512)
    print "received %d bytes." % len(s)
    if len(s) == 0:
        break
    fp.write(s)
    remain = remain - len(s)
    if remain <= 0:
        break

print "file transfer finished."
fp.close()
conn.close()
recv_soc.close()
