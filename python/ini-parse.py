''' This script parse a ini config file.
Author: Wu Jiqing
Create: 2014-05-15
'''

# If no mode is specified, 'r'ead mode is assumed.
# help(open) to check more modes
f = open('test.ini', 'r')
config = {}

while True:
    line = f.readline()
    if len(line) == 0:
        break;
    # help(str) to check how to handle str
    s = line.partition('=')
    key = s[0].strip()
    value = s[2].strip()
    if len(key) > 0:
        config[key] = value

f.close()

for key, value in config.items():
    print('{0}:{1}'.format(key, value))
