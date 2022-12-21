#include <iostream>
#include <vector>
using namespace std;

void escriu(const vector<string>& solucio_parcial)
{
    cout << "{";
    bool primer = true;
    for (string a : solucio_parcial) {
        if (primer) {
            cout << a;
            primer = false;
        } else {
            cout << "," << a;
        }
    }
    cout << "}" << endl;
}

void genera(const vector<string>& paraules, vector<string>& solucio_parcial, int cont, int k, int m)
{
    if (k == m) {
        escriu(solucio_parcial);
    } else {
        for (int i = cont; paraules.size() - i >= m - k; ++i) {
            solucio_parcial[k] = paraules[i];
            genera(paraules, solucio_parcial, i + 1, k + 1, m);
        }
    }
}

int main()
{
    int m, n;
    cin >> m >> n;
    vector<string> paraules(n);
    for (int i = 0; i < n; ++i)
        cin >> paraules[i];
    vector<string> solucio_parcial(m);
    genera(paraules, solucio_parcial, 0, 0, m);
}
