# encoding: utf-8

from bottle import static_file, route, run, error

# try http://localhost:8080/download/stock-index.png
@route('/download/:filename')
def download(filename):
    create_file(filename)
    return static_file(filename, root='./', download=filename)

def create_file(filename):
    f = open("./" + filename, 'w')
    f.write('@' * 2048)
    f.close()

run(host='localhost', port=8080)
