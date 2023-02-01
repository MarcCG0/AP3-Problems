/*
Some problems are so classic that barely need a statement. For this one, please compute the minimum cost to insert letters into two words w1 and w2 to make them identical. Both words are made up of only letters chosen among the n smallest lowercase letters (for instance, for n=4, the alphabet is {a, b, c, d}). For every letter (call it x), inserting an x in any place in any word has cost Ix.

Input consists of several cases. Each case begins with 2≤ n≤ 26, followed by n strictly positive natural numbers Ia, Ib, Ic, …. Follow two words w1 and w2 made up of between 1 and 1000 lowercase letters chosen among the n smallest letters. Assume 1≤ Ix≤ 1000 for every letter x.

For every case, print the minimum cost to make w1 and w2 identical.
*/
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int cost(const string& a, int b_j, const vector<int>& c)
{
    return c[a[b_j] - 'a'];
}

int f(int a_i, int b_j, const string& a, const string& b, const vector<int>& c, vector<vector<int>>& M)
{
    // If we are done, edition required costs 0
    if (a_i == a.size() && b_j == b.size())
        return 0; 
    // Dynamic Programming: return previously computed results
    else if (M[a_i][b_j] != -1)
        return M[a_i][b_j];
    // Recursive cases
    else if (a_i == a.size()) 
        return M[a_i][b_j] = cost(b, b_j, c) + f(a_i, b_j + 1, a, b, c, M);

    else if (b_j == b.size())
        return M[a_i][b_j] = cost(a, a_i, c) + f(a_i + 1, b_j, a, b, c, M);

    else if (a[a_i] == b[b_j]) 
        return M[a_i][b_j] = f(a_i + 1, b_j + 1, a, b, c, M);

    else 
        return M[a_i][b_j] = min(cost(a, a_i, c) + f(a_i + 1, b_j, a, b, c, M), cost(b, b_j, c) + f(a_i, b_j + 1, a, b, c, M));
}

int main()
{
    int n;
    while (cin >> n) {
        vector<int> cost(n);
        for (int i = 0; i < n; ++i) {
            cin >> cost[i];
        }
        string a, b;
        cin >> a >> b;
        int n = a.size();
        int m = b.size();
        vector<vector<int>> M(n + 1, vector<int>(m + 1, -1));
        cout << f(0, 0, a, b, cost, M) << endl;
    }
}
