from OpenSSL.crypto import *
import base64

data = "abcdefghijkl12345678"
digest = "sha1"
key_file = open("cert/secure2.key")
key_buffer = key_file.read()
pkey = load_privatekey(FILETYPE_PEM, key_buffer)
result = sign(pkey, data, digest)
packet = data + result
print len(packet)
b64packet = base64.b64encode(packet)
print b64packet
print len(b64packet)

import httplib
import urllib, urllib2

# request_string = "/verify?m=" + packet
# request_in_url = urllib.quote(request_string)
parameters = {"message": b64packet}
data = urllib.urlencode(parameters)
conn = httplib.HTTPConnection("localhost:8080");
conn.request(method="POST", url="/verify", body=data);
r1 = conn.getresponse();
print r1.status, r1.reason
data1 = r1.read()
conn.close()
print data1

# url="http://localhost:8080/verify"
# request = urllib2.Request(url,data)
# response = urllib2.urlopen(request)
# print response.read()
