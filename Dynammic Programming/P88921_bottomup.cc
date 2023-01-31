#include <iostream>
#include <vector>

using namespace std;
using Matrix = vector<vector<int>>;
const int UNDEF = -1;

int main()
{
    int n, m;
    while (cin >> n >> m) {

        if (n > 0 && m > 0) {
            Matrix M(n, vector<int>(m, 0));
            // prepare maze according to input
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < m; ++j) {
                    char c;
                    cin >> c;
                    if (c == 'X')
                        M[i][j] = UNDEF;
                }

            // compute recurrence

            M[0][0] = 1;

            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    if (M[i][j] == UNDEF)
                        continue;

                    if (i > 0 && M[i - 1][j] != UNDEF) {
                        if (M[i][j] != UNDEF)
                            M[i][j] += M[i - 1][j];
                    }

                    if (j > 0 && M[i][j - 1] != UNDEF) {
                        M[i][j] += M[i][j - 1];
                    }

                    if (M[i][j] >= 1e6)
                        M[i][j] = 1e6;
                }
            }
            if (m > 0 && n > 0) {

                if (M[n - 1][m - 1] >= 1e6)
                    cout << "!!!" << endl;
                else
                    cout << M[n - 1][m - 1] << endl;
            }
        }
    }
}