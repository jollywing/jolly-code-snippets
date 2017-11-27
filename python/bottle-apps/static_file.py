# encoding: utf-8

from bottle import static_file, route, run, error

# try http://localhost:8080/images/stock-index.png
@route('/images/:filename#.*.png#')
def send_image(filename):
    return static_file(filename, root='./static', mimetype = 'image/png')

# try http://localhost:8080/download/stock-index.png
@route('/download/:filename')
def download(filename):
    return static_file(filename, root='./static', download=filename)

# try http://localhost:8080/static/1.html
@route('/static/:filename')
def server_static(filename):
    # root 目录要使用相对路径
    return static_file(filename, root='./static/')

# try http://localhost:8080/static/2.html
@error(404)
def error404(error):
    return '404 error, nothing here, sorry!'

run(host='localhost', port=8080)
