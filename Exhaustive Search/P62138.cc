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