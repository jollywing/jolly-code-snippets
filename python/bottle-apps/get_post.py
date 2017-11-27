
from bottle import get, post, request, run

#@route('/login')
@get('/login')
def login_form():
    return '''<form method = "POST">
    <input name="name" type="text" />
    <input name="password" type="password" />
    <input type="submit" value="Login" />
    </form>'''

#@route('/login', method = 'POST')
@post('/login')
def login():
    name = request.forms.get('name')
    password = request.forms.get('password')
    if check_login(name, password):
        return '<p>Your login was correct</p>'
    else:
        return '<p>Login failed</p>'

def check_login(name, password):
    return True

run(host='localhost', port=8080)
