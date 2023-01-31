/*
Considereu un tauler n × m on a cada casella hi ha un cert nombre de monedes. Es vol cobrir la màxima quantitat de monedes possible amb cavalls dels escacs. L’única restricció és que els cavalls no es poden amenaçar entre si.

L’entrada consisteix en diversos casos, cadascun amb n i m, seguides d’n files amb m naturals cadascuna, que indiquen el nombre de monedes que hi ha a cada casella del tauler. Suposeu n ≥ 2, m ≥ 2, n · m ≤ 30, i que cada casella té entre 0 i 106 monedes.

Per a cada cas, escriviu el màxim nombre de monedes que es poden cobrir amb cavalls que no s’amenacin entre si.
*/

#include <iostream>
#include <vector>
using namespace std;

void opt(const vector<vector<int>>& M, vector<vector<bool>>& cavalls, const vector<pair<int, int>>& dirs, int i, int j, int& monedes_millor, int monedes_parcial, int monedes_restants)
{
    int n = M.size();
    int m = M[0].size();

    // Si ja he emplenat el tauler, actualitzar, si cal, el maxim de monedes
    if (i == n) {
        monedes_millor = max(monedes_millor, monedes_parcial);
        return;
    }

    // Poda: Si ja no puc millorar la solucio parcial aturo la crida
    if (monedes_parcial + monedes_restants < monedes_millor)
        return;

    // Escollir nous indexos
    int n_i, n_j;
    if (j == m - 1) {
        n_i = i + 1;
        n_j = 0;
    } else {
        n_i = i;
        n_j = j + 1;
    }

    // No escullo el cavall
    cavalls[i][j] = false;
    opt(M, cavalls, dirs, n_i, n_j, monedes_millor, monedes_parcial, monedes_restants - M[i][j]);

    // Escullo el cavall pero compte amb la restriccio
    bool amenaca = false;
    for (int k = 0; k < 8; ++k) {
        // comprovem si a les caselles on hi pot haver un cavall amenacador, hi ha un cavall
        int possible_i = i + dirs[k].first;
        int possible_j = j + dirs[k].second;

        // Si la casella existeix al tauler, i aquesta conte un cavall, es una amenaca
        if (possible_i >= 0 && possible_i < n && possible_j >= 0 && possible_j < m && cavalls[possible_i][possible_j]) {
            amenaca = true;
            break;
        }
    }

    // Si cap cavall amenaca la casella, llavors podem emplenar-la
    if (not amenaca) {
        cavalls[i][j] = true;
        opt(M, cavalls, dirs, n_i, n_j, monedes_millor, monedes_parcial + M[i][j], monedes_restants - M[i][j]);
        cavalls[i][j] = false;
    }
}

int millor_solucio(const vector<vector<int>>& M, int monedes_totals)
{
    int n = M.size();
    int m = M[0].size();

    int monedes_millor = 0; // max monedes possibles
    static vector<pair<int, int>> dirs = { { 1, 2 }, { 1, -2 }, { -1, 2 }, { -1, -2 }, { 2, 1 }, { 2, -1 }, { -2, 1 }, { -2, -1 } };
    vector<vector<bool>> cavalls(n, vector<bool>(m, false));
    opt(M, cavalls, dirs, 0, 0, monedes_millor, 0, monedes_totals);
    return monedes_millor;
}

int main()
{
    int n, m;
    while (cin >> n >> m) {
        int monedes_totals = 0;

        //Llegim matriu de monedes
        vector<vector<int>> M(n, vector<int>(m));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                cin >> M[i][j];
                monedes_totals += M[i][j];
            }

        cout << millor_solucio(M, monedes_totals) << endl;
    }
}