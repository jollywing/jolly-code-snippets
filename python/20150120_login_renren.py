import urllib, urllib2, cookielib

url_login = "http://www.renren.com/PLogin.do"
login_data = {"email": "jiqingwu@gmail.com", "password": "800zgyfjch925"}

cj = cookielib.CookieJar()
opener = urllib2.build_opener(urllib2.HTTPCookieProcessor(cj))
resp = opener.open(url_login, urllib.urlencode(login_data))

f = open('result.html', 'w');

for line in resp:
    f.write(line)

f.close()
