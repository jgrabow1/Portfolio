using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Simon_Game
{
    public partial class Form1 : Form
    {
        int level = 2;
        int listPointer = 0;
        int playFlag = 0;
        enum Buttons {Red, Green, Yellow, Blue};
        List<int> buttonsClicked = new List<int>();
        List<int> buttonsRando = new List<int>();

        public Form1()
        {
            InitializeComponent();
        }

        private void check_win()
        {
            if (listPointer == level)
            {
                statusBox.Text = "You win!";
                level++;
                listPointer = 0;
                playFlag = 0;
                buttonsClicked.Clear();
                buttonsRando.Clear();
            }
        }

        private void buttonR_Click(object sender, EventArgs e)
        {
            int Red = (int)Buttons.Red;

            if (playFlag == 1)
            {
                buttonsClicked.Add(Red);
                if (buttonsRando.ElementAt(listPointer) != buttonsClicked.ElementAt(listPointer))
                {
                    statusBox.Text = "You lose!";
                    level = 2;
                    listPointer = 0;
                    playFlag = 0;
                    buttonsClicked.Clear();
                    buttonsRando.Clear();
                }
                listPointer++;

                check_win();
            }
        }

        private void buttonG_Click(object sender, EventArgs e)
        {
            int Green = (int)Buttons.Green;

            if (playFlag == 1)
            {
                buttonsClicked.Add(Green);
                if (buttonsRando.ElementAt(listPointer) != buttonsClicked.ElementAt(listPointer))
                {
                    statusBox.Text = "You lose!";
                    level = 2;
                    listPointer = 0;
                    playFlag = 0;
                    buttonsClicked.Clear();
                    buttonsRando.Clear();
                }
                listPointer++;

                check_win();
            }
        }

        private void buttonY_Click(object sender, EventArgs e)
        {
            int Yellow = (int)Buttons.Yellow;

            if (playFlag == 1)
            {
                buttonsClicked.Add(Yellow);
                if (buttonsRando.ElementAt(listPointer) != buttonsClicked.ElementAt(listPointer))
                {
                    statusBox.Text = "You lose!";
                    level = 2;
                    listPointer = 0;
                    playFlag = 0;
                    buttonsClicked.Clear();
                    buttonsRando.Clear();
                }
                listPointer++;

                check_win();
            }
        }

        private void buttonB_Click(object sender, EventArgs e)
        {
            int Blue = (int)Buttons.Blue;

            if (playFlag == 1)
            {
                buttonsClicked.Add(Blue);
                if (buttonsRando.ElementAt(listPointer) != buttonsClicked.ElementAt(listPointer))
                {
                    statusBox.Text = "You lose!";
                    level = 2;
                    listPointer = 0;
                    playFlag = 0;
                    buttonsClicked.Clear();
                    buttonsRando.Clear();
                }
                listPointer++;

                check_win();
            }
        }

        private void playBut_Click(object sender, EventArgs e)
        {
            Random random = new Random();
            int buttonsAdded = 0;

            solutionBox.Clear();
            statusBox.Clear();

            playFlag = 1;
            while (buttonsAdded < level)
            {
                int randoButton = random.Next(4);
                buttonsRando.Add(randoButton);

                switch (randoButton)
                {
                    case 0:
                        solutionBox.AppendText("Red ");
                        break;

                    case 1:
                        solutionBox.AppendText("Green ");
                        break;

                    case 2:
                        solutionBox.AppendText("Yellow ");
                        break;

                    case 3:
                        solutionBox.AppendText("Blue ");
                        break;
                }

                buttonsAdded++;
            }
        }
    }
}
