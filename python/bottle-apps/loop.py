import threading
import time
from bottle import get, run, redirect, request, post, static_file

@get('/index')
def index():
    return static_file("loop-test.html", root="./")

@post('/post')
def post():
    print request.json
    print request.POST.keys()
    request.POST['sex'] = 'male'
    print request.POST.keys()
    print request.json

@get('/')
def loop():
    print request.environ.get('REMOTE_ADDR')
    for i in range(10):
        print i
        time.sleep(1)

    return '<p>Wait for 10 seconds.</p>'

run(host='0.0.0.0', port=8080)
