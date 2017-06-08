#!/usr/bin/python3

import tkinter
import random
import math
import pyaudio
import threading

CHUNK = 1024
FORMAT = pyaudio.paInt16
CHANNELS = 1
RATE = 44100
p = pyaudio.PyAudio()

stream = p.open(format=FORMAT,
		channels=CHANNELS,
		rate=RATE,
		input=True,
		frames_per_buffer=CHUNK)
def hello():
	pass

class popupWindow(object):
	def __init__(self,master):
		self.top=tkinter.Toplevel(master)
		self.l=tkinter.Label(self.top,text="Name of label")
		self.l.pack()
		self.e=tkinter.Entry(self.top)
		self.e.pack()
		self.b=tkinter.Button(self.top,text='Add',command=self.cleanup)
		self.b.pack()
	def cleanup(self):
		self.value=self.e.get()
		self.top.destroy()
 
class UI:
	def recording_thread(self):
		self.buffer = [[],[]]
		while self.recording_mode == "recording":
			readings = stream.read(CHUNK)
			prev = 0
			total = 0
			for i in readings:
				total+= 100*abs(float(i)-prev)
				prev = float(i)
			recording = map(abs,readings)
			power = sum(recording)
			self.buffer[0].append(power)
			self.buffer[1].append(total/power)
		print(len(self.buffer[0]))
	def add_label(self):
		my_popup = popupWindow(self.top)
		self.top.wait_window(my_popup.top)
		self.listbox.insert(tkinter.END, my_popup.value)
	def button_clicked(self):
		if self.recording_mode == "standby":
			self.buttontxt.set("Stop")
			self.recording_mode = "recording"
			threading.Thread(target=self.recording_thread).start()
		elif self.recording_mode == "recording":
			self.buttontxt.set("Start recording")
			self.recording_mode = "standby"
			self.update_graph()
	def add_marker(self, event):
		self.markers.append((event.x,self.listbox.get(self.listbox.curselection())))
		self.plot.create_line(event.x, 0, event.x, 100,fill="black")
	def update_graph(self):
		self.plot.delete(tkinter.ALL)
		colors = ["red","blue"]
		i = 0
		for line in self.buffer:
			max_val = max(line)
			min_val = min(line)
			index = 0
			prev_val = 0
			line_color = colors[i]
			i+=1
			for item in line:
				self.plot.create_line(index, prev_val,
                                                      index+600/len(line),
                                                      100-90*(item-min_val)/(max_val-min_val), fill=line_color)
				index+=600/len(line)
				prev_val = 100-90*(item-min_val)/(max_val-min_val)
		self.plot.update()      
	def record(self):
		self.update_graph()
		self.recording_mode = "standby"
		self.buttontxt.set("Start Recording...")
	def __init__(self):
		self.markers = []
		self.buffer = [[math.sin(math.pi/20*x) for x in range(200)],
                               [math.cos(math.pi/20*x) for x in range(200)]]
		self.recording_mode = "Marking"
		self.top = tkinter.Tk()
		self.menu = tkinter.Menu(self.top)
		# The file menu for the interface
		filemenu = tkinter.Menu(self.menu, tearoff=0)
		filemenu.add_command(label="Open existing recording", command=hello)
		filemenu.add_command(label="New recording", command=self.record)
		filemenu.add_command(label="Save", command=hello)
		self.menu.add_cascade(label="File", menu=filemenu)

		# The edit menu
		emenu = tkinter.Menu(self.menu, tearoff=0)
		emenu.add_command(label="Undo", command=hello)
		emenu.add_command(label="Redo", command=hello)
		self.menu.add_cascade(label="Edit", menu=emenu)

		# The labels menu
		lmenu = tkinter.Menu(self.menu, tearoff=0)
		lmenu.add_command(label="Add label...", command=self.add_label)
		lmenu.add_command(label="Delete label...", command=hello)
		lmenu.add_command(label="Load label file...", command=hello)
		self.menu.add_cascade(label="Labels", menu=lmenu)

		# The graph canvas
		self.plot = tkinter.Canvas(self.top, width=600, height=100)
		self.plot.pack(side=tkinter.LEFT, anchor=tkinter.E)
		self.plot.bind("<Button-1>", self.add_marker)
		
		# The label box
		self.listbox = tkinter.Listbox(self.top)
		self.listbox.insert(tkinter.END, "None")
		self.listbox.pack(side=tkinter.RIGHT)
		
		# The button
		self.buttontxt = tkinter.StringVar()
		self.buttontxt.set("Mark")
		self.button = tkinter.Button(self.top, textvariable=self.buttontxt, command=self.button_clicked)
		self.button.pack(side=tkinter.RIGHT, anchor=tkinter.S)
		# Add the menus
		self.top.config(menu=self.menu)
		# Perform the main loop
		self.top.mainloop()


if __name__ == "__main__":
	UI()
