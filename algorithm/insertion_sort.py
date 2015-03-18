
# Knowledges:
# insertion 
# function define
# for loop
# range()
# if statement
# swap 2 objects
# print

def insertion_sort(a):
    for i in range(1, len(a)):
        for j in range(i, 0, -1):
            if a[j] < a[j-1]:
                t = a[j]
                a[j] = a[j-1]
                a[j-1] = t
            else:
                break

a = [1.1, -10, -300.33, 1E-2]
print('the given list is {}'.format(a))
insertion_sort(a)
print('After insertion sorting, it become into {}.'.format(a))

names = ["Wu", "Li", "Zhang", "Zhao", "Wan", "Cheng"]
print('the given list is {}'.format(names))
insertion_sort(names)
print('After insertion sorting, it become into {}.'.format(names))
