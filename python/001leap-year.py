
def leap_year(y):
    if (y % 400 == 0) or (y % 4 == 0 and y % 100 != 0):
        return True
    else:
        return False

print("Practice 1:")

if leap_year(2010):
    print("This year is leap year!")
else:
    print("This year is not leap year!")


def prime_number(u):
    l = range(u+1)
    print('{0}'.format(l))

print("Practice 2:")

prime_number(100)


