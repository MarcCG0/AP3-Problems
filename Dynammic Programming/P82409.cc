#include <iostream>
#include <vector>
using namespace std;

const int NIL = -1;
const int MAX = 67;
vector<long int> v;

long int paraules(int n)
{
    if (n == 0)
        return 1;

    long int& k = v[n];

    if (k != NIL)
        return k;

    long int sum = 0;
    for (int i = 2; i <= n; ++i) {
        sum += paraules(i - 2) * paraules(n - i);
    }
    v[n] = sum;

    return sum;
}

int main()
{
    int n;
    v = vector<long int>(MAX + 1, NIL);

    while (cin >> n) {
        cout << paraules(n) << endl;
    }
}
