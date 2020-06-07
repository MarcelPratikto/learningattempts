# import tkinter into this program,
# but calling its contents require calling tkinter first (ex: tkinter.Tk())
import tkinter
from tkinter import ttk
# the below method also imports,
# but you no longer need to call the module first
#(no need to type tkinter.constants.CENTER, just type CENTER)
from tkinter.constants import *

#-------------------------------------------------------------------------------
# source: https://docs.python.org/3/library/tkinter.html#tkinter-modules
# class to create a frame (contents of window)
class Application(tkinter.Frame):
    message = "AAA"
    def __init__(self, master=None):
        super().__init__(master)
        self.master = master
        self.pack()
        self.create_widgets()

    def create_widgets(self):
        # create a button to print hello world
        self.hi_there = tkinter.Button(self)
        self.hi_there["fg"] = "blue"
        self.hi_there["text"] = "Hello World\n(click me)"        
        self.hi_there["command"] = self.say_hi
        self.hi_there.pack(side = "top")
        # create a label
        style = ttk.Style()
        style.configure("BW.TLabel", foreground="black", background="white")
        self.label = ttk.Label(text = self.message, style = "BW.TLabel")
        self.label.pack(side = "right")
        # create a button to quit program
        self.quit = tkinter.Button(self, text="QUIT", fg="red", bg="black",
                                   command=self.master.destroy)
        self.quit.pack(side="bottom")        

    # function that print a string
    def say_hi(self):
        self.message = "hi there"        

#-------------------------------------------------------------------------------
# creates a window object
root = tkinter.Tk()
# fill the window, assign to app, then run it
app = Application(master=root)
app.mainloop()

# TODO figure out a way to refresh canvas
# after every button presses (or after every key presses when typing)
# or at a set interval (ex: 60 times per second)
