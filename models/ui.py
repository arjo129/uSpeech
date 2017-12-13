from tkinter import *
from tkinter import filedialog
from tkinter.scrolledtext import ScrolledText
import os
class MainUI(Frame):
    def __init__(self, master=None):
        Frame.__init__(self, master, width=600, height=480)
        self.data_directory = StringVar()
        self.data_directory.set("no data selected... please select directory of google_speech_data")
        self.directory_prompt = Label(self, textvariable = self.data_directory)
        self.directory_prompt.grid(row=0,column=0,sticky=W)
        self.select_dir = Button(self, text ="Change directory")
        self.select_dir.grid(row=0,column=1)
        self.select_dir.bind("<Button-1>",self.chdir)
        self.gru_label = Label(self, text = "GRU Size:")
        self.gru_label.grid(row=1,column=0,sticky=E)
        self.gru_entry = Entry(self)
        self.gru_entry.insert(0,"20")
        self.gru_entry.grid(row=1,column=1)
        self.words_label = Label(self,text = "Words to learns: (one line per word)")
        self.words_label.grid(row=2,column=0,sticky=W)
        self.words = ScrolledText(self)
        self.words.grid(row=3,column=0,columnspan=2)
        self.trainbtn = Button(self, text ="Train model")
        self.trainbtn.bind("<Button-1>",self.train)
        self.trainbtn.grid(row=4,column=1)
        self.pack(side=LEFT)
    def chdir(self, event):
        self.speech_data = filedialog.askdirectory()
        if self.speech_data:
            self.data_directory.set("Using speech data from: "+self.speech_data)
            os.chdir(self.speech_data)
    def train(self, event):
        filename = filedialog.asksaveasfilename(title = "Select file to checkpoint the model to",filetypes =(("uspeech model checkpoint","*.model"),))
        if filename:
            pass #TODO Implement training routine
root = Tk()
app =  MainUI(master=root)
menubar = Menu(root)
filemenu = Menu(menubar, tearoff = 0)
filemenu.add_command(label="Open...")
menubar.add_cascade(label="File", menu=filemenu)
root.config(menu=menubar)
app.master.title("uspeech 5.0.0 wizard")
app.mainloop()
root.destroy()
