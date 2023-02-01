/*
Your friend selects a number n, and you must show cards whose total value equals n, by using the minimum possible number of cards. Assume that you have an unlimited number of cards of each suit.

Input consists of several cases, each one with a natural number n between 0 and 500000. Input ends with a −1.

For every n, print the corresponding result.
*/

#include <climits>
#include <iostream>
#include <vector>

using namespace std;
const int MAX = 500001;

int main()
{
    vector<int> V(MAX, INT_MAX);
    vector<int> cards = { 1, 5, 8, 14 };
    V[0] = 0;
    for (int i = 1; i < MAX; ++i) {
        for (int value : cards) {
            if (i - value >= 0)
                V[i] = min(V[i], 1 + V[i - value]);
        }
    }

    int n;
    while (cin >> n && n != -1)
        cout << V[n] << endl;
}