using System;
using System.Collections.Generic;
using System.Text;

namespace Search
{
    class Ai
    {
        public int[] winner = new int[1 << 20];
        public int state;
        public int winrow(int[,] a, int id)
        {
            if (a[id, 0] == a[id, 1] && a[id, 1] == a[id, 2] && a[id, 0] > 0) return a[id, 0];
            else return -1;
        }
        public int wincol(int[,] a, int id)
        {
            if (a[0, id] == a[1, id] && a[1, id] == a[2, id] && a[0, id] > 0) return a[0, id];
            else return -1;
        }
        public int windiag(int[,] a)
        {
            if (a[0, 0] == a[1, 1] && a[1, 1] == a[2, 2] && a[0, 0] > 0) return a[0, 0];
            if (a[0, 2] == a[1, 1] && a[1, 1] == a[2, 0] && a[2, 0] > 0) return a[0, 2];
            return -1;
        }
        public bool isfull(int x)
        {
            int[,] a = new int[3, 3];
            int t, s;
            t = s = 0;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                {
                    a[i, j] = (x >> t) % 4;
                    if (a[i, j] > 0) s++;
                    t += 2;
                }
            return (s == 9);
        }
        public int whowin(int x)
        {
            int[,] a = new int[3, 3];
            int t;
            t = 0;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                {
                    a[i, j] = (x >> t) % 4;
                    t += 2;
                }
            for (int i = 0; i < 3; ++i) if (winrow(a, i) > 0) return winrow(a, i);
            for (int i = 0; i < 3; ++i) if (wincol(a, i) > 0) return wincol(a, i);
            if (windiag(a) > -1) return windiag(a);
            return 0;
        }
        public int put(int s,int x, int y, int z)
        {
            int t;
            t = x * 3 + y;
            t *= 2;
            if ((s >> t) % 4 > 0) return -1;
            else return s + (z << t);
        }
        public void dfs(int s, int who)
        {
            if (winner[s] >= 0) return;
            int t = whowin(s);
            if (t > 0)
            {
                winner[s] = t;
                return;
            }
            if (isfull(s))
            {
                winner[s] = 0;
                return;
            }
            t = 0;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                {
                    int ns = put(s, i, j, who);  //s是当前的状态，i,j表示棋子的落子，who代表谁下子
                    if (ns == -1) continue;
                    dfs(ns, 3 - who);
                    t++;
                    if (winner[ns] == 3 - who) t--;
                    if (winner[ns] == who)
                    {
                        winner[s] = who;
                        return;
                    }
                }
            if (t == 0) winner[s] = 3 - who;
            else winner[s] = 0;
        }
        public void getnext(int s, ref int x, ref int y)
        {
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                {
                    int ns = put(s, i, j, 2);
                    if (ns == -1) continue;
                    if (winner[ns] == 2)
                    {
                        x = i; y = j; return;
                    }
                }
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                {
                    int ns = put(s, i, j, 2);
                    if (ns == -1) continue;
                    if (winner[ns] == 0)
                    {
                        x = i; y = j; return;
                    }
                }
            x = y = -1;
        }
        public void init()
        {
            state = 0;
            for (int i = 0; i < winner.Length; i++)
            {
                winner[i] = -1;
            }
        }

    }

}
