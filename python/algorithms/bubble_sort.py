
#. bubble sort
#. for loop
#. function definition
#. the length of array: len(list)

# Use bubble sort to sort a list
# Whether the element is number or string, this function worked.
# a is the list to sort
def sort(a):
    # NOTICE: range(1, 5) generates [1, 2, 3, 4]
    # but range() generates only 1 number each time
    # If you want to get the whole list, you can use list(range())
    for i in range(len(a), 1, -1):
        for j in range(0, i - 1):
            if a[j] > a[j+1]:
                t = a[j]
                a[j] = a[j+1]
                a[j+1] = t

a = [1, 9, 7, 5, 10]
print("The given list is {}".format(a))
sort(a)
print("After sorting, it become {}".format(a))

b = [1.1, 3.0, -10, 100.9, 0]
print("The given list is {}".format(b))
sort(b)
print("After sorting, it become {}".format(b))

c = ['John', 'Jam', 'Mike', 'Leo']
print("The given list is {}".format(c))
sort(c)
print("After sorting, it become {}".format(c))

print("In fact, the list has sort() method.")
