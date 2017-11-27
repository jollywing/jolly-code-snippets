# usage: python hello.py
# then access http://localhost:8080/hello/xxx with your browser.

import bottle

# if you access /hello/xxx, then will return the result of index(xxx).
@bottle.route('/hello/:name')
def index(name = 'World'):
    return '<p>Hello, {}!</p>'.format(name)

@bottle.route('/index.html')
def welcome():
    return '<b>You are welcome!</b>'

@bottle.route('/')
def default():
    return '''
try to access /index.html, and hello/xyz '''


bottle.run(host='localhost', port=8080)
