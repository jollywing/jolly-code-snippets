from bottle import get, post, static_file, run

@get('/add_record')
def add_record_page():
    return static_file('add-record.html', root='.')

@post('/add_record')
def handle_new_record():
    pass

run(host='localhost', port=8080)
