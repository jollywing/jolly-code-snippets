# -*- encoding: utf-8 -*-

def makeHtmlTag(tag, *args, **kwds):
    def real_decorator(fn):
        css_class = " class='{0}'".format(kwds["css_class"]) \
                                     if "css_class" in kwds else ""
        def wrapped(*args, **kwds):
            return "<"+tag+css_class+">" + fn(*args, **kwds) + "</"+tag+">"
        return wrapped
    return real_decorator

@makeHtmlTag(tag="b", css_class="bold_css")
@makeHtmlTag(tag="i", css_class="italic_css")
def hello():
    return "hello world"

print hello()

# 输出：
# <b class='bold_css'><i class='italic_css'>hello world</i></b>

# 注意, long leg作为一个装饰器一定要返回一个函数。

def long_leg(fn):
    def wrapper():
        fn()
        print 'I have long legs.'
    return wrapper

# boy = long_leg(boy)
@long_leg
def boy():
    print 'I am a boy.'

boy()

def say(some):
    def saying_girl(girl):
        # 必须要定义一个函数然后返回
        def wrapper():
            girl()
            print some
        return wrapper

    return saying_girl

# beauty = say(xxx)(beauty)
@say('I have a pair of long legs.')
@say('I have black hair.')
def beauty():
    print "I'm a beautiful girl."

beauty()
