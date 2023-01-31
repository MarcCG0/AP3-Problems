/*
Two friends, Arthur and Bob, are playing computer games, and they have decided to store their scores. When they stop playing, Arthur and Bob want to determine the length of the maximum subsequence of scores that they have in common.

For instance, if the scores of Arthur are [8, 12, 6, 9, 2], and those of Bob are [12, 6, 8, 2], then the maximum subsequence that they have in common is [12, 6, 2], which has length 3. Note that a subsequence does not have to be made up of consecutive elements, but we must preserve the order of the scores.

Input consists of several cases. Each case begins with two numbers 0≤ M≤ 1000 and 0≤ N≤ 1000, representing the length of the subsequences of Arthur and Bob, respectively. Follow the M numbers of Arthur, and the N numbers of Bob. All the numbers are natural.

For every case, print the length of the longest common subsequence.
*/
#include <iostream>
#include <vector>

using namespace std;
using dyn = vector<vector<int>>;

int max_length(vector<int>& arthur, vector<int>& bob, dyn& st, int i_a, int i_b)
{
    if (i_a == arthur.size() or i_b == bob.size())
        return 0;

    if (st[i_a][i_b] != -1)
        return st[i_a][i_b];

    if (arthur[i_a] == bob[i_b])
        return st[i_a][i_b] = 1 + max_length(arthur, bob, st, i_a + 1, i_b + 1);
    else
        return st[i_a][i_b] = max(max_length(arthur, bob, st, i_a + 1, i_b), max_length(arthur, bob, st, i_a, i_b + 1));
}

int main()
{
    int n, m;
    while (cin >> m >> n) {
        vector<int> arthur(m);
        vector<int> bob(n);
        for (int& a : arthur)
            cin >> a;
        for (int& b : bob)
            cin >> b;
        dyn st(m + 1, vector<int>(n + 1, -1));
        cout << max_length(arthur, bob, st, 0, 0) << endl;
    }
}