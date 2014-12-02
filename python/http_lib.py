
import httplib
import sys

def check_web_server(host, port=80, path='/'):
    h = httplib.HTTPConnection(host, port)
    h.request('GET', path)
    resp = h.getresponse()
    print 'HTTP response:'
    print '    status:', resp.status
    print '    reason:', resp.reason
    print 'HTTP Headers:'
    for hdr in resp.getheaders():
        print '    %s : %s' % hdr

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print 'Usage: %s <url>' % sys.argv[0]
        exit()
    check_web_server(sys.argv[1])
