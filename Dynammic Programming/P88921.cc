/*
Write a program to compute the number of different paths that allow us to scape from a given maze, by going from the bottom-right cell to the upper-left cell. Every movement must be upwards or to the left. There are prohibited cells that we cannot pass by. There is always at least one path from the entrance to the exit.

Input consists of several cases. Every case begins with the number of rows n and the number of columns m, followed by n lines with m characters each. An ‘X’ indicates a forbidden cell, and a dot indicates a free cell. A special test with n = m = 0 marks the end of input. You can assume 2 ≤ n ≤ 40 and 2 ≤ m ≤ 40.

For every case, print the number of different paths that go from the bottom-right corner to the upper-left corner, with all the movements upwards or to the left. If this number is greater than or equal to 106, instead print “!!!”.
*/

#include <iostream>
#include <vector>

using namespace std;
using Maze = vector<vector<char>>;
const int NIL = -1;
const int MAX = 1000001;

Maze read_maze(int n, int m)
{
    Maze mz(n, vector<char>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> mz[i][j];
        }
    }
    return mz;
}

int exh_maze(const Maze& mz, vector<vector<int>>& M, int n_c, int m_c)
{
    if (n_c == NIL or m_c == NIL)
        return 0;

    if (M[n_c][m_c] != NIL)
        return M[n_c][m_c];

    if (mz[n_c][m_c] == 'X')
        return 0;

    if (n_c == 0 and m_c == 0)
        return 1;

    M[n_c][m_c] = exh_maze(mz, M, n_c - 1, m_c) + exh_maze(mz, M, n_c, m_c - 1);
    if (M[n_c][m_c] >= 1e6)
        M[n_c][m_c] = MAX;
    return M[n_c][m_c];
}

int main()
{
    int n, m;
    while (cin >> n >> m && n + m > 0) {
        Maze mz = read_maze(n, m);

        vector<vector<int>> M(n, vector<int>(m, NIL));
        int count = exh_maze(mz, M, n - 1, m - 1);
        if (count >= 1000000)
            cout << "!!!" << endl;
        else
            cout << count << endl;
    }
}