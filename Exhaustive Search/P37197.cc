#include <iostream>
#include <map>
#include <vector>

using namespace std;
void escriu(const vector<int>& sol_parcial, map<int, char>& invers)
{
    for (int a : sol_parcial)
        cout << invers[a];
    cout << endl;
}

void genera(vector<vector<int>>& restriccions, vector<int>& sol_parcial, int k, map<int, char>& invers)
{
    if (k == restriccions.size())
        escriu(sol_parcial, invers);
    else {
        for (uint i = 0; i < restriccions.size(); ++i) {
            if ((k == 0) || (restriccions[i][i] == -1 && restriccions[i][sol_parcial[k - 1]] == -1)) {
                // El posem;
                restriccions[i][i] = 0;
                sol_parcial.push_back(i);
                genera(restriccions, sol_parcial, k + 1, invers);
                restriccions[i][i] = -1;
                sol_parcial.pop_back();
            }
        }
    }
}

int main()
{
    int n;
    cin >> n;

    /*
        Relacionarem les especies amb la seva posicio
        al vector d'enters i booleans.
    */ 
    map<char, int> relacio;

    // convenient per imprimir;
    map<int, char> invers;
    for (int i = 0; i < n; ++i) {
        char a;
        cin >> a;
        relacio[a] = i;
        invers[i] = a;
    }
    // Diagonal de la matriu actua com vector de booleans -1 no visitat, 0 visitat.
    vector<vector<int>> restriccions(n, vector<int>(n, -1)); 
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        char a, b;
        cin >> a >> b;

        // (i,j) tenen restriccio --> restriccions[i][j]=1, si no en te, -1.
        restriccions[relacio[a]][relacio[b]] = 1;
        restriccions[relacio[b]][relacio[a]] = 1;
    }
    vector<int> sol_parcial;
    genera(restriccions, sol_parcial, 0, invers);
}