namespace tictactoe
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.button_start = new System.Windows.Forms.Button();
            this.pictureBox_player2 = new System.Windows.Forms.PictureBox();
            this.pictureBox_player1 = new System.Windows.Forms.PictureBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.button11 = new System.Windows.Forms.Button();
            this.button12 = new System.Windows.Forms.Button();
            this.button13 = new System.Windows.Forms.Button();
            this.button21 = new System.Windows.Forms.Button();
            this.button22 = new System.Windows.Forms.Button();
            this.button23 = new System.Windows.Forms.Button();
            this.button31 = new System.Windows.Forms.Button();
            this.button32 = new System.Windows.Forms.Button();
            this.button33 = new System.Windows.Forms.Button();
            this.ReStartToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.AIToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.选择棋子ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.玩家1ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.玩家2ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.panel_choose = new System.Windows.Forms.Panel();
            this.radioButton2 = new System.Windows.Forms.RadioButton();
            this.radioButton1 = new System.Windows.Forms.RadioButton();
            this.imageList1 = new System.Windows.Forms.ImageList(this.components);
            this.backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
            this.Tips = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_player2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_player1)).BeginInit();
            this.panel_choose.SuspendLayout();
            this.SuspendLayout();
            // 
            // button_start
            // 
            this.button_start.Font = new System.Drawing.Font("宋体", 15F);
            this.button_start.ForeColor = System.Drawing.Color.DarkRed;
            this.button_start.Location = new System.Drawing.Point(849, 732);
            this.button_start.Margin = new System.Windows.Forms.Padding(7);
            this.button_start.Name = "button_start";
            this.button_start.Size = new System.Drawing.Size(313, 81);
            this.button_start.TabIndex = 0;
            this.button_start.Text = "开始游戏";
            this.button_start.UseVisualStyleBackColor = true;
            this.button_start.Click += new System.EventHandler(this.Onstart);
            // 
            // pictureBox_player2
            // 
            this.pictureBox_player2.BackColor = System.Drawing.Color.SandyBrown;
            this.pictureBox_player2.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox_player2.Image")));
            this.pictureBox_player2.Location = new System.Drawing.Point(999, 479);
            this.pictureBox_player2.Margin = new System.Windows.Forms.Padding(7);
            this.pictureBox_player2.Name = "pictureBox_player2";
            this.pictureBox_player2.Size = new System.Drawing.Size(163, 158);
            this.pictureBox_player2.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBox_player2.TabIndex = 1;
            this.pictureBox_player2.TabStop = false;
            // 
            // pictureBox_player1
            // 
            this.pictureBox_player1.BackColor = System.Drawing.Color.Sienna;
            this.pictureBox_player1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox_player1.Image")));
            this.pictureBox_player1.Location = new System.Drawing.Point(999, 220);
            this.pictureBox_player1.Margin = new System.Windows.Forms.Padding(7);
            this.pictureBox_player1.Name = "pictureBox_player1";
            this.pictureBox_player1.Size = new System.Drawing.Size(163, 158);
            this.pictureBox_player1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBox_player1.TabIndex = 2;
            this.pictureBox_player1.TabStop = false;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.BackColor = System.Drawing.Color.Transparent;
            this.label1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.label1.Font = new System.Drawing.Font("宋体", 12F);
            this.label1.ForeColor = System.Drawing.Color.Black;
            this.label1.Location = new System.Drawing.Point(761, 299);
            this.label1.Margin = new System.Windows.Forms.Padding(7, 0, 7, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(215, 38);
            this.label1.TabIndex = 3;
            this.label1.Text = "玩家1棋子：";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.BackColor = System.Drawing.Color.Transparent;
            this.label2.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.label2.Font = new System.Drawing.Font("宋体", 12F);
            this.label2.ForeColor = System.Drawing.Color.Black;
            this.label2.Location = new System.Drawing.Point(761, 572);
            this.label2.Margin = new System.Windows.Forms.Padding(7, 0, 7, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(215, 38);
            this.label2.TabIndex = 4;
            this.label2.Text = "玩家2棋子：";
            // 
            // button11
            // 
            this.button11.BackColor = System.Drawing.SystemColors.Control;
            this.button11.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.button11.Location = new System.Drawing.Point(82, 166);
            this.button11.Margin = new System.Windows.Forms.Padding(5, 4, 5, 4);
            this.button11.Name = "button11";
            this.button11.Size = new System.Drawing.Size(187, 180);
            this.button11.TabIndex = 5;
            this.button11.Text = " ";
            this.button11.UseVisualStyleBackColor = true;
            this.button11.Click += new System.EventHandler(this.OnBnt);
            // 
            // button12
            // 
            this.button12.BackColor = System.Drawing.SystemColors.Control;
            this.button12.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.button12.Location = new System.Drawing.Point(280, 166);
            this.button12.Margin = new System.Windows.Forms.Padding(5, 4, 5, 4);
            this.button12.Name = "button12";
            this.button12.Size = new System.Drawing.Size(187, 180);
            this.button12.TabIndex = 6;
            this.button12.Text = " ";
            this.button12.UseVisualStyleBackColor = true;
            this.button12.Click += new System.EventHandler(this.OnBnt);
            // 
            // button13
            // 
            this.button13.BackColor = System.Drawing.SystemColors.Control;
            this.button13.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.button13.Location = new System.Drawing.Point(481, 166);
            this.button13.Margin = new System.Windows.Forms.Padding(5, 4, 5, 4);
            this.button13.Name = "button13";
            this.button13.Size = new System.Drawing.Size(187, 180);
            this.button13.TabIndex = 7;
            this.button13.Text = " ";
            this.button13.UseVisualStyleBackColor = true;
            this.button13.Click += new System.EventHandler(this.OnBnt);
            // 
            // button21
            // 
            this.button21.BackColor = System.Drawing.SystemColors.Control;
            this.button21.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.button21.Location = new System.Drawing.Point(82, 360);
            this.button21.Margin = new System.Windows.Forms.Padding(5, 4, 5, 4);
            this.button21.Name = "button21";
            this.button21.Size = new System.Drawing.Size(187, 180);
            this.button21.TabIndex = 8;
            this.button21.Text = " ";
            this.button21.UseVisualStyleBackColor = true;
            this.button21.Click += new System.EventHandler(this.OnBnt);
            // 
            // button22
            // 
            this.button22.BackColor = System.Drawing.SystemColors.Control;
            this.button22.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.button22.Location = new System.Drawing.Point(280, 360);
            this.button22.Margin = new System.Windows.Forms.Padding(5, 4, 5, 4);
            this.button22.Name = "button22";
            this.button22.Size = new System.Drawing.Size(187, 180);
            this.button22.TabIndex = 9;
            this.button22.Text = " ";
            this.button22.UseVisualStyleBackColor = true;
            this.button22.Click += new System.EventHandler(this.OnBnt);
            // 
            // button23
            // 
            this.button23.BackColor = System.Drawing.SystemColors.Control;
            this.button23.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.button23.Font = new System.Drawing.Font("宋体", 50F);
            this.button23.Location = new System.Drawing.Point(481, 360);
            this.button23.Margin = new System.Windows.Forms.Padding(5, 4, 5, 4);
            this.button23.Name = "button23";
            this.button23.Size = new System.Drawing.Size(187, 180);
            this.button23.TabIndex = 10;
            this.button23.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            this.button23.UseVisualStyleBackColor = true;
            this.button23.Click += new System.EventHandler(this.OnBnt);
            // 
            // button31
            // 
            this.button31.BackColor = System.Drawing.SystemColors.Control;
            this.button31.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.button31.Location = new System.Drawing.Point(82, 554);
            this.button31.Margin = new System.Windows.Forms.Padding(5, 4, 5, 4);
            this.button31.Name = "button31";
            this.button31.Size = new System.Drawing.Size(187, 180);
            this.button31.TabIndex = 11;
            this.button31.Text = " ";
            this.button31.UseVisualStyleBackColor = true;
            this.button31.Click += new System.EventHandler(this.OnBnt);
            // 
            // button32
            // 
            this.button32.BackColor = System.Drawing.SystemColors.Control;
            this.button32.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.button32.Location = new System.Drawing.Point(280, 554);
            this.button32.Margin = new System.Windows.Forms.Padding(5, 4, 5, 4);
            this.button32.Name = "button32";
            this.button32.Size = new System.Drawing.Size(187, 180);
            this.button32.TabIndex = 12;
            this.button32.Text = " ";
            this.button32.UseVisualStyleBackColor = true;
            this.button32.Click += new System.EventHandler(this.OnBnt);
            // 
            // button33
            // 
            this.button33.BackColor = System.Drawing.SystemColors.Control;
            this.button33.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.button33.Location = new System.Drawing.Point(481, 554);
            this.button33.Margin = new System.Windows.Forms.Padding(5, 4, 5, 4);
            this.button33.Name = "button33";
            this.button33.Size = new System.Drawing.Size(187, 180);
            this.button33.TabIndex = 13;
            this.button33.Text = " ";
            this.button33.UseVisualStyleBackColor = true;
            this.button33.Click += new System.EventHandler(this.OnBnt);
            // 
            // ReStartToolStripMenuItem
            // 
            this.ReStartToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("ReStartToolStripMenuItem.Image")));
            this.ReStartToolStripMenuItem.Name = "ReStartToolStripMenuItem";
            this.ReStartToolStripMenuItem.Size = new System.Drawing.Size(171, 40);
            this.ReStartToolStripMenuItem.Text = "重新开始";
            this.ReStartToolStripMenuItem.Click += new System.EventHandler(this.Onstart);
            // 
            // AIToolStripMenuItem
            // 
            this.AIToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.选择棋子ToolStripMenuItem});
            this.AIToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("AIToolStripMenuItem.Image")));
            this.AIToolStripMenuItem.Name = "AIToolStripMenuItem";
            this.AIToolStripMenuItem.Size = new System.Drawing.Size(171, 40);
            this.AIToolStripMenuItem.Text = "人机对战";
            // 
            // 选择棋子ToolStripMenuItem
            // 
            this.选择棋子ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.玩家1ToolStripMenuItem,
            this.玩家2ToolStripMenuItem});
            this.选择棋子ToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("选择棋子ToolStripMenuItem.Image")));
            this.选择棋子ToolStripMenuItem.Name = "选择棋子ToolStripMenuItem";
            this.选择棋子ToolStripMenuItem.Size = new System.Drawing.Size(228, 42);
            this.选择棋子ToolStripMenuItem.Text = "选择棋子";
            // 
            // 玩家1ToolStripMenuItem
            // 
            this.玩家1ToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("玩家1ToolStripMenuItem.Image")));
            this.玩家1ToolStripMenuItem.Name = "玩家1ToolStripMenuItem";
            this.玩家1ToolStripMenuItem.Size = new System.Drawing.Size(190, 42);
            this.玩家1ToolStripMenuItem.Text = "玩家1";
            // 
            // 玩家2ToolStripMenuItem
            // 
            this.玩家2ToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("玩家2ToolStripMenuItem.Image")));
            this.玩家2ToolStripMenuItem.Name = "玩家2ToolStripMenuItem";
            this.玩家2ToolStripMenuItem.Size = new System.Drawing.Size(190, 42);
            this.玩家2ToolStripMenuItem.Text = "玩家2";
            // 
            // panel_choose
            // 
            this.panel_choose.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("panel_choose.BackgroundImage")));
            this.panel_choose.Controls.Add(this.radioButton2);
            this.panel_choose.Controls.Add(this.radioButton1);
            this.panel_choose.Location = new System.Drawing.Point(82, 794);
            this.panel_choose.Margin = new System.Windows.Forms.Padding(7);
            this.panel_choose.Name = "panel_choose";
            this.panel_choose.Size = new System.Drawing.Size(698, 79);
            this.panel_choose.TabIndex = 15;
            // 
            // radioButton2
            // 
            this.radioButton2.AutoSize = true;
            this.radioButton2.BackColor = System.Drawing.Color.Transparent;
            this.radioButton2.Font = new System.Drawing.Font("宋体", 12F);
            this.radioButton2.ForeColor = System.Drawing.Color.LavenderBlush;
            this.radioButton2.Location = new System.Drawing.Point(399, 20);
            this.radioButton2.Margin = new System.Windows.Forms.Padding(7);
            this.radioButton2.Name = "radioButton2";
            this.radioButton2.Size = new System.Drawing.Size(208, 40);
            this.radioButton2.TabIndex = 1;
            this.radioButton2.Text = "玩家2先手";
            this.radioButton2.UseVisualStyleBackColor = false;
            // 
            // radioButton1
            // 
            this.radioButton1.AllowDrop = true;
            this.radioButton1.AutoSize = true;
            this.radioButton1.BackColor = System.Drawing.Color.Transparent;
            this.radioButton1.Checked = true;
            this.radioButton1.Font = new System.Drawing.Font("宋体", 12F);
            this.radioButton1.ForeColor = System.Drawing.Color.LavenderBlush;
            this.radioButton1.Location = new System.Drawing.Point(42, 20);
            this.radioButton1.Margin = new System.Windows.Forms.Padding(7);
            this.radioButton1.Name = "radioButton1";
            this.radioButton1.Size = new System.Drawing.Size(208, 40);
            this.radioButton1.TabIndex = 0;
            this.radioButton1.TabStop = true;
            this.radioButton1.Text = "玩家1先手";
            this.radioButton1.UseVisualStyleBackColor = false;
            // 
            // imageList1
            // 
            this.imageList1.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList1.ImageStream")));
            this.imageList1.TransparentColor = System.Drawing.Color.Transparent;
            this.imageList1.Images.SetKeyName(0, "icon_horde.bmp");
            this.imageList1.Images.SetKeyName(1, "icon_alliance.bmp");
            // 
            // Tips
            // 
            this.Tips.BackColor = System.Drawing.Color.PeachPuff;
            this.Tips.ForeColor = System.Drawing.SystemColors.ControlText;
            this.Tips.Location = new System.Drawing.Point(77, 54);
            this.Tips.Name = "Tips";
            this.Tips.Size = new System.Drawing.Size(614, 92);
            this.Tips.TabIndex = 16;
            this.Tips.Text = "井字棋";
            // 
            // button1
            // 
            this.button1.Font = new System.Drawing.Font("宋体", 15F);
            this.button1.ForeColor = System.Drawing.Color.DarkRed;
            this.button1.Location = new System.Drawing.Point(849, 830);
            this.button1.Margin = new System.Windows.Forms.Padding(7);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(313, 81);
            this.button1.TabIndex = 17;
            this.button1.Text = "重新开始";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.OnReStart);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(14F, 27F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.BackColor = System.Drawing.Color.White;
            this.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("$this.BackgroundImage")));
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.ClientSize = new System.Drawing.Size(1223, 927);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.Tips);
            this.Controls.Add(this.panel_choose);
            this.Controls.Add(this.button33);
            this.Controls.Add(this.button32);
            this.Controls.Add(this.button31);
            this.Controls.Add(this.button23);
            this.Controls.Add(this.button22);
            this.Controls.Add(this.button21);
            this.Controls.Add(this.button13);
            this.Controls.Add(this.button12);
            this.Controls.Add(this.button11);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.pictureBox_player1);
            this.Controls.Add(this.pictureBox_player2);
            this.Controls.Add(this.button_start);
            this.Margin = new System.Windows.Forms.Padding(7);
            this.Name = "Form1";
            this.Text = "井字棋小程序";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_player2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_player1)).EndInit();
            this.panel_choose.ResumeLayout(false);
            this.panel_choose.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button_start;
        private System.Windows.Forms.PictureBox pictureBox_player2;
        private System.Windows.Forms.PictureBox pictureBox_player1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button button11;
        private System.Windows.Forms.Button button12;
        private System.Windows.Forms.Button button13;
        private System.Windows.Forms.Button button21;
        private System.Windows.Forms.Button button22;
        private System.Windows.Forms.Button button23;
        private System.Windows.Forms.Button button31;
        private System.Windows.Forms.Button button32;
        private System.Windows.Forms.Button button33;
        private System.Windows.Forms.ToolStripMenuItem ReStartToolStripMenuItem;
        private System.Windows.Forms.Panel panel_choose;
        private System.Windows.Forms.RadioButton radioButton2;
        private System.Windows.Forms.RadioButton radioButton1;
        private System.Windows.Forms.ToolStripMenuItem AIToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 选择棋子ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 玩家1ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 玩家2ToolStripMenuItem;
        private System.Windows.Forms.ImageList imageList1;
        private System.ComponentModel.BackgroundWorker backgroundWorker1;
        private System.Windows.Forms.Label Tips;
        private System.Windows.Forms.Button button1;
    }
}

