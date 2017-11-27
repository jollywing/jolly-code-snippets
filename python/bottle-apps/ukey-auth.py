from bottle import get, post, request, run
import OpenSSL, urllib
import base64
# try http://localhost:8080/admin
@get('/')
def hello():
    return "Welcome to CS2C measuring server!"

@post('/verify')
def verify():
    b64message = request.POST.get('message', '')
    if b64message == '':
        return "Verify failed!\n"
    message = base64.b64decode(b64message)
    sn = message[:16]
    print "sn:", sn
    data = message[16:36]
    print "data:", data
    sig = message[36:]
    print "signature:", sig
    cert_file = open("cert/secure2.crt")
    cert_buffer = cert_file.read()
    cert = OpenSSL.crypto.load_certificate(OpenSSL.crypto.FILETYPE_PEM, cert_buffer)
    try:
        OpenSSL.crypto.verify(cert, sig, data, "md5")
    except OpenSSL.crypto.Error:
        return "Verify failed!"
    else:
        return "Verify Succeed!"

# try http://localhost:8080/manage
# @route('/manage')
# def wrong():
#     redirect('/admin')

run(host='0.0.0.0', port=8080)
