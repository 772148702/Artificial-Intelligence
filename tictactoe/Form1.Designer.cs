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
            this.imageList1 = new System.Windows.Forms.ImageList(this.components);
            this.backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
            this.Tips = new System.Windows.Forms.Label();
            this.button_restart = new System.Windows.Forms.Button();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.游戏模式ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.人机对战ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.人人对战ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.pictureBox3 = new System.Windows.Forms.PictureBox();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            this.SuspendLayout();
            // 
            // button_start
            // 
            this.button_start.Font = new System.Drawing.Font("宋体", 15F);
            this.button_start.ForeColor = System.Drawing.Color.DarkRed;
            this.button_start.Location = new System.Drawing.Point(54, 495);
            this.button_start.Name = "button_start";
            this.button_start.Size = new System.Drawing.Size(134, 36);
            this.button_start.TabIndex = 0;
            this.button_start.Text = "开始游戏";
            this.button_start.UseVisualStyleBackColor = true;
            this.button_start.Click += new System.EventHandler(this.Onstart);
            // 
            // button11
            // 
            this.button11.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.button11.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.button11.FlatAppearance.BorderSize = 0;
            this.button11.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button11.Location = new System.Drawing.Point(61, 150);
            this.button11.Margin = new System.Windows.Forms.Padding(2);
            this.button11.Name = "button11";
            this.button11.Size = new System.Drawing.Size(80, 80);
            this.button11.TabIndex = 5;
            this.button11.Text = " ";
            this.button11.UseVisualStyleBackColor = false;
            this.button11.Click += new System.EventHandler(this.OnBnt);
            // 
            // button12
            // 
            this.button12.BackColor = System.Drawing.SystemColors.Control;
            this.button12.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.button12.FlatAppearance.BorderSize = 0;
            this.button12.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button12.Location = new System.Drawing.Point(146, 150);
            this.button12.Margin = new System.Windows.Forms.Padding(2);
            this.button12.Name = "button12";
            this.button12.Size = new System.Drawing.Size(80, 80);
            this.button12.TabIndex = 6;
            this.button12.Text = " ";
            this.button12.UseVisualStyleBackColor = false;
            this.button12.Click += new System.EventHandler(this.OnBnt);
            // 
            // button13
            // 
            this.button13.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.button13.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.button13.FlatAppearance.BorderSize = 0;
            this.button13.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button13.Location = new System.Drawing.Point(232, 150);
            this.button13.Margin = new System.Windows.Forms.Padding(2);
            this.button13.Name = "button13";
            this.button13.Size = new System.Drawing.Size(80, 80);
            this.button13.TabIndex = 7;
            this.button13.Text = " ";
            this.button13.UseVisualStyleBackColor = false;
            this.button13.Click += new System.EventHandler(this.OnBnt);
            // 
            // button21
            // 
            this.button21.BackColor = System.Drawing.SystemColors.Control;
            this.button21.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.button21.FlatAppearance.BorderSize = 0;
            this.button21.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button21.Location = new System.Drawing.Point(61, 236);
            this.button21.Margin = new System.Windows.Forms.Padding(2);
            this.button21.Name = "button21";
            this.button21.Size = new System.Drawing.Size(80, 80);
            this.button21.TabIndex = 8;
            this.button21.Text = " ";
            this.button21.UseVisualStyleBackColor = false;
            this.button21.Click += new System.EventHandler(this.OnBnt);
            // 
            // button22
            // 
            this.button22.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.button22.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.button22.FlatAppearance.BorderSize = 0;
            this.button22.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button22.Location = new System.Drawing.Point(146, 236);
            this.button22.Margin = new System.Windows.Forms.Padding(2);
            this.button22.Name = "button22";
            this.button22.Size = new System.Drawing.Size(80, 80);
            this.button22.TabIndex = 9;
            this.button22.Text = " ";
            this.button22.UseVisualStyleBackColor = false;
            this.button22.Click += new System.EventHandler(this.OnBnt);
            // 
            // button23
            // 
            this.button23.BackColor = System.Drawing.SystemColors.Control;
            this.button23.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.button23.FlatAppearance.BorderSize = 0;
            this.button23.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button23.Font = new System.Drawing.Font("宋体", 50F);
            this.button23.Location = new System.Drawing.Point(232, 236);
            this.button23.Margin = new System.Windows.Forms.Padding(2);
            this.button23.Name = "button23";
            this.button23.Size = new System.Drawing.Size(80, 80);
            this.button23.TabIndex = 10;
            this.button23.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            this.button23.UseVisualStyleBackColor = false;
            this.button23.Click += new System.EventHandler(this.OnBnt);
            // 
            // button31
            // 
            this.button31.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.button31.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.button31.FlatAppearance.BorderSize = 0;
            this.button31.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button31.Location = new System.Drawing.Point(61, 322);
            this.button31.Margin = new System.Windows.Forms.Padding(2);
            this.button31.Name = "button31";
            this.button31.Size = new System.Drawing.Size(80, 80);
            this.button31.TabIndex = 11;
            this.button31.Text = " ";
            this.button31.UseVisualStyleBackColor = false;
            this.button31.Click += new System.EventHandler(this.OnBnt);
            // 
            // button32
            // 
            this.button32.BackColor = System.Drawing.SystemColors.Control;
            this.button32.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.button32.FlatAppearance.BorderSize = 0;
            this.button32.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button32.Location = new System.Drawing.Point(146, 322);
            this.button32.Margin = new System.Windows.Forms.Padding(2);
            this.button32.Name = "button32";
            this.button32.Size = new System.Drawing.Size(80, 80);
            this.button32.TabIndex = 12;
            this.button32.Text = " ";
            this.button32.UseVisualStyleBackColor = false;
            this.button32.Click += new System.EventHandler(this.OnBnt);
            // 
            // button33
            // 
            this.button33.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.button33.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.button33.FlatAppearance.BorderSize = 0;
            this.button33.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button33.Location = new System.Drawing.Point(232, 322);
            this.button33.Margin = new System.Windows.Forms.Padding(2);
            this.button33.Name = "button33";
            this.button33.Size = new System.Drawing.Size(80, 80);
            this.button33.TabIndex = 13;
            this.button33.Text = " ";
            this.button33.UseVisualStyleBackColor = false;
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
            this.选择棋子ToolStripMenuItem.Size = new System.Drawing.Size(124, 22);
            this.选择棋子ToolStripMenuItem.Text = "选择棋子";
            // 
            // 玩家1ToolStripMenuItem
            // 
            this.玩家1ToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("玩家1ToolStripMenuItem.Image")));
            this.玩家1ToolStripMenuItem.Name = "玩家1ToolStripMenuItem";
            this.玩家1ToolStripMenuItem.Size = new System.Drawing.Size(107, 22);
            this.玩家1ToolStripMenuItem.Text = "玩家1";
            // 
            // 玩家2ToolStripMenuItem
            // 
            this.玩家2ToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("玩家2ToolStripMenuItem.Image")));
            this.玩家2ToolStripMenuItem.Name = "玩家2ToolStripMenuItem";
            this.玩家2ToolStripMenuItem.Size = new System.Drawing.Size(107, 22);
            this.玩家2ToolStripMenuItem.Text = "玩家2";
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
            this.Tips.BackColor = System.Drawing.SystemColors.GradientActiveCaption;
            this.Tips.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Tips.ForeColor = System.Drawing.Color.RoyalBlue;
            this.Tips.Location = new System.Drawing.Point(65, 432);
            this.Tips.Margin = new System.Windows.Forms.Padding(1, 0, 1, 0);
            this.Tips.Name = "Tips";
            this.Tips.Size = new System.Drawing.Size(263, 41);
            this.Tips.TabIndex = 16;
            this.Tips.Text = "选择模式及先后手，然后点击按钮开始游戏（默认AI先手）";
            // 
            // button_restart
            // 
            this.button_restart.Font = new System.Drawing.Font("宋体", 15F);
            this.button_restart.ForeColor = System.Drawing.Color.DarkRed;
            this.button_restart.Location = new System.Drawing.Point(194, 495);
            this.button_restart.Name = "button_restart";
            this.button_restart.Size = new System.Drawing.Size(134, 36);
            this.button_restart.TabIndex = 17;
            this.button_restart.Text = "重新开始";
            this.button_restart.UseVisualStyleBackColor = true;
            this.button_restart.Click += new System.EventHandler(this.OnReStart);
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(36, 36);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.游戏模式ToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(376, 44);
            this.menuStrip1.TabIndex = 19;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // 游戏模式ToolStripMenuItem
            // 
            this.游戏模式ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.人机对战ToolStripMenuItem,
            this.人人对战ToolStripMenuItem});
            this.游戏模式ToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("游戏模式ToolStripMenuItem.Image")));
            this.游戏模式ToolStripMenuItem.Name = "游戏模式ToolStripMenuItem";
            this.游戏模式ToolStripMenuItem.Size = new System.Drawing.Size(104, 40);
            this.游戏模式ToolStripMenuItem.Text = "游戏模式";
            // 
            // 人机对战ToolStripMenuItem
            // 
            this.人机对战ToolStripMenuItem.Checked = true;
            this.人机对战ToolStripMenuItem.CheckState = System.Windows.Forms.CheckState.Checked;
            this.人机对战ToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("人机对战ToolStripMenuItem.Image")));
            this.人机对战ToolStripMenuItem.Name = "人机对战ToolStripMenuItem";
            this.人机对战ToolStripMenuItem.ShowShortcutKeys = false;
            this.人机对战ToolStripMenuItem.Size = new System.Drawing.Size(148, 22);
            this.人机对战ToolStripMenuItem.Text = "人机对战(默认)";
            this.人机对战ToolStripMenuItem.Click += new System.EventHandler(this.ManVSMachine);
            // 
            // 人人对战ToolStripMenuItem
            // 
            this.人人对战ToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("人人对战ToolStripMenuItem.Image")));
            this.人人对战ToolStripMenuItem.Name = "人人对战ToolStripMenuItem";
            this.人人对战ToolStripMenuItem.Size = new System.Drawing.Size(148, 22);
            this.人人对战ToolStripMenuItem.Text = "人人对战";
            this.人人对战ToolStripMenuItem.Click += new System.EventHandler(this.ManVsMan);
            // 
            // pictureBox1
            // 
            this.pictureBox1.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("pictureBox1.BackgroundImage")));
            this.pictureBox1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.pictureBox1.Location = new System.Drawing.Point(54, 56);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(80, 78);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.pictureBox1.TabIndex = 20;
            this.pictureBox1.TabStop = false;
            // 
            // pictureBox3
            // 
            this.pictureBox3.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("pictureBox3.BackgroundImage")));
            this.pictureBox3.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.pictureBox3.Location = new System.Drawing.Point(239, 57);
            this.pictureBox3.Name = "pictureBox3";
            this.pictureBox3.Size = new System.Drawing.Size(78, 77);
            this.pictureBox3.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.pictureBox3.TabIndex = 22;
            this.pictureBox3.TabStop = false;
            // 
            // pictureBox2
            // 
            this.pictureBox2.BackColor = System.Drawing.Color.Transparent;
            this.pictureBox2.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("pictureBox2.BackgroundImage")));
            this.pictureBox2.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.pictureBox2.Location = new System.Drawing.Point(140, 68);
            this.pictureBox2.Name = "pictureBox2";
            this.pictureBox2.Size = new System.Drawing.Size(93, 50);
            this.pictureBox2.TabIndex = 23;
            this.pictureBox2.TabStop = false;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.BackColor = System.Drawing.Color.White;
            this.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("$this.BackgroundImage")));
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.ClientSize = new System.Drawing.Size(376, 554);
            this.Controls.Add(this.pictureBox2);
            this.Controls.Add(this.pictureBox3);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.button_restart);
            this.Controls.Add(this.Tips);
            this.Controls.Add(this.button33);
            this.Controls.Add(this.button32);
            this.Controls.Add(this.button31);
            this.Controls.Add(this.button23);
            this.Controls.Add(this.button22);
            this.Controls.Add(this.button21);
            this.Controls.Add(this.button13);
            this.Controls.Add(this.button12);
            this.Controls.Add(this.button11);
            this.Controls.Add(this.button_start);
            this.Controls.Add(this.menuStrip1);
            this.ForeColor = System.Drawing.SystemColors.InfoText;
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "井字棋小程序";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button_start;
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
        private System.Windows.Forms.ToolStripMenuItem AIToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 选择棋子ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 玩家1ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 玩家2ToolStripMenuItem;
        private System.Windows.Forms.ImageList imageList1;
        private System.ComponentModel.BackgroundWorker backgroundWorker1;
        private System.Windows.Forms.Label Tips;
        private System.Windows.Forms.Button button_restart;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem 游戏模式ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 人机对战ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 人人对战ToolStripMenuItem;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.PictureBox pictureBox3;
        private System.Windows.Forms.PictureBox pictureBox2;
    }
}

