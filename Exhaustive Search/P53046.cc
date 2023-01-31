/*

Write a program that prints all the permutations of { 1, …, n } with exactly one cycle, for a given n. Assume that the content of the position i of a permutation indicates “the next position to visit”.

For instance, consider the permutation (4,3,2,5,1,7,6). The position 1 has a 4, the position 4 has a 5, and the position 5 has a 1. Therefore, one of the cycles of this permutation is 1 → 4 → 5 → 1. The other two cycles are 2 → 3 → 2 and 6 → 7 → 6. The permutation (3,2,1) has the two cycles 1 → 3 → 1 and 2 → 2. The permutation (3,4,5,6,7,1,2) has only the cycle 1 → 3 → 5 → 7 → 2 → 4 → 6 → 1.

Input consists of a natural number n > 0.

Print all the permutations of { 1, …, n } with only one cycle.

*/

#include <iostream>
#include <vector>

using namespace std;

void write_perm(const vector<int>& perm)
{
    cout << "(";
    for (int i = 1; i < perm.size(); ++i) {
        if (i == 1)
            cout << perm[i];
        else
            cout << "," << perm[i];
    }
    cout << ")" << endl;
}

void genera(vector<int>& perm, vector<bool>& used, int index, int k, int n)
{
    /*
        If current permutation cannot be extended to a pemutation with a unique cycle,
        then stop recursion. 
    */
    if (perm[index] != -1 and k != n)
        return;
    if (perm[index] != -1 && k == n)
        write_perm(perm);

    else if (k < n) {
        for (int i = 1; i <= n; ++i) {
            /*
                Recurse in order to find permutations with a single cycle
            */
            if (not used[i]) {
                used[i] = true;
                perm[index] = i;
                genera(perm, used, i, k + 1, n);
                perm[index] = -1;
                used[i] = false;
            }
        }
    }
}

int main()
{
    int n;
    cin >> n;
    vector<bool> used(n, false);
    vector<int> perm(n + 1, -1);
    genera(perm, used, 1, 0, n);
}