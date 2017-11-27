from bottle import route, abort, run, redirect

# try http://localhost:8080/admin
@route('/admin')
def restricted():
    abort(401, 'Sorry, access denied.')

# try http://localhost:8080/manage
@route('/manage')
def wrong():
    redirect('/admin')

run(host='localhost', port=8080)
