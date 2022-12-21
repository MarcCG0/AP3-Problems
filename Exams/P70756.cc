#include <iostream>
#include <vector>

using namespace std;

using Matrix = vector<vector<string>>;

void escriu(Matrix& M, int sb)
{
    for (int i = 0; i < sb; ++i) {
        cout << "subconjunt " << i + 1 << ": {";
        bool primer = true;
        for (string& a : M[i]) {
            if (primer) {
                primer = false;
                cout << a;
            } else
                cout << "," << a;
        }
        cout << "}" << endl;
    }
    cout << endl;
}

void generate_partitions(int sb, const vector<string>& words, Matrix& M, int k)
{
    if (k == words.size())
        escriu(M, sb);

    else
        for (uint i = 0; i < sb; ++i) {
            M[i].push_back(words[k]);
            generate_partitions(sb, words, M, k + 1);
            M[i].pop_back();
        }
}

int main()
{
    int n;
    cin >> n;
    vector<string> v(n);
    for (int i = 0; i < n; ++i)
        cin >> v[i];
    int sb;
    cin >> sb;
    Matrix M(sb);
    generate_partitions(sb, v, M, 0);
}
