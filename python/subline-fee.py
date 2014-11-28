# Python 2
# given single way price and day count, Caculate the new cost of subway.

import sys

def new_cost(price, days):
    sum = 0
    for i in range(days * 2):
        if sum > 150:
            sum += price * 0.5
        elif sum > 100:
            sum += price * 0.8
        else:
            sum += price
    return sum

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print 'Usage: %s <price> <days>' % (sys.argv[0],)
        exit()

    try:
        price = float(sys.argv[1])
        days = int(sys.argv[2])
        print 'Single price: %f\nDays: %d' % (price, days)
        print 'Totol cost per month: %f' %(new_cost(price, days),)
    except ValueError, e:
        print str(e)

# 200.9
