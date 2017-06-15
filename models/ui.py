#!/usr/bin/python3

import tkinter
from tkinter import filedialog
import random
import math
import pyaudio
import threading
import wave
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
	def open_dialog(self):
		f = filedialog.askopenfilename(defaultextension=".wav")
		if f == "":
			return
		my_file = wave.open(f,"r")
		
	def save_dialog(self):
		f = filedialog.asksaveasfile(defaultextension=".speech")
		if f is None:
			return
		current_marker = 0
		units_per_marker = len(self.buffer[0])/600
		for i in range(len(self.buffer[0])):
			if current_marker < len(self.markers)-1:
				if i/units_per_marker >= self.markers[current_marker+1][0]:
				     current_marker += 1
			label = self.markers[current_marker][1]
			f.write(str(self.buffer[0][i]) + "\t" + str(self.buffer[1][i]) + "\t" + label + "\n")
		f.close()
		

	def recording_thread(self):
		self.buffer = [[],[]]
		while self.recording_mode == "recording":
			readings = stream.read(CHUNK)
			prev = 0
			total = 0
			for i in readings:
				total+= 100*abs(float(i)-prev)
				prev = float(i)
			recording = map(lambda x: abs(x-sum(readings)/len(readings)),readings)
			power = sum(recording)
			print(sum(readings)/len(readings))
			self.buffer[0].append(power)
			self.buffer[1].append(total/power)
		
		
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
		self.stack.append(self.markers.copy())
		del self.stack[0]
		self.markers.append((event.x,self.listbox.get(self.listbox.curselection())))
		self.update_graph()

		
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
		for x, label in self.markers:
			self.plot.create_line(x, 0, x, 100,fill="black")
		self.plot.update()

		
	def record(self):
		self.update_graph()
		self.recording_mode = "standby"
		self.buttontxt.set("Start Recording...")

	def undo(self):
		self.rstack.append(self.markers.copy())
		del self.rstack[0]
		self.markers = self.stack.pop()
		self.update_graph()

	def redo(self):
		self.stack.append(self.markers.copy())
		del self.stack[0]
		self.markers = self.rstack.pop()
		self.update_graph()
		
	def __init__(self):
		self.stack = [[],[],[]]
		self.rstack = [[],[],[]]
		self.markers = [(0,"None")]
		self.buffer = [[math.sin(math.pi/20*x) for x in range(200)],
			       [math.cos(math.pi/20*x) for x in range(200)]]
		self.recording_mode = "Marking"
		self.top = tkinter.Tk()
		self.top.wm_title("uspeech Research Sandbox 0.0.1")
		self.menu = tkinter.Menu(self.top)
		# The file menu for the interface
		filemenu = tkinter.Menu(self.menu, tearoff=0)
		filemenu.add_command(label="New recording", command=self.record)
		filemenu.add_command(label="Save", command=self.save_dialog)
		filemenu.add_command(label="Import Recording", command=self.open_dialog)
		self.menu.add_cascade(label="File", menu=filemenu)

		# The edit menu
		emenu = tkinter.Menu(self.menu, tearoff=0)
		emenu.add_command(label="Undo", command=self.undo)
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
