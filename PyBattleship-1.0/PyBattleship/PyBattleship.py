from tkinter import *
from random import *
import time
import shelve

LARGE_FONT = ("Verdana", 12)
LARGER_FONT = ("Verdana", 22)
LARGEST_FONT = ("Verdana", 36)

class Battleship():
    def __init__(self, root):
        self.root = root
        self.pages = {}
        self.player1_array = [[(0,0) for y in range(10)] for x in range(10)]
        self.player2_array = [[(0,0) for y in range(10)] for x in range(10)]
        self.placement = 'horizontal'
        self.mode = 'new game'
        self.select_index = 0
        self.continue_check = {'Continue': False}
        self.p1_shiptally = {'Carrier': 5, 'Battleship': 4, 'Submarine': 3, 'Cruiser': 3, 'Destroyer': 2}
        self.p2_shiptally = {'Carrier': 5, 'Battleship': 4, 'Submarine': 3, 'Cruiser': 3, 'Destroyer': 2}
        self.ships_list = ['Carrier', 'Battleship', 'Submarine', 'Cruiser', 'Destroyer']

        container = Frame(root)
        container.pack(side="top", fill="both", expand=True)
        container.grid()

        for P in (MainMenu, ShipSelect, BattleScreen, WinScreen, LoseScreen):
            frame = P(container, self)
            frame.grid(row=0, column=0, sticky="nsew")
            self.pages[P] = frame
        self.show_frame(MainMenu)

    def quit_game(self):
        f = shelve.open('temp.db')
        f['player1_array'] = self.player1_array
        f['player2_array'] = self.player2_array
        f['p1_shiptally'] = self.p1_shiptally
        f['p2_shiptally'] = self.p2_shiptally
        f['continue_check'] = self.continue_check
        f.close()
        self.root.destroy()

    def print_array(self, player):
        for row in range(10):
            if player==1:
                print(self.player1_array[row])
            else:
                print(self.player2_array[row])

    def show_frame(self, cont):
        if cont==BattleScreen:
            self.pages[BattleScreen].init_grids(self)
        frame = self.pages[cont]
        frame.tkraise()

    def set_vertical(self):
        self.placement = 'vertical'
        print(self.placement)

    def set_horizontal(self):
        self.placement = 'horizontal'
        print(self.placement)


class MainMenu(Frame):
    def __init__(self, parent, controller):
        Frame.__init__(self, parent)
        self.controller = controller
        label = Label(self, text="Welcome to PyBattleship!", font=LARGER_FONT)
        label.pack(pady=40,padx=10)

        button1 = Button(self, text='New Game', width=13, font=LARGE_FONT, command=lambda controller=controller:controller.show_frame(ShipSelect))
        button1.pack()
        button2 = Button(self, text='Continue Game', width=13, font=LARGE_FONT, command=lambda :self.continue_game())
        button2.pack()
        button3 = Button(self, text='Quit', width=13, font=LARGE_FONT, command=lambda controller=controller:controller.quit_game())
        button3.pack()
        self.clabel = Label(self, font=LARGE_FONT)
        self.clabel.pack(pady=20,padx=10)

    def continue_game(self):
        try:
            f = shelve.open('temp.db')
            self.controller.player1_array = f['player1_array']
            self.controller.player2_array = f['player2_array']
            self.controller.p1_shiptally = f['p1_shiptally']
            self.controller.p2_shiptally = f['p2_shiptally']
            continue_check = f['continue_check']
            f.close()
        except:
            print("Cannot continue game.")
            self.clabel["text"] = "No game to continue!"
            return False
        if continue_check['Continue'] == True:
            self.controller.mode = 'continue game'
            self.controller.show_frame(BattleScreen)
        else:
            print("Cannot continue game.")
            self.clabel["text"] = "No game to continue!"
            return False


class ShipSelect(Frame):
    def __init__(self, parent, controller):
        Frame.__init__(self, parent)

        for row in range(11):
           for col in range(10):
                if row==0:
                    grid_button = Label(self, height=1, width=1)
                    grid_button.grid(row=row, column=col)
                else:
                    grid_button = Button(self, bg='blue', height=1, width=1, command=lambda col=int(col), row=int(row):self.place_ship(controller, 1, col, row-1))
                    grid_button.grid(row=row, column=col)
        for row in range(11):
           for col in range(12, 32):
               grid_button = Label(self, height=1, width=1)
               grid_button.grid(row=row, column=col)

        place_text = "Placing %s (size: %d)" % (controller.ships_list[controller.select_index], controller.p1_shiptally[controller.ships_list[controller.select_index]])

        label = Label(self, text="Please place your ships", font=LARGE_FONT)
        label.grid(row=0, column=0, columnspan=15, sticky="w")
        self.ship_label = Label(self, text=place_text)
        self.ship_label.grid(row=2, column=11, columnspan=15, sticky="w")
        vButton = Button(self, text='Place vertically', width=13, command=lambda :controller.set_vertical())
        vButton.grid(row=3, column=11, columnspan=15, sticky="w")
        hButton = Button(self, text='Place horizontally', width=13, command=lambda :controller.set_horizontal())
        hButton.grid(row=4, column=11, columnspan=15, sticky="w")
        button1 = Button(self, text='Quit', width=6, command=lambda controller=controller:controller.quit_game())
        button1.grid(row=11, column=0, columnspan=4, sticky="w")

    def place_ship(self, controller, player, col, row):
        no_errors = True
        if player==1: #Player 1 is placing ship
            if controller.placement == 'horizontal':
                if (10-col) >= controller.p1_shiptally[controller.ships_list[controller.select_index]]:
                    for i in range(controller.p1_shiptally[controller.ships_list[controller.select_index]]):
                        x,y = controller.player1_array[row][col+i]
                        if x != 0:
                            print("Cannot place. Ship already exists in path!")
                            return False
                else:
                    print("Cannot place. Not enough room!")
                    return False
                if (10-col) >= controller.p1_shiptally[controller.ships_list[controller.select_index]]:
                    for i in range(controller.p1_shiptally[controller.ships_list[controller.select_index]]):
                        controller.player1_array[row][col+i] = ("^", controller.ships_list[controller.select_index])
                else:
                    no_errors = False
                    print("Cannot place. Not enough room!")
            else:
                if (10-row) >= controller.p1_shiptally[controller.ships_list[controller.select_index]]:
                    for i in range(controller.p1_shiptally[controller.ships_list[controller.select_index]]):
                        x,y = controller.player1_array[row+i][col]
                        if x != 0:
                            print("Cannot place. Ship already exists in path!")
                            return False
                else:
                    print("Cannot place. Not enough room!")
                    return False
                if (10-row) >= controller.p1_shiptally[controller.ships_list[controller.select_index]]:
                    for i in range(controller.p1_shiptally[controller.ships_list[controller.select_index]]):
                        controller.player1_array[row+i][col] = ("^", controller.ships_list[controller.select_index])
                else:
                    no_errors = False
                    print("Cannot place. Not enough room!")
            if no_errors==True:
                if controller.placement == 'horizontal':
                    for i in range(controller.p1_shiptally[controller.ships_list[controller.select_index]]):
                        grid_button = Button(self, bg='grey', height=1, width=1, command=lambda col=int(col), row=int(row):self.place_ship(controller, 1, col, row))
                        grid_button.grid(row=(row+1), column=col+i)
                else:
                    for i in range(controller.p1_shiptally[controller.ships_list[controller.select_index]]):
                        grid_button = Button(self, bg='grey', height=1, width=1, command=lambda col=int(col), row=int(row):self.place_ship(controller, 1, col, row))
                        grid_button.grid(row=(row+1)+i, column=col)
                if controller.select_index < 4:
                    controller.select_index +=1
                else:
                    controller.select_index = 0
                    controller.continue_check['Continue'] = True
                    controller.show_frame(BattleScreen)
                new_text = "Placing %s (size: %d)" % (controller.ships_list[controller.select_index], controller.p1_shiptally[controller.ships_list[controller.select_index]])
                self.ship_label["text"] = new_text
        else: #Player 2 is placing ship
            rang = controller.p1_shiptally[controller.ships_list[controller.select_index]]
            if controller.placement == 'horizontal':
                leeway = (9-col)
                if (leeway) >= rang:
                    for i in range(rang):
                        x,y = controller.player2_array[row][col+i]
                        if x != 0:
                            print("Cannot place. Ship already exists in path!")
                            return False
                else:
                    print("Cannot place. Not enough room!")
                    return False
                if (leeway) >= rang:
                    for i in range(rang):
                        controller.player2_array[row][col+i] = ("^", controller.ships_list[controller.select_index])
                else:
                    no_errors = False
                    print("Ship does not fit here!")
            else:
                leeway = (9-row)
                if (leeway) >= rang:
                    for i in range(rang):
                        x,y = controller.player2_array[row+i][col]
                        if x != 0:
                            print("Cannot place. Ship already exists in path!")
                            return False
                else:
                    print("Cannot place. Not enough room!")
                    return False
                if (leeway) >= rang:
                    for i in range(rang):
                        controller.player2_array[row+i][col] = ("^", controller.ships_list[controller.select_index])
                else:
                    no_errors = False
                    print("Ship does not fit here!")
        return no_errors


class BattleScreen(Frame):
    def __init__(self, parent, controller):
        Frame.__init__(self, parent)
        self.parent = parent
        self.controller = controller
        self.p1_turn = True #true if player 1's turn
        self.ai_lhit = False #true if ai's last shot was a hit
        self.pshot = () #Coordinates of last shot by ai


    def init_grids(self, controller):
        if controller.mode == 'new game':
            position = ['horizontal', 'vertical']
            for i in range(5):
                placement_error = False
                while placement_error==False:
                    controller.placement = position[randint(0, 1)]
                    col = randint(0, 9)
                    row = randint(0, 9)
                    placement_error = controller.pages[ShipSelect].place_ship(controller, 2, col, row)
                controller.select_index +=1
            controller.placement = 'horizontal'
            controller.select_index = 0

        for row in range(11):
           for col in range(10):
               if row==0:
                    grid_button = Label(self, height=1, width=1)
                    grid_button.grid(row=row, column=col)
               else:
                    x,y = self.controller.player2_array[row-1][col]
                    if x=='X':
                        grid_button = Button(self, bg='red', height=1, width=1)
                        grid_button.grid(row=row, column=col)
                    elif x==1:
                        grid_button = Button(self, bg='green', height=1, width=1)
                        grid_button.grid(row=row, column=col)
                    else:
                        grid_button = Button(self, bg='blue', height=1, width=1, command=lambda col=int(col), row=int(row):self.p1attack(controller, col, (row-1)))
                        grid_button.grid(row=row, column=col)
        for row in range(11):
            grid_button = Label(self, height=1, width=1)
            grid_button.grid(row=row, column=11)
        for row in range(11):
           for col in range(12, 22):
               if row==0:
                    grid_button = Label(self, height=1, width=1)
                    grid_button.grid(row=row, column=col)
               else:
                    x,y = self.controller.player1_array[row-1][col-12]
                    if x=='^':
                        grid_button = Button(self, bg='grey', height=1, width=1)
                        grid_button.grid(row=row, column=col)
                    elif x=='X':
                        grid_button = Button(self, bg='red', height=1, width=1)
                        grid_button.grid(row=row, column=col)
                    elif x==1:
                        grid_button = Button(self, bg='green', height=1, width=1)
                        grid_button.grid(row=row, column=col)
                    else:
                        grid_button = Button(self, bg='blue', height=1, width=1)
                        grid_button.grid(row=row, column=col)

        label1 = Label(self, text="Click grid cell to attack")
        label1.grid(row=0, column=0, columnspan=10, sticky="w")
        label2 = Label(self, text="Here are your ships")
        label2.grid(row=0, column=12, columnspan=10, sticky="w")
        self.turn_label = Label(self, text="Turn: Player 1")
        self.turn_label.grid(row=11, column=10, columnspan=10, sticky="w")
        self.sunk_label = Label(self, text="")
        self.sunk_label.grid(row=11, column=20, columnspan=10, sticky="w")
        button1 = Button(self, text='Quit', width=8, command=lambda controller=self.controller:controller.quit_game())
        button1.grid(row=11, columnspan=4)
        rdy_button = Button(self, text='End Turn', width=11, command=lambda controller=self.controller:self.p2initiate(controller))
        rdy_button.grid(row=11, column=3, columnspan=8)

    def p2initiate(self, controller):
        no_error = False
        if self.p1_turn==False:
            self.turn_label["text"] = "Turn: AI"
            time.sleep(1)
            self.sunk_label["text"] = ''
            while no_error==False:
                if self.ai_lhit==False:
                    col = randint(0, 9)
                    row = randint(0, 9)
                    no_error = self.p2attack(controller, col, row)
                else:
                    row, col = self.find_newcoords()
                    no_error = self.p2attack(controller, col, row)
            self.turn_label["text"] = "Turn: Player 1"
        else:
            print("Must make a move before ending turn!")
        return no_error

    def longest_ship(self):
        max = 0
        for x,y in self.controller.p1_shiptally.items():
            if y > max:
                max = y
        return max

    def find_newcoords(self):
        for row in range(10):
            for col in range(10):
                x,y = self.controller.player1_array[row][col]
                if x=='X' and self.controller.p1_shiptally[y] != -1:
                    if int(row) != 9:
                        x2, y2 = self.controller.player1_array[row+1][col]
                        if x2 != 'X' and x2 != 1:
                            return int(row+1), int(col)
                    if int(row) != 0:
                        x2, y2 = self.controller.player1_array[row-1][col]
                        if x2 != 'X' and x2 != 1:
                            return int(row-1), int(col)
                    if int(col) != 9:
                        x2, y2 = self.controller.player1_array[row][col+1]
                        if x2 != 'X' and x2 != 1:
                            return int(row), int(col+1)
                    if int(col) != 0:
                        x2, y2 = self.controller.player1_array[row][col-1]
                        if x2 != 'X' and x2 != 1:
                            return int(row), int(col-1)

    def check_spot(self, col, row):
        horizontal = 0
        vertical = 0
        longest_ship = self.longest_ship()
        for i in range(10):
            if (col+i) <= 9:
                x,y = self.controller.player1_array[row][col+i]
                if x == 0 or x == '^':
                    horizontal += 1
                else:
                    break
            else:
                break
        for i in range(10):
            if (col-i) >= 0:
                x,y = self.controller.player1_array[row][col-i]
                if x == 0 or x == '^':
                    horizontal += 1
                else:
                    break
            else:
                break
        for i in range(10):
            if (row+i) <= 9:
                x,y = self.controller.player1_array[row+i][col]
                if x == 0 or x == '^':
                    vertical += 1
                else:
                    break
            else:
                break
        for i in range(10):
            if (row-i) >= 0:
                x,y = self.controller.player1_array[row-i][col]
                if x == 0 or x == '^':
                    vertical += 1
                else:
                    break
            else:
                break
        if horizontal >= longest_ship or vertical >= longest_ship:
            return True
        else:
            return False

    def p2attack(self, controller, col, row):
        no_error = True
        sunk = 0
        if self.ai_lhit == False:
            if self.check_spot(col, row) == False: #AI check to see if cell is logical place to fire at
                return False
        x,y = controller.player1_array[row][col]
        if x=='^': #hit
            controller.p1_shiptally[y] -= 1
            grid_button = Button(self, bg='red', height=1, width=1)
            grid_button.grid(row=(row+1), column=(col+12))
            controller.player1_array[row][col] = ('X', y)
            self.ai_lhit = True #Scored a hit so last hit considered a hit until ship is sunk
            for i,j in controller.p1_shiptally.items():
                if j==0:
                    print("AI sunk your %s!" % (i))
                    #self.sunk_label["text"] = 'Sunk!'
                    controller.p1_shiptally[i] = -1
                    self.ai_lhit = False #ai sunk ship so last hit no longer considered a hit
            for i,j in controller.p1_shiptally.items():
                if j==-1:
                    sunk +=1
            if sunk >= 5:
                controller.show_frame(LoseScreen)
                print("You lose!") #Player 1 loses!
        elif x==0: #miss
            grid_button = Button(self, bg='green', height=1, width=1)
            grid_button.grid(row=(row+1), column=(col+12))
            controller.player1_array[row][col] = (1, y)
        else: #invalid
            print("You have already attacked here!")
            no_error = False
        self.p1_turn = True
        self.pshot = (col, row) #recording coordinates of last shot
        return no_error

    def p1attack(self, controller, col, row):
        no_error = True
        sunk = 0
        if self.p1_turn==True:
            x,y = controller.player2_array[row][col]
            if x=='^': #hit
                controller.p2_shiptally[y] -= 1
                grid_button = Button(self, bg='red', height=1, width=1, command=lambda col=int(col), row=int(row):self.p1attack(controller, col, row))
                grid_button.grid(row=(row+1), column=col)
                controller.player2_array[row][col] = ('X', y)
                self.turn_label["text"] = "Turn: Player 1 turn ending"
                self.p1_turn = False
                for i,j in controller.p2_shiptally.items():
                    if j==0:
                        print("You sunk %s!" % (i))
                        self.sunk_label["text"] = 'Sunk!'
                        controller.p2_shiptally[i] = -1
                for i,j in controller.p2_shiptally.items():
                    if j==-1:
                        sunk +=1
                if sunk >= 5:
                    controller.show_frame(WinScreen)
                    print("You win!") #Player 1 wins!
            elif x==0: #miss
                grid_button = Button(self, bg='green', height=1, width=1, command=lambda col=int(col), row=int(row):self.p1attack(controller, col, row))
                grid_button.grid(row=(row+1), column=col)
                controller.player2_array[row][col] = (1, y)
                self.turn_label["text"] = "Turn: Player 1 turn ending"
                self.p1_turn = False
            else: #invalid
                print("You have already attacked here!")
                no_error = False
        else:
            print("Not your turn!")
            no_error = False
        return no_error

class WinScreen(Frame):
    def __init__(self, parent, controller):
        Frame.__init__(self, parent)
        self.parent = parent
        self.controller = controller

        label1 = Label(self, text="Congratulations! You win!", font=LARGEST_FONT)
        label1.pack(pady=30,padx=10)
        wwbutton = Button(self, text='Quit', width=13, font=LARGE_FONT, command=lambda controller=controller:controller.root.destroy())
        wwbutton.pack()

class LoseScreen(Frame):
    def __init__(self, parent, controller):
        Frame.__init__(self, parent)
        self.parent = parent
        self.controller = controller

        label1 = Label(self, text="Sorry! You lose!", font=LARGEST_FONT)
        label1.pack(pady=30,padx=10)
        llbutton = Button(self, text='Quit', width=13, font=LARGE_FONT, command=lambda controller=controller:controller.root.destroy())
        llbutton.pack()




root = Tk()
root.title('Py-Battleship')
sheet = Battleship(root)
root.mainloop()

#sheet.print_array(1)
#print('\n')
#sheet.print_array(2)















