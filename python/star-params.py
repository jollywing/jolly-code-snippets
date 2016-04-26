
# -*- encoding: utf-8 -*-

# 一个星号表示接收的参数作为元组来处理
def sum(*args):
    total = 0
    for i in args:
        total = total + i
    return total

def list_stocks(**kvpairs):
    print kvpairs
    for p in kvpairs.items():
        print p[0], " price: ", p[1]

if __name__ == "__main__":
    print sum(1, 3, 5, 7, 9)
    list_stocks(volvo=10.00, haval=5.01)
    list_stocks(honda=9.10, audi=12.38)
