#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool cmp(int a, int b)
{
    return a > b;
}

int main()
{
    int n;
    while (cin >> n) {
        vector<int> v(3 * n);
        int total = 0;
        for (int i = 0; i < 3 * n; ++i) {
            cin >> v[i];
            total += v[i];
        }
        sort(v.begin(), v.end(), cmp);

        // un cop tenim ordenat el vector, comptem de tres en tres el que no paguem;
        for (int j = 2; j < 3 * n; j += 3)
            total -= v[j];

        cout << total << endl;
    }
}
