#include <climits>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

/* Algorisme


  1. Provem de posar el nombre k-èssim al conjunt A, o al conjunt B
  2. Si el valor absolut de la diferència que portem menys i més el que ens queda per assignar
  és més gran que la resposta òptima que ja hem trobat, vol dir que aquella solucio no serà optima
  3. Si s'han assignat tots els nombres als conjunts, comprovem si es millora la solució parcial


*/

void opt(vector<int>& v, int s_a, int s_b, int k, int& m_abs, int left)
{
    if (abs(s_a - s_b) - left > m_abs)
        return;
    if (k == v.size()) {
        if (abs(s_a - s_b) < m_abs)
            m_abs = abs(s_a - s_b);
        return;
    }
    opt(v, s_a + v[k], s_b, k + 1, m_abs, left - v[k]);
    opt(v, s_a, s_b + v[k], k + 1, m_abs, left - v[k]);
}

int main()
{
    int n;
    while (cin >> n) {
        vector<int> v(n);
        int total = 0;
        for (int& a : v) {
            cin >> a;
            total += a;
        }
        int m_abs = INT_MAX;
        opt(v, 0, 0, 0, m_abs, total);
        cout << m_abs << endl;
    }
}