from tkinter import *

class Spreadsheet(Frame):
    error_flag = False
    sym_table = {}
    cells = {}

    def __init__(self, root, nr=4, nc=4):
        Frame.__init__(self, root)
        self.root = root
        self.nr = nr
        self.nc = nc
        self.grid()

        self.init_array()
        self.init_sheet()
        #self.traverse()

    def init_array(self):
        self.cell_array = [[(0,0) for y in range(self.nc)] for x in range(self.nr)]


    def init_sheet(self):
        w = 20
        alpha = ["", 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']

        for row in range(self.nr):
            for col in range(self.nc):
                if col == 0:
                    #Create row labels
                    label1 = Label(root, width=1, text=alpha[row])
                    label1.grid(row=row, column=col)
                elif row == 0:
                    #Create column labels
                    label1 = Label(root, width=1, text=str(col))
                    label1.grid(row=row, column=col)
                else:
                    #Create entry object
                    entry1 = Entry(root, width=w)
                    #Place the object
                    entry1.grid(row=row, column=col)
                    #get entry and input cell into array
                    cell = "%s%s" % (alpha[row], col)
                    self.cells[cell] = entry1
                    if len(str(entry1.get())) >= 1 or isinstance(entry1.get(), int):
                        val = eval(entry1.get(), {}, self.sym_table)
                    else:
                        val = 0
                    self.input_array(entry1.get(), val, col, row)
                    #Bind the object to left mouse click
                    entry1.bind('<Button-1>', lambda e, cell=cell: self.click(e, cell))
                    #Bind the object to enter key
                    entry1.bind('<Return>', lambda e, cell=cell: self.key_r(e, cell))
                    #Bind the object to tab key
                    entry1.bind('<Tab>', lambda e, cell=cell: self.key_r(e, cell))

    def convert_alpha(self, letter):
        num = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26]
        alph = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']
        i = alph.index(letter)
        #print("number from conversion: " + str(num[i]))
        return num[i]

    def get_cell(self, col, row):
        num = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26]
        alph = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']
        i = num.index(col)
        return alph[i]+str(row)

    def click(self, event, cell):
        self.root.title("you clicked mouse button %d in cell %s" % (event.num, cell))

        #Get old expression and value and set them
        col = self.convert_alpha(cell[0])
        row = cell[-1]
        x,y = self.cell_array[int(col)][int(row)]
        self.old_exp = x
        self.old_val = y
        print(self.old_exp)
        print(self.old_val)
        #Set cell back to expression
        tv = StringVar()
        self.cells[cell]["textvariable"] = tv
        tv.set(x)

    def key_r(self, event, cell):    #Algorithm 1 to go inside this function
        exp_exists = True
        #Get text/data in given cell
        data = self.cells[cell].get()
        #data = self.get_exp(cell)
        print(data)
        self.root.title("cell %s contains %s" % (cell, data))
        #Get col and row for array usage
        col = self.convert_alpha(cell[0])
        row = cell[-1]
        #Start Algorithm 1
        self.creat_symTable(cell)
        #Prune symbol table
        clean = self.first_loop(cell)
        while clean==False:
            clean = self.first_loop(cell)
        #Evaluate new expression using pruned symbol table
        try:
            val = eval(data, {}, self.sym_table)
            self.cell_array[int(col)][int(row)] = (data, val)
        except:
            print("Evaluation of new expression did not work!")
            return False
        #Change cell to value instead of expression
        if exp_exists:
            tv = StringVar()
            self.cells[cell]["textvariable"] = tv
            tv.set(val)
        #put current cell back into symbol table
        self.sym_table[cell] = val
        #Update all cells to reflect new value
        okay = True
        okay = self.second_loop(cell)
        while okay==False:
            okay = self.second_loop(cell)
        if self.error_flag==True:
            okay = False
        return okay

    def creat_symTable(self, cur_cell):
        for row in range(self.nr-1):
            for col in range(self.nc-1):
                if int(col)!=0 and int(row)!=0:
                    x,y = self.cell_array[int(col)][int(row)]
                    if len(x) >= 1:
                        cell = self.get_cell(int(col), int(row))
                        self.sym_table[cell] = y
        if cur_cell in self.sym_table.keys():
            del self.sym_table[cur_cell]

    def first_loop(self, cur_cell): #do this function until it returns clean=True
        clean = True
        for cell, value in self.sym_table.items():
            try:
                eval(self.cells[cell].get(), {}, self.sym_table)
            except:
                del self.sym_table[cell]
                clean = False
        return clean

    def get_exp(self, cell):
        tcol = self.convert_alpha(cell[0])
        tcell = cell[0:]
        trow = tcell
        for row in range(self.nr-1):
            for col in range(self.nc-1):
                if int(col)==tcol and int(row)==trow:
                    x,y = self.cell_array[int(col)][int(row)]
                    return x

    def second_loop(self, cur_cell):
        done = True
        for row in range(self.nr-1):
            for col in range(self.nc-1):
                if int(col)!=0 and int(row)!=0:
                    x,y = self.cell_array[int(col)][int(row)]
                    if len(x) >= 1:
                        cell = self.get_cell(int(col), int(row))
                        if cell != cur_cell:
                            try:
                                #print("cell get: " + self.cells[cell].get())
                                val = eval(x, {}, self.sym_table)
                            except:
                                #Set current cell exp and val back to old
                                tv = StringVar()
                                self.cells[cur_cell]["textvariable"] = tv
                                tv.set(self.old_val)
                                cur_col = self.convert_alpha(cur_cell[0])
                                tcur_cell = cur_cell[0:]
                                cur_row = tcur_cell
                                self.cell_array[int(cur_col)][int(cur_row)] = (self.old_exp, self.old_val)
                                #set flags
                                done = False
                                self.error_flag = True #okay=false
                                return done
                            if val != y:
                                #update cell if vals don't match
                                self.cell_array[int(col)][int(row)] = (x, val)
                                tv = StringVar()
                                self.cells[cell]["textvariable"] = tv
                                tv.set(val)
                                self.sym_table[cell] = val
                                done = False
                                return done
        return done

    def input_array(self, entryx, entryy, col, row):
        self.cell_array[col][row] = entryx,entryy



root = Tk()
root.title('Py-Spreadsheet')
nr = 6 #rows
nc = 6 #cols
sheet = Spreadsheet(root, nr, nc)
root.mainloop()

#print(sheet.cell_array)

#s = "6"
#print(eval(s) - 1)
# eval(expr, {}, symbolTable)




