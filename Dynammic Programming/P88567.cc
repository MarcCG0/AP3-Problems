/*
Given a grid with uppercase letters, compute the sum of the values of the letters in each rectangle with a corner in the upper-left extreme. The values of the letters are ’A’=1, ’B’=1+2=3, ’C’=1+2+3=6, ’D’=1+2+3+4=10, etcetera, up to ’Z’=351.

Input consists of 0< r≤ 500 lines, all of them with the same number of uppercase letters 0<c≤ 500.

Print r lines with c numbers each. The j-th number of the i-th row must be the sum of the values of the letters of the rectangle whose corners are the first letter of the input, and the j-th letter of the i-th row.
*/
#include <iostream>
#include <vector>

using namespace std;

using Matrix = vector<vector<int>>;

void treat_line(vector<int>& treated_line, const string& line)
{
    for (char a : line) {
        int num = a - 'A' + 1;
        treated_line.push_back(num * (num + 1) / 2);
    }
}

void write_table(Matrix& T)
{
    int fil = T.size();
    int col = T[0].size();

    for (int i = 0; i < fil; ++i) {
        for (int j = 0; j < col; ++j) {
            if (i > 0)
                T[i][j] += T[i - 1][j];
            if (j > 0)
                T[i][j] += T[i][j - 1];
            if (j > 0 && i > 0)
                T[i][j] -= T[i - 1][j - 1];
            if (j == 0)
                cout << T[i][j];
            else
                cout << " " << T[i][j];
        }
        cout << endl;
    }
}

int main()
{

    string line;
    Matrix T;
    while (cin >> line) {
        vector<int> treated_line;
        treat_line(treated_line, line);
        T.push_back(treated_line);
    }
    write_table(T);
}