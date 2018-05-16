using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Search;

namespace tictactoe
{
    enum Operation
    {
       noai,ai
    }

    enum Turn
    {
        firstChess=1, secondChess=2
    }
    enum State
    {
        ready, running, end
    }
    enum ChessResult
    {
        firstWin,secondWin,noWin
    }
    public partial class Form1 : Form
    {
        private int[,] chessState;
        private Turn turn;
        private State state;
        private ChessResult re;
        private int count;
        private Operation op;
        private bool isAiTurn;
        private bool isAiFirst;
        private Ai ai = new Ai();
        DialogResult dr_AI = DialogResult.Yes;
        DialogResult dr_M = DialogResult.No;
        bool mode = true;
        public Form1()
        {
            op = Operation.ai;
            state = State.ready;
            turn = Turn.firstChess;
            InitializeComponent();
        }
        private bool CheckWin()
        {
            for (int i = 0; i < 3; i++)
            {
                if (chessState[i, 0] + chessState[i, 1] + chessState[i, 2] == 3||chessState[0,i]+chessState[1,i]+chessState[2,i]==3)
                {
                    re = ChessResult.firstWin;
                    return true;
                }
                if (chessState[i, 0] + chessState[i, 1] + chessState[i, 2] == -3|| chessState[0, i] + chessState[1, i] + chessState[2, i] == -3)
                {
                    re = ChessResult.secondWin;
                    return true;
                }
            }
            if(chessState[0,0]+chessState[1,1]+chessState[2,2]==3||chessState[0,2]+chessState[1,1]+chessState[2,0]==3)
            {
                re = ChessResult.firstWin;
                return true;
            }
            if (chessState[0, 0] + chessState[1, 1] + chessState[2, 2] == -3 || chessState[0, 2] + chessState[1, 1] + chessState[2, 0] == -3)
            {
                re = ChessResult.secondWin;
                return true;
            }
            if(count==9)
            {
                re = ChessResult.noWin; 
                return true;
            }
            return false;
        }


        private void Onstart(object sender, EventArgs e)
        {
            Tips.Tag = "准备中。";
            count = 0;
            chessState = new int[3, 3];
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    chessState[i, j] = 0;
            state = State.running;
            if (dr_AI == DialogResult.Yes && mode) AiFisrt();
            if (dr_AI == DialogResult.No && mode) AiSecond();
            if (op == Operation.ai )
            {
                ai.init();
                if(isAiTurn)
                {
                    int x=-1, y=-1;
                    if (isAiFirst)
                    {
                        ai.dfs(ai.state, 2);
                        ai.getnext(ai.state, ref x, ref y);
                        ai.state=ai.put(ai.state,x, y, 2);

                        chessState[x,y] = 1;
                        loadImage(x, y);
                        turn = Turn.secondChess;
                        isAiTurn = false;
                        count++;
                    }
                }
            }
            else
            {
                if (dr_M == DialogResult.Yes && !mode) NoAiPlayerOneFirst();
                if (dr_M == DialogResult.No && !mode) NoAiPlayerTwoFirst();
            }
            button11.Enabled = true;
            button12.Enabled = true;
            button13.Enabled = true;
            button21.Enabled = true;
            button22.Enabled = true;
            button23.Enabled = true;
            button31.Enabled = true;
            button32.Enabled = true;
            button33.Enabled = true;
        }

        private void OnBnt(object sender, EventArgs e)
        {   
            Button btn = (Button) sender;
            int row = Convert.ToInt32(btn.Name.Substring(btn.Name.Length - 2, 1)) - 1;
            int column = Convert.ToInt32(btn.Name.Substring(btn.Name.Length - 1, 1)) - 1;
            if (state == State.running&&btn.Enabled==true&&isAiTurn==false)  //human ' s turn
            {
                count++;
                if(turn == Turn.firstChess)
                {
                    btn.BackgroundImage = imageList1.Images[0];
                    turn = Turn.secondChess;
                    chessState[row, column] = 1;
                    
                }
                else
                {
                    btn.BackgroundImage = imageList1.Images[1];
                    turn = Turn.firstChess;
                    chessState[row, column] = -1;
                }
                if (op == Operation.ai)
                {
                    ai.state= ai.put(ai.state, row, column, 1); // 人是2
                    isAiTurn = true;
                }

                btn.Enabled = false;
                if (CheckWin()) {
                    state = State.end;
                    showResult();
                }
                if (op == Operation.ai)
                {

                    int x = -1, y = -1;
                    ai.dfs(ai.state, 2);
                    ai.getnext(ai.state, ref x, ref y);
                    if(x < 0 || y < 0)
                    {
                        re = ChessResult.noWin;
                        showResult();
                        state = State.end;
                        return ;
                    }
                    ai.state = ai.put(ai.state, x, y, 2); //机器2
                    loadImage(x, y);
                    if(isAiFirst) chessState[x,y] = 1;
                    else chessState[x, y] = -1;
                    if (turn == Turn.firstChess)
                        turn = Turn.secondChess;
                    else turn = Turn.firstChess;
                    isAiTurn = false;
                    count++;
                    if (CheckWin())
                    {
                        state = State.end;
                        showResult();
                    }
                }
            }
        }

        private void showResult()
        {

            if (op == Operation.noai)
            {
                if (re == ChessResult.firstWin)
                {
                    Tips.Text = "第一位选手获得了胜利！";
                }
                if (re == ChessResult.secondWin)
                {
                    Tips.Text = "第二位选手获得了胜利！";
                }
                if (re == ChessResult.noWin)
                {
                    Tips.Text = "平局";
                }
            }
            else
            {
                if(isAiFirst)
                {
                    if (re == ChessResult.firstWin)
                    {
                        Tips.Text = "ai选手获得了胜利！";
                    }
                    if (re == ChessResult.secondWin)
                    {
                        Tips.Text = "人类选手获得了胜利！";
                    }
                }
                else
                {
                    if (re == ChessResult.firstWin)
                    {
                        Tips.Text = "人类选手获得了胜利！"; 
                    }
                    if (re == ChessResult.secondWin)
                    {
                        Tips.Text = "ai选手获得了胜利！";
                    }
                }
                if (re == ChessResult.noWin)
                {
                    Tips.Text = "平局";
                }
            }
        }

  

        private void OnReStart(object sender, EventArgs e)
        {
            count = 0;
            button11.BackgroundImage = null;
            button12.BackgroundImage = null;
            button13.BackgroundImage = null;
            button21.BackgroundImage = null;
            button22.BackgroundImage = null;
            button23.BackgroundImage = null;
            button31.BackgroundImage = null;
            button32.BackgroundImage = null;
            button33.BackgroundImage = null;
            button11.Enabled = true;
            button12.Enabled = true;
            button13.Enabled = true;
            button21.Enabled = true;
            button22.Enabled = true;
            button23.Enabled = true;
            button31.Enabled = true;
            button32.Enabled = true;
            button33.Enabled = true;
            Tips.Tag = "准备中。";
            Tips.Text = "游戏已重开";  //重置Tips提醒字符串，覆盖上一局结果
            chessState = new int[3, 3];
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    chessState[i, j] = 0;
            state = State.running;
            if (dr_AI == DialogResult.Yes && mode) AiFisrt();
            if (dr_AI == DialogResult.No && mode) AiSecond();
            if (op == Operation.ai)
            {

                ai.init();
                if (isAiTurn)
                {
                    int x = 0, y = 0;
                    if (isAiFirst)
                    {
                        ai.dfs(ai.state, 2);
                        ai.getnext(ai.state, ref x, ref y);
                        ai.state = ai.put(ai.state, x, y, 2);
                        chessState[x, y] = 1;
                        loadImage(x, y);
                        count++;
                        turn = Turn.secondChess;
                        isAiTurn = false;

                    }
                }
            }
            else
            {
                if (dr_M == DialogResult.Yes && !mode) NoAiPlayerOneFirst();
                if (dr_M == DialogResult.No && !mode) NoAiPlayerTwoFirst();
            }   
        }

        private void AiFisrt()
        {
            op = Operation.ai;
            turn = Turn.firstChess;
            isAiTurn = true;
            isAiFirst = true ;
        }
        private void AiSecond()
        {
            op = Operation.ai;
            turn = Turn.firstChess;
            isAiTurn = false;
            isAiFirst = false;
        }
        private void NoAiPlayerOneFirst()
        {
            op = Operation.noai;
            turn = Turn.firstChess;
            isAiTurn = false;
            isAiFirst = false;
        }
        private void NoAiPlayerTwoFirst()
        {
            op = Operation.noai;
            turn = Turn.secondChess;
            isAiTurn = false;
            isAiFirst = false;
        }
        public void loadImage(int x,int y)
        {
            int who = 1;
            if (isAiFirst) who = 1;
            else who = 2;
            if(x==0&&y==0)
            {
                button11.Enabled = false;
                button11.BackgroundImage = imageList1.Images[who - 1];
            }
            if (x == 0 && y == 1)
            {
                button12.Enabled = false;
                button12.BackgroundImage = imageList1.Images[who - 1];
            }
            if (x == 0 && y == 2)
            {
                button13.Enabled = false;
                button13.BackgroundImage = imageList1.Images[who - 1];
            }
            if (x == 1 && y == 0)
            {
                button21.Enabled = false;
                button21.BackgroundImage = imageList1.Images[who - 1];
            }
            if (x == 1&& y == 1)
            {
                button22.Enabled = false;
                button22.BackgroundImage = imageList1.Images[who - 1];

            }
            if (x == 1 && y == 2)
            {
                button23.Enabled = false;
                button23.BackgroundImage = imageList1.Images[who - 1];
            }
            if (x == 2 && y == 0)
            {
                button31.Enabled = false;
                button31.BackgroundImage = imageList1.Images[who - 1];
            }
            if (x == 2&& y == 1)
            {
                button32.Enabled = false;
                button32.BackgroundImage = imageList1.Images[who - 1];
            }
            if (x == 2 && y == 2)
            {
                button33.Enabled = false;
                button33.BackgroundImage = imageList1.Images[who - 1];
            }

        }

     

        private void ManVSMachine(object sender, EventArgs e)
        {
            op = Operation.ai;

            mode = true;
            dr_AI = MessageBox.Show("是否电脑先手", "人机先后手对战选择", MessageBoxButtons.YesNo,
                     MessageBoxIcon.Warning, MessageBoxDefaultButton.Button1);
            if (dr_AI == DialogResult.Yes)
            {
                //MessageBox.Show("电脑将先手", "你选择的为“是”按钮");
                AiFisrt();
                OnReStart(null, EventArgs.Empty);
            }
                
            else if (dr_AI == DialogResult.No)
            {
               //MessageBox.Show("玩家将先手", "你选择的为“否”按钮");
                AiSecond();
                OnReStart(null, EventArgs.Empty);
            }    
        }

        private void ManVsMan(object sender, EventArgs e)
        {
            op = Operation.noai;
            mode = false;
            dr_M = MessageBox.Show("是否玩家1（部落）先手", "人人先后手对战选择", MessageBoxButtons.YesNo,
                     MessageBoxIcon.Warning, MessageBoxDefaultButton.Button1);
            if (dr_M == DialogResult.Yes)
            {
               // MessageBox.Show("玩家1（部落）将先手", "你选择的为“是”按钮");
                NoAiPlayerOneFirst();
                OnReStart(null, EventArgs.Empty);
            }

            else if (dr_M == DialogResult.No)
            {
                //MessageBox.Show("玩家2（联盟）将先手", "你选择的为“否”按钮");
                NoAiPlayerTwoFirst();
                OnReStart(null, EventArgs.Empty);
            }
        }
    }
}
