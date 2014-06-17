
class ShortInputException(Exception):
    def __init__(self, length, atleast):
        Exception.__init__(self)
        self.length = length
        self.atleast = atleast

    # x = ShortInputException(n1, n2); str(x) will return this string
    # print(x) will output this string
    def __str__(self):
        return 'Your input length is {}, shorter than {}.'.format(self.length, self.atleast)

    def __getitem__(self, k):
        if k == 0:
            return self.length
        elif k == 1:
            return self.atleast
        else:
            raise IndexError()

# if __name__ = main:
s = input('Input something:')

try:
    if len(s) < 3:
        # use raise to throw exception.
        # which to throw is a instance of subclass of Exception or Error
        raise ShortInputException(len(s), 3)
# catch exception use except, where e is instance of ShortInputException
except ShortInputException as e:
    print(e)
    try:
        print(e[0])
        print(e[2])
    except:
        print('something strange happened.')
else:
    print(s)
finally:
    print('whatever I will say something.')
