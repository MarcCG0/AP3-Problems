/*
Given a directed and complete graph with n vertices, and an initial vertex x, compute the maximum cost of all the paths without repeated vertices that begin at x. The given graph is represented by an n × n matrix M, where for every pair (i, j) with i ≠ j, mij is the (perhaps negative) cost of the arc from i to j.

For instance, the maximum cost of the first test is 80, corresponding to the path 1 → 0 → 3, with cost −10 + 90 = 80.


Input consists of the number of vertices n, followed by the matrix M (n lines, each one with n integer numbers), followed by the initial vertex x. Vertices are numbered from 0 to n−1. You can assume 1 ≤ n ≤ 11, 0 ≤ x < n, that the diagonal has only zeros, and that the rest of numbers are between −106 and 106.

Print the maximum cost of all the paths without repeated vertices that begin at x.
*/
#include <iostream>
#include <vector>

using namespace std;
using Matrix = vector<vector<int>>;

void desopt(const Matrix& M, vector<bool>& used, int k, int& m_c, int p_c, int v)
{
    if (k == M.size())
        return;

    if (m_c < p_c)
        m_c = p_c;

    for (int i = 0; i < M.size(); ++i) {
        if (not used[i]) {
            used[i] = true;
            desopt(M, used, k + 1, m_c, p_c + M[v][i], i);
            used[i] = false;
        }
    }
}

int mx_cost(Matrix& M, int x)
{
    int m_c = 0;
    int n = M.size();
    vector<bool> used(n, false);
    used[x] = true;
    desopt(M, used, 0, m_c, 0, x);
    return m_c;
}

int main()
{
    int n;
    cin >> n;
    Matrix M(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> M[i][j];
    int x;
    cin >> x;
    cout << mx_cost(M, x) << endl;
}