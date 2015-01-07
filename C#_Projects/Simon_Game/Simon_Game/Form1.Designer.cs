namespace Simon_Game
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.buttonR = new System.Windows.Forms.Button();
            this.buttonG = new System.Windows.Forms.Button();
            this.buttonY = new System.Windows.Forms.Button();
            this.buttonB = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.playBut = new System.Windows.Forms.Button();
            this.statusBox = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.solutionBox = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // buttonR
            // 
            this.buttonR.BackColor = System.Drawing.Color.Red;
            this.buttonR.Cursor = System.Windows.Forms.Cursors.Hand;
            this.buttonR.Location = new System.Drawing.Point(400, 115);
            this.buttonR.Name = "buttonR";
            this.buttonR.Size = new System.Drawing.Size(201, 105);
            this.buttonR.TabIndex = 0;
            this.buttonR.UseVisualStyleBackColor = false;
            this.buttonR.Click += new System.EventHandler(this.buttonR_Click);
            // 
            // buttonG
            // 
            this.buttonG.BackColor = System.Drawing.Color.Lime;
            this.buttonG.Cursor = System.Windows.Forms.Cursors.Hand;
            this.buttonG.Location = new System.Drawing.Point(167, 115);
            this.buttonG.Name = "buttonG";
            this.buttonG.Size = new System.Drawing.Size(208, 105);
            this.buttonG.TabIndex = 1;
            this.buttonG.UseVisualStyleBackColor = false;
            this.buttonG.Click += new System.EventHandler(this.buttonG_Click);
            // 
            // buttonY
            // 
            this.buttonY.BackColor = System.Drawing.Color.Yellow;
            this.buttonY.Cursor = System.Windows.Forms.Cursors.Hand;
            this.buttonY.Location = new System.Drawing.Point(167, 237);
            this.buttonY.Name = "buttonY";
            this.buttonY.Size = new System.Drawing.Size(208, 107);
            this.buttonY.TabIndex = 2;
            this.buttonY.UseVisualStyleBackColor = false;
            this.buttonY.Click += new System.EventHandler(this.buttonY_Click);
            // 
            // buttonB
            // 
            this.buttonB.BackColor = System.Drawing.Color.Blue;
            this.buttonB.Cursor = System.Windows.Forms.Cursors.Hand;
            this.buttonB.Location = new System.Drawing.Point(400, 237);
            this.buttonB.Name = "buttonB";
            this.buttonB.Size = new System.Drawing.Size(201, 107);
            this.buttonB.TabIndex = 3;
            this.buttonB.UseVisualStyleBackColor = false;
            this.buttonB.Click += new System.EventHandler(this.buttonB_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 48F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(284, 19);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(214, 73);
            this.label1.TabIndex = 4;
            this.label1.Text = "Simon";
            // 
            // playBut
            // 
            this.playBut.BackColor = System.Drawing.Color.White;
            this.playBut.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.playBut.Location = new System.Drawing.Point(341, 375);
            this.playBut.Name = "playBut";
            this.playBut.Size = new System.Drawing.Size(86, 29);
            this.playBut.TabIndex = 5;
            this.playBut.Text = "Play";
            this.playBut.UseVisualStyleBackColor = false;
            this.playBut.Click += new System.EventHandler(this.playBut_Click);
            // 
            // statusBox
            // 
            this.statusBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.statusBox.Location = new System.Drawing.Point(51, 35);
            this.statusBox.Name = "statusBox";
            this.statusBox.Size = new System.Drawing.Size(155, 44);
            this.statusBox.TabIndex = 6;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(48, 19);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(68, 13);
            this.label2.TabIndex = 7;
            this.label2.Text = "Game Status";
            // 
            // solutionBox
            // 
            this.solutionBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.solutionBox.Location = new System.Drawing.Point(36, 431);
            this.solutionBox.Name = "solutionBox";
            this.solutionBox.Size = new System.Drawing.Size(698, 29);
            this.solutionBox.TabIndex = 8;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(33, 415);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(83, 13);
            this.label3.TabIndex = 9;
            this.label3.Text = "Buttons to press";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(793, 472);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.solutionBox);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.statusBox);
            this.Controls.Add(this.playBut);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.buttonB);
            this.Controls.Add(this.buttonY);
            this.Controls.Add(this.buttonG);
            this.Controls.Add(this.buttonR);
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.Text = "Simon";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonR;
        private System.Windows.Forms.Button buttonG;
        private System.Windows.Forms.Button buttonY;
        private System.Windows.Forms.Button buttonB;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button playBut;
        private System.Windows.Forms.TextBox statusBox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox solutionBox;
        private System.Windows.Forms.Label label3;
    }
}

