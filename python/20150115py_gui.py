# python 3

from tkinter import *
top = Tk()
# setup title
top.title('Hello, python')
# setup size
top.geometry('400x500')
l = Label(top, text='Hello, python', bg='skyblue')
l.pack(fill = Y)
top.mainloop()
