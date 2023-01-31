/*
Donat dos naturals m i n, heu de construir un nombre x amb els dígits {1, …, n} (exactament un de cada) de manera que cap prefix (no buit) d’x sigui múltiple d’m. Per exemple, amb m=3 i n=4, x=2314 no és un ordre vàlid, perquè 231 és múltiple de 3. En canvi, x=4312 sí que és un ordre vàlid, perquè ni 4, ni 43, ni 431, ni 4312 són múltiples de 3.

A més, teniu una matriu M[1..n][1..n] tal que M[i][j] indica el premi que s’aconsegueix si es posa el dígit j immediatament a la dreta del dígit i. Maximitzeu la suma total de premis.

L’entrada consisteix en diversos casos. Cada cas comença amb m i n, seguits d’M: n files, cadascuna amb n naturals entre 1 i 106, excepte la diagonal, que conté zeros. Podeu suposar 3 ≤ m ≤ 1000 i 2 ≤ n ≤ 9.

Per a cada cas, escriviu el màxim premi possible. Si no es pot construir cap x, escriviu 0.
*/

#include <iostream>
#include <vector>
using namespace std;

void upd_prize(const vector<vector<int>>& M, int& mx_prize, const vector<int>& sol)
{

    int p_prize = 0;
    for (int i = 1; i < sol.size(); ++i) {
        int a = sol[i - 1];
        int b = sol[i];
        p_prize += M[a][b];
    }
    mx_prize = max(mx_prize, p_prize);
}

bool valid(int num, int scaled, int i, int m)
{
    num = num * scaled + i;
    return num % m != 0;
}

void opt(const vector<vector<int>>& M, vector<bool>& used, vector<int>& sol,
    int m, int k, int& mx_prize, int scaled, int num)
{
    if (k == M.size() - 1)
        upd_prize(M, mx_prize, sol);
    else {
        for (int i = 1; i < M.size(); ++i) {
            if (not used[i] && valid(num, scaled, i, m)) {
                used[i] = true;
                sol.push_back(i);
                opt(M, used, sol, m, k + 1, mx_prize, 10, num * scaled + i);
                used[i] = false;
                sol.pop_back();
            }
        }
    }
}

int top_prize(const vector<vector<int>>& M, int m)
{
    int mx_prize = 0;
    int n = M.size();
    vector<bool> used(n + 1);
    vector<int> sol;
    opt(M, used, sol, m, 0, mx_prize, 1, 0);
    return mx_prize;
}

int main()
{
    int m, n;
    while (cin >> m >> n) {

        vector<vector<int>> M(n + 1, vector<int>(n + 1));
        for (int i = 1; i < n + 1; ++i)
            for (int j = 1; j < n + 1; ++j)
                cin >> M[i][j];
        cout << top_prize(M, m) << endl;
    }
}