#include <iostream>
#include <vector>

using namespace std;

using Sudoku = vector<vector<char>>;
using Checker_c = vector<vector<bool>>;
using Checker_f = vector<vector<bool>>;
using Checker_s = vector<vector<bool>>;

void print(const Sudoku& s)
{
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (j == 0)
                cout << s[i][j];
            else
                cout << " " << s[i][j];
        }
        cout << endl;
    }
}

/* Enumeration of subsets
0 1 2
3 4 5
6 7 8
*/
int subset(int i, int j)
{
    // first row
    if (i < 3) {
        if (j < 3)
            return 0;
        if (j < 6)
            return 1;
        return 2;
    }
    // second row
    if (i < 6) {
        if (j < 3)
            return 3;
        if (j < 6)
            return 4;
        return 5;
    }
    // third row
    if (j < 3)
        return 6;
    if (j < 6)
        return 7;
    return 8;
}

/*
    While reading Sudoku, prepares checkers for recursion
    rows & cols (0..8).
*/
void read_sudoku(Sudoku& s, Checker_c& cc, Checker_f& cf, Checker_f& cs)
{
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            cin >> s[i][j];
            if (s[i][j] != '.') {
                int num = s[i][j] - '1';
                int sb = subset(i, j);

                // there's a number assigned
                cc[j][num] = cf[i][num] = cs[sb][num] = true;
            }
        }
    }
}

// Backtrack till finding the unique solution
void solve(Sudoku& s, Checker_c& cc, Checker_f& cf, Checker_f& cs, int i, int j, bool& solved)
{
    if (solved)
        return; // done solving;

    else if (i == 9) {
        solved = true;
        print(s);
        return;

    } else if (j == 9) // when done with a row, solve next row
        solve(s, cc, cf, cs, i + 1, 0, solved);

    else if (s[i][j] != '.') // when position is a number, treat next position
        solve(s, cc, cf, cs, i, j + 1, solved);

    else {
        for (int k = 0; k < 9; ++k) { // 0 is 1 ... 8 is 9
            int sb = subset(i, j);

            // when placing k on (i,j) is valid, place it and recurse
            if (not cf[i][k] && not cc[j][k] && not cs[sb][k]) {
                s[i][j] = char('1' + k);
                cf[i][k] = cc[j][k] = cs[sb][k] = true;
                solve(s, cc, cf, cs, i, j + 1, solved);
                s[i][j] = '.';
                cf[i][k] = cc[j][k] = cs[sb][k] = false;
            }
        }
    }
}

int main()
{
    int n;
    cin >> n;
    cout << n << endl
         << endl;
    while (n > 0) {
        --n;
        Sudoku s(9, vector<char>(9));

        // Checker_cc contains at cc[j][num] whether num has already been placed in column j
        // Checker_cf contains at cc[i][num] whether num has already been placed in row i
        // Checker_cs contains at cc[i][num] whether num has already been placed in subset i
        // Note: subset refers to 3x3 grid

        Checker_c cc(9, vector<bool>(9, false));
        Checker_f cf(9, vector<bool>(9, false));
        Checker_s cs(9, vector<bool>(9, false));

        read_sudoku(s, cc, cf, cs);

        bool solved = false;
        solve(s, cc, cf, cs, 0, 0, solved);

        if (n > 0)
            cout << endl;
    }
}