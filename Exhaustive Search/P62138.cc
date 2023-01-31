/*
There are n tasks, which have to be done one by one. Some tasks must be done before others: there are m precedence relations between tasks. Write a program that prints all possible ways to order the n tasks according to the m given precedences.

Input consists of a natural number n ≥ 1, followed by a natural number m, followed by m different pairs x, y, indicating that task x must be done before task y. Suppose that the tasks are numbered from 0 to n − 1.

Print, one per line and in lexicographic order, all the ways of sorting the n tasks according to the m given precedences. There will always be at least one solution.
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

void escriu(vector<int>& sol_parcial)
{
    for (int i = 0; i < sol_parcial.size(); ++i) {
        if (i == 0)
            cout << sol_parcial[i];
        else
            cout << " " << sol_parcial[i];
    }
    cout << endl;
}

void genera(const vector<vector<int>>& precedences, vector<int>& before, vector<int>& sol_parcial, int k, int n)
{
    if (k == n)
        escriu(sol_parcial);
    else {
        for (int i = 0; i < n; ++i) {
            if (before[i] == 0) {

                // Marquem i com a feta servir
                before[i] = -1;
                sol_parcial[k] = i;

                // Restarli un predecessor als predecessors de i.
                for (int a : precedences[i]) {
                    --before[a];
                }
                genera(precedences, before, sol_parcial, k + 1, n);

                // Des-fer els canvis de la crida.
                before[i] = 0;
                for (int a : precedences[i]) {
                    ++before[a];
                }
            }
        }
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> precedences(n); // 1 si i preceideix a j, 0 altrament.
    vector<int> before(n, 0);
    for (int i = 0; i < m; ++i) {
        int x, y; // x precedeix a y
        cin >> x >> y;
        precedences[x].push_back(y);
        ++before[y]; // quanta gent va abans que y.
    }

    vector<int> sol_parcial(n);
    genera(precedences, before, sol_parcial, 0, n);
}
