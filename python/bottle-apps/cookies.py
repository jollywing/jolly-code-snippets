from bottle import route, run, request, response, static_file

@route('/index.html')
def index():
    return static_file('cookies.html', root='./static/')

@route('/hello')
def hello_again():
    if request.get_cookie('visited'):
        return 'Welcome back! Nice to see you again'
    else:
        response.set_cookie('visited','yes')
        response.set_cookie('max_age', 600)
        return 'Hello there! Nico to meet you!'

# you must add method = "POST", otherwise you will get error 405:
# Method not allowed.
@route('/login', method="POST")
def login():
    username = request.forms.get('username')
    password = request.forms.get('password')
    if check_user_credentials(username, password):
        response.set_cookie('account', username, secret='some-sceret-key')
        return 'Welcome {}'.format(username)
    else:
        return "You're not allowed."

@route('/restricted')
def restricted_area():
    username = request.get_cookie('account', secret='some-secret-key')
    if username:
        return 'Hello {}'.format(username)
    else:
        return 'You are not logged in.'

def check_user_credentials(username, password):
    if username == "admin" and password == "admin":
        return True
    else:
        return False

run(host='localhost', port=8080)
