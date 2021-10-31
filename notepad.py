# Creating a text-editor(Notepad) using tkinter module in python
from tkinter import *
from tkinter.messagebox import *
from tkinter.filedialog import *
import os

# Basic tkinter setup
root = Tk()
root.title("Untitled-Document")
root.wm_iconbitmap("notepad_image.png")
root.geometry("600x700")

# New file
def newfile():
    global file
    # Title of new file is given 
    root.title("Untitled-Notepad")
    file = None
    # Delete all that is currently present in textarea from 0th character of first line till end
    textarea.delete(1.0,END)

# Open a file
def openfile():
    global file
    file = askopenfilename(defaultextension=".txt",filetypes=[("All Files","*.*"),("Text Documents",".txt")])
    # If there is no file to open 
    if file == "":
        file = None
    else:
        textarea.delete(1.0,END)
        # Open the file
        f = open(file,"r")
        # Insert in textarea what is present inside file
        textarea.insert(1.0,f.read())
        # Close the file
        f.close()
        root.title(os.path.basename(file)+" - Notepad")

# Save the file
def savefile():
    global file
    # If there is a new file
    if file == None:
        file = asksaveasfilename(initialfile="Untitled.txt",defaultextension=".txt",filetypes=[("All Files","*.*"),("Text Documents",".txt")])
        # If no file is selected
        if file == "":
            file = None
        # Save as new file
        else:
            f = open(file,"w")
            f.write(textarea.get(1.0,END))
            f.close()
            root.title(os.path.basename(file)+" - Notepad")

    # The content will be replaced and file will be saved  
    else:
        f = open(file,"w")
        f.write(textarea.get(1.0,END))
        f.close()

# Exit from window
def exitfile():
    root.destroy()

# Cut text inside textarea
def cutfile():
    textarea.event_generate(("<<Cut>>"))

# Copy text inside textarea
def copyfile():
    textarea.event_generate(("<<Copy>>"))

# Paste text inside textarea
def pastefile():
    textarea.event_generate(("<<Paste>>"))

def aboutnotepad():
    showinfo("Notepad","Notepad by Mansi")

# Add textarea
textarea = Text(root,font="lucida 13")
# Pointing to the file the we are considering. Initially no file is opened
file = None
textarea.pack(expand = True,fill = BOTH)

# Add a horizontal menu in the root
menubar = Menu(root)

# file menu is created inside menubar
filemenu = Menu(menubar,tearoff = 0)
# To open new file
filemenu.add_command(label = "New",command = newfile)
# to open already existing file
filemenu.add_command(label = "Open",command = openfile)
# To save current file
filemenu.add_command(label = "Save",command = savefile)
# To add a line
filemenu.add_separator()
# To exit
filemenu.add_command(label = "Exit",command = exitfile)
menubar.add_cascade(label = "File",menu = filemenu)
# file menu ends


# edit menu is created
editmenu = Menu(menubar,tearoff = 0)
# To give a feature of cut 
editmenu.add_command(label = "Cut",command = cutfile)
# To give a feature of copy  
editmenu.add_command(label = "Copy",command = copyfile)
# To give a feature of paste
editmenu.add_command(label = "Paste",command = pastefile)
menubar.add_cascade(label = "Edit",menu = editmenu)
# edit menu ends


# help menu is created
helpmenu = Menu(menubar,tearoff = 0)
helpmenu.add_command(label = "About Notepad",command = aboutnotepad)
menubar.add_cascade(label = "Help",menu = helpmenu)
# help menu ends
root.config(menu = menubar)

# Adding scrollbar
scroll = Scrollbar(textarea)
scroll.pack(fill = Y,side = RIGHT)
scroll.config(command = textarea.yview)
textarea.config(yscrollcommand = scroll.set)

root.mainloop()
