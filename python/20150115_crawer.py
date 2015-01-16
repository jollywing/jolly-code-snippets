import urllib2
import re
page = urllib2.urlopen(r'http://www.baidu.com').read()
email_patt = re.compile(r'\w+@\w+\.\w{2,3}')
match = email_patt.findall(page)
print match
# start = page.find('<body>')
# start += 6
# end = page.find('</body>')
# print page[start:end]
