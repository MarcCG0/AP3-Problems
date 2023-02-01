/*
Some problems are so classic that barely need a statement. For this one, we ask you to compute the longest subword that two given words have in common. In case of a tie, print the smallest one in alphabetical order.

Input consists of several cases, each with two non-empty words w1 and w2 made up of at most 500 lowercase letters.

For every case, print the longest common subword. In case of a tie, print the smallest one in alphabetical order.
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int UNDEF = -1;

string get_word(const pair<int, int>& p, const string& a)
{
    int i_pos = p.first;
    int lgth = p.second;
    string w = "";
    while (lgth > 0) {
        w.push_back(a[i_pos]);
        --lgth;
        ++i_pos;
    }
    return w;
}

void write(const string& a, const vector<pair<int, int>>& v)
{
    string p = get_word(v[0], a);
    for (uint i = 1; i < v.size(); ++i) {
        p = min(p, get_word(v[i], a));
    }
    for (char& a : p)
        cout << a;
    cout << endl;
}

int main()
{
    string a, b;
    while (cin >> a >> b) {
        int n = a.size(); // i
        int m = b.size(); // j
        int max = 0;
        vector<vector<int>> M(n, vector<int>(m, UNDEF));
        /*
            Compute the following recurrence: 
            LCS[i][j] = #length of lowest common subword
            starting in index i in word a and j in word b.
            LCS[i][j] = 1+LCS[i+1][j+1] iff a[i] == b[j]
            LCS[i][j] = 0 iff a[i] != b[j]. 
        */
        for (int i = n - 1; i >= 0; --i) {
            for (int j = m - 1; j >= 0; --j) {
                if (j == m - 1 or i == n - 1)
                    M[i][j] = a[i] == b[j];
                else if (a[i] == b[j])
                    M[i][j] = 1 + M[i + 1][j + 1];
                else
                    M[i][j] = 0;
                if (M[i][j] > max)
                    max = M[i][j];
            }
        }
        // Get all the tied longest subwords and choose the answer
        vector<pair<int, int>> maxs;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (M[i][j] == max)
                    maxs.push_back({ i, M[i][j] });
            }
        }
        write(a, maxs);
    }
}