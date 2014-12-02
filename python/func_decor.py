
def dec(func):
    print 'find the max'
    return func

@dec
def max(a, b):
    if a > b:
        return a
    else:
        return b

# Now max = dec(max)
max(3,4)

def make_deco(s):
    print 'making deco ....'
    return dec

@make_deco('making decoration')
def say_hello():
    print 'hello, world!'

# say_hello = make_deco('making decoration')(say_hello)
say_hello()
