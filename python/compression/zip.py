import zlib

file_name = 'temp'

# open file
fp = open(file_name, 'r')
content = fp.read()
fp.close()

fp = open('temp.data', 'w')

try:
    # compress
    result = zlib.compress(content)
except zlib.error:
    print "compress error!"
    fp.close()
    exit()

fp.write(result)
fp.close()

fp = open('temp.data', 'r')
content = fp.read()
fp.close()

try:
    result = zlib.decompress(content)
except zlib.error:
    print "decompress error!"
    exit()

fp = open('temp.1', 'w')
fp.write(result)
fp.close()
