# No module named 'Tkinter'
# from Tkinter import *

# NOTE!! if your python file is named tkinter.py, you'll fuck yourself
from tkinter import *

root = Tk()

# _tkinter.TclError: unknown option "-text"
# root['text'] = 'Try Tkinter'

btn = Button(root)

btn['text'] = 'Hello, Tkinter!' # set button text
btn['command'] = exit
btn.pack(side='top')                      # you need this line to show button

# you need this line to show window
root.mainloop()
