
/*

Write a program that, given an integer number s and n integer numbers x1, …, xn, prints all the subsets (maybe with repeated numbers, but using every xi at most once) whose sum is exactly s.

Input consists of an integer number s, followed by a number n > 0, followed by x1, …, xn.

Print all the subsets whose sum is s that can be made up with x1, …, xn.

*/

#include <iostream>
#include <vector>
using namespace std;

void write(const vector<int>& ns, const vector<bool>& used)
{
    bool first = true;
    cout << "{";
    for (int i = 0; i < ns.size(); ++i) {
        if (used[i]) {
            if (first) {
                cout << ns[i];
                first = false;
            } else {
                cout << "," << ns[i];
            }
        }
    }
    cout << "}" << endl;
}

void exh(int k, const vector<int>& ns, int sum, vector<bool>& used, int s, bool nw)
{
    if (k == ns.size())return;

    /*
        If sum has been accomplished and it is not a repeated solution, 
        then write so
    */

    if (s == sum && nw)write(ns, used);
    /*
        Decide whether to put or skip the k-th number in ns vector
    */
    used[k] = true;
    exh(k + 1, ns, sum + ns[k], used, s, true);
    used[k] = false;
    exh(k + 1, ns, sum, used, s, false);
}

int main()
{
    int s, n;
    cin >> s >> n;
    vector<int> ns(n);

    for (int i = 0; i < n; ++i) {
        cin >> ns[i];
    }
    vector<bool> used(n, false);
    exh(0, ns, 0, used, s, true);
}