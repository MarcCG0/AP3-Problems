/*
Your friend selects a number n, and you must show cards whose total value equals n, by using the minimum possible number of cards. Assume that you have an unlimited number of cards of each suit.

Input consists of several cases, each one with a natural number n between 0 and 500000. Input ends with a −1.

For every n, print the corresponding result.
*/

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
static const int MAX = 500000;
static const int UNDEF = -1;

int card_game(vector<int>& dynamic, int n)
{
    if (n < 0)
        return MAX;

    int& res = dynamic[n];

    if (res != UNDEF)
        return res;

    if (n == 0)
        return res = 0;

    return res = 1 + min(min(card_game(dynamic, n - 1), card_game(dynamic, n - 5)),
                         min(card_game(dynamic, n - 8), card_game(dynamic, n - 14)));
}

int main()
{
    int n;
    vector<int> dynamic(MAX + 1, UNDEF);
    while (cin >> n && n != -1) {
        cout << card_game(dynamic, n) << endl;
    }
}