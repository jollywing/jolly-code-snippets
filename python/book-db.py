
books = []

def insertbook():
    title = input('Input the book title:')
    author = input('Input the book author:')
    year = input('Input the publish year:')
    while True:
        rate = input('Input the rating (1 - 5):')
        if rate.isdecimal():
            rate = int(rate)
            if rate >= 1 and rate <= 5:
                break

    bookentry = {}
    bookentry['title'] = title
    bookentry['author'] = author
    bookentry['year'] = year
    bookentry['rate'] = rate
    books.append(bookentry)

    input('Insert success, press any key to continue ...')
    mainUI()

def listbook():
    i = 0
    for book in books:
        print('{0}: {1}\t{2}\t{3}\t{4}'.format(i, book['title'], book['author'], book['year'], book['rate']))
        i += 1

    input('\npress any key to continue ...')
    mainUI()

def deletebook():
    while True:
        id = input("Input a id to delete, or input 'x' to cancel: ")
        if id.isdecimal():
            id = int(id)
            if id >= 0 and id < len(books):
                del books[id]
                break
        elif id == 'x':
            break

    mainUI()

def mainUI():
    # TODO: clear screen
    print('There are {0} books in database'.format(len(books)))

    print('1. Insert\n2. List\n3. Search\n4. Update\n5. Delete\n6. Quit')
    selection = input('What do you want to do?')
    if not selection.isdecimal():
        print('Input a digital (1 - 5), please.')
        input('press any key to continue ...')

    if selection == '1':
        insertbook()
    elif selection == '2':
        listbook()
    elif selection == '3':
        searchbook()
    elif selection == '4':
        updatebook()
    elif selection == '5':
        deletebook()
    else:
        exit()
    
mainUI()
