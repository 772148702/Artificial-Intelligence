using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace tictactoe
{
    enum Turn
    {
        firstChess=-1, secondChess=1
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

        public Form1()
        {
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
            chessState = new int[3, 3];
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    chessState[i, j] = 0;
            state = State.running;
            if (radioButton1.Checked == true)
            {
                turn = Turn.firstChess;
            }
            else
            {
                turn = Turn.secondChess;
            }
            count = 0;
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
            if (state == State.running&&btn.Enabled==true)
            {
                count++;
                if(turn==Turn.firstChess)
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
                
                btn.Enabled = false;
                if (CheckWin()) {
                    state = State.end;
                    showResult();
                }
            }
        }

        private void showResult()
        {
            if(re==ChessResult.firstWin)
            {
                Tips.Text= "第一位选手获得了胜利！";
            }
            if(re==ChessResult.secondWin)
            {
                Tips.Text = "第二位选手获得了胜利！";
            }
            if (re == ChessResult.noWin)
            {
                Tips.Text = "平局";
            }
        }

  

        private void OnReStart(object sender, EventArgs e)
        {
            Tips.Tag = "准备中。";
            chessState = new int[3, 3];
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    chessState[i, j] = 0;
            state = State.running;
            if(radioButton1.Checked==true)
            {
                turn = Turn.firstChess;
            }
            else
            {
                turn = Turn.secondChess;
            }
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
        }
    }
}
