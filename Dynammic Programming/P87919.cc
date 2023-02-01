/*
For this one, given a collection of n coins with different values and a target amount A, we ask you to indicate the way to add up to A by using coins of the largest possible values. In particular, a way is better than another one if the former uses more coins of the largest value; in the event of a tie, if it uses more coins of the second largest value, etc.

Input consists of several cases. Each case begins with the number of coins n between 1 and 100, followed by n different integer numbers v1, …, vn, where 1≤ vi≤ 10000. Finally, we have an integer number 1≤ A≤ 100000.

For every case, print in non-increasing order the necessary coins to get A, choosing the combination with coins of largest value in case of a tie. If there is no solution, print −1.
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int UNDEF = -1;

bool possible(const vector<int>& coins, int A, vector<int>& M)
{
    if (A < 0)
        return false;
    if (A == 0)
        return true;

    if (M[A] != UNDEF)
        return M[A] != -2;

    for (uint i = 0; i < coins.size(); ++i) {
        if (possible(coins, A - coins[i], M)) {
            M[A] = coins[i];
            return true;
        }
    }
    M[A] = -2;
    return false;
}

void best_comb(const vector<int>& coins, int A)
{
    vector<int> M(A + 1, UNDEF);
    if (possible(coins, A, M)) {
        bool first = true;

        while (A != 0) {
            if (first) {
                first = false;
                cout << M[A];
            } else
                cout << "," << M[A];
            A -= M[A];
        }
        cout << endl;
    } else
        cout << "-1" << endl;
}

int main()
{
    int n;
    while (cin >> n) {
        vector<int> coins(n);
        for (int i = 0; i < n; ++i)
            cin >> coins[i];
        sort(coins.begin(), coins.end(), greater<int>());
        int A;
        cin >> A;
        best_comb(coins, A);
    }
}