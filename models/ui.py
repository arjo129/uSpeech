#!/usr/bin/python3

import tkinter


def hello():
	pass
top = tkinter.Tk()
menu = tkinter.Menu(top)

# The file menu for the interface
filemenu = tkinter.Menu(menu, tearoff=0)
filemenu.add_command(label="Open existing recording", command=hello)
filemenu.add_command(label="New recording", command=hello)
filemenu.add_command(label="Save", command=hello)
menu.add_cascade(label="File", menu=filemenu)

# The edit menu
emenu = tkinter.Menu(menu, tearoff=0)
emenu.add_command(label="Undo", command=hello)
emenu.add_command(label="Redo", command=hello)
menu.add_cascade(label="Edit", menu=emenu)

# The labels menu
lmenu = tkinter.Menu(menu, tearoff=0)
lmenu.add_command(label="Manage labels...", command=hello)
lmenu.add_command(label="Load label file...", command=hello)
menu.add_cascade(label="Labels", menu=lmenu)

# The graph canvas
w = tkinter.Canvas(top, width=600, height=100)
w.pack(side=tkinter.LEFT, anchor=tkinter.N)

# The label box
listbox = tkinter.Listbox(top)
listbox.pack(side=tkinter.RIGHT)
b = tkinter.Button(top, text="Mark", command=hello)
b.pack(side=tkinter.RIGHT, anchor=tkinter.S)
top.config(menu=menu)

top.mainloop()
