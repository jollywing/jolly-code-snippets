
import locale
import curses

locale.setlocale(locale.LC_ALL, '')
code = locale.getpreferredencoding()

screen = curses.initscr()
curses.noecho()
curses.cbreak()
screen.box()
y,x = screen.getmaxyx()

text = "This is a TEst."
cur_x = int(x / 2 - len(text)/2)
cur_y = int(y / 2)
screen.addstr(cur_x, cur_y, text)
screen.refresh()

c = screen.getch()
curses.echo()
curses.nocbreak()
curses.endwin()
