#!/usr/bin/env python
# vim:foldmethod=indent
# create: 2011-01-17 

import pygtk
pygtk.require('2.0')
import gtk
from epss import * 

class EpssGui:
    def epss(self, widget, data=None):
        f = open('epss.py')
        exec f

    def delete_event(self, widget, event, data=None):
        print "delete event occurred"
        return False

    def destroy(self, widget, data=None):
        gtk.main_quit()

    def __init__(self):
        self.window = gtk.Window(gtk.WINDOW_TOPLEVEL)
        self.window.connect("delete_event", self.delete_event)
        self.window.connect("destroy", self.destroy)
        self.window.set_border_width(10)

        self.button = gtk.Button("Run EPSS")
        self.button.connect("clicked", self.epss, None)
        #self.button.connect_object("clicked",\
                #gtk.Widget.destroy, self.window)
        self.window.add(self.button)
        self.button.show()
        self.window.show()
    def main(self):
        gtk.main()

if __name__=="__main__":
    hello = EpssGui()
    hello.main()
