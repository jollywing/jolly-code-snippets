# 2013-06-14
# python 2

print("Welcome!")
goal = 50
count = 0
while True:
    try:
        g = input("Guess the number:")
        guess = int(g)
        count += 1
        if guess == goal:
            print("You got it!!!")
            break
        elif guess > goal:
            print('Larger!')
        else:
            print('Smaller!')
    except Exception, e:
        print str(e)
        print 'Please input a number!'

print 'You use %d times to succeed!' % count
