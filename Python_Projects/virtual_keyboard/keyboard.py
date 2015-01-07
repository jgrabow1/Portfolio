import layout
from tkinter import *

class Keyboard(Frame):
    kboard_buttons = []
    specials = ["Backspace", "Tab", "Enter", "Ctrl", "Alt", "Space"]
    caps_flag = 0
    shift_flag = 0

    def __init__(self, root, press):
        Frame.__init__(self, root)
        self.press = press
        self.createWidgets()
        self.bind("<Button-1>", self.click)

    def createWidgets(self):
        ctrl_counter = 0
        shift_counter = 0
        alt_counter = 0
        row = 0
        for tup in layout.layout:
            row = row + 1
            if row>1:
                col = 1
            else:
                col = 0
            for key, value in tup:
                if key == "CapsLock":
                    button = Button(self, text=key, command=lambda key=key: self.caps_lock(), width = 8, height = 2)
                    button.grid(row=3, column=0, columnspan=value)
                    self.kboard_buttons.append(button)
                    print("key: %s , value: %s" % (key, value))
                elif key == "Shift" and shift_counter == 0:
                    button = Button(self, text=key, command=lambda key=key: self.shift_key(), width = 8, height = 2)
                    button.grid(row=4, column=0, columnspan = 2)
                    self.kboard_buttons.append(button)
                    print("key: %s , value: %s" % (key, value))
                    shift_counter += 1
                elif key == "Shift" and shift_counter != 0:
                    button = Button(self, text=key, command=lambda key=key: self.shift_key(), width = 13, height = 2)
                    button.grid(row=row, column=col, columnspan = value)
                    self.kboard_buttons.append(button)
                    print("key: %s , value: %s" % (key, value))
                elif key in self.specials:
                    if key == "Ctrl" and ctrl_counter == 0:
                        button = Button(self, text=key, command=lambda key=key: self.press(key), width = 8)
                        button.grid(row=5, column=0, columnspan = 2)
                        self.kboard_buttons.append(button)
                        print("key: %s , value: %s" % (key, value))
                        ctrl_counter += 1
                    elif key == "Ctrl" and ctrl_counter != 0:
                        button = Button(self, text=key, command=lambda key=key: self.press(key), width = 8)
                        button.grid(row=5, column=13, columnspan = 2)
                        self.kboard_buttons.append(button)
                        print("key: %s , value: %s" % (key, value))
                        #ctrl_counter = 0
                    elif key == "Alt" and alt_counter == 0:
                        button = Button(self, text=key, command=lambda key=key: self.press(key), width = 8)
                        button.grid(row=5, column=2, columnspan = 2)
                        self.kboard_buttons.append(button)
                        print("key: %s , value: %s" % (key, value))
                        alt_counter += 1
                    elif key == "Alt" and alt_counter != 0:
                        button = Button(self, text=key, command=lambda key=key: self.press(key), width = 8)
                        button.grid(row=5, column=11, columnspan = 2)
                        self.kboard_buttons.append(button)
                        print("key: %s , value: %s" % (key, value))
                        #alt_counter = 0
                    elif key == "Space":
                        button = Button(self, text=key, command=lambda key=key: self.press(key), width = 32)
                        button.grid(row=5, column=4, columnspan = 7)
                        self.kboard_buttons.append(button)
                        print("key: %s , value: %s" % (key, value))
                    elif key == "Tab":
                        button = Button(self, text=key, command=lambda key=key: self.press(key), width = 8, height = 2)
                        button.grid(row=2, column=0, columnspan = value)
                        self.kboard_buttons.append(button)
                        print("key: %s , value: %s" % (key, value))
                    else:
                        button = Button(self, text=key, command=lambda key=key: self.press(key), width = 8, height = 2)
                        button.grid(row=row, column=col, columnspan=value)
                        self.kboard_buttons.append(button)
                        print("key: %s , value: %s" % (key, value))
                elif '\n' in key:
                    button = Button(self, text=key, command=lambda key=key: self.dual_symbol(key), width = 3)
                    button.grid(row=row, column=col, columnspan=value)
                    self.kboard_buttons.append(button)
                    print("key: %s , value: %s" % (key, value))
                else:
                    button = Button(self, text=key, command=lambda key=key: self.inner_press(key), width = 3, height = 2)
                    button.grid(row=row, column=col, columnspan=value) #columnspan=col
                    self.kboard_buttons.append(button)
                    print("key: %s , value: %s" % (key, value))
                col = col + 1

    def click(self, event):
        print("clicked at", event.x, event.y)

    def caps_lock(self):
        if self.caps_flag == 0:
            self.caps_flag = 1
        else:
            self.caps_flag = 0

    def shift_key(self):
        if self.shift_flag == 0:
            self.shift_flag = 1
        else:
            self.shift_flag = 0

    def dual_symbol(self, key):
        if self.shift_flag == 0:
            self.press(key[-1])
        else:
            self.press(key[0])
            self.shift_flag = 0

    def inner_press(self, key):
        if self.caps_flag == 0:
            if self.shift_flag == 0:
                self.press(key.lower())
            else:
                self.press(key)
                self.shift_flag = 0
        else:
            if self.shift_flag == 0:
                self.press(key)
            else:
                self.press(key.lower())
                self.shift_flag = 0



def press(key):
    print(key)

root = Tk()
root.title('Keyboard Module Self-Test')
kbd = Keyboard(root, press)
kbd.grid()
root.mainloop()




