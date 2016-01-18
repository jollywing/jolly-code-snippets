from socket import *
import os

# new a socket
soc = socket(AF_INET, SOCK_STREAM)
# connect
server_addr = ('127.0.0.1', 8000)
soc.connect(server_addr)
# send file head
file_name = 'temp.txt'
file_size = os.path.getsize(file_name)
file_head_info = "%s,%d" % (file_name, file_size)
soc.send(file_head_info)
print "send file head info: ", file_head_info

# send file data
fp = open(file_name)
content = fp.read()
print "file data: ", content

total_sent = 0
while total_sent < file_size:
    sent = soc.send(content[total_sent:])
    total_sent = total_sent + sent
    print "%d bytes sent, total sent: %d" % (sent, total_sent)

print "file transfer finished."

# close socket
soc.close()
