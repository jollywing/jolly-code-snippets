# usage: python yaHello.py
# encoding: utf-8

from bottle import Bottle, run

app = Bottle()

@app.route('/hello')
def hello():
    return "Hello World!"

@app.route('/')
@app.route('/index.html')
def index():
    return hello()

# id 只允许是0-9组成的数字，任意多位
@app.route('/article/:id#[0-9]+#')
def view_object(id):
    return 'Object ID: {}'.format(id)

run(app, host='localhost', port=8080)
