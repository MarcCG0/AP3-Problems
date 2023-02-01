/*
Write a program that, given n different words s1, …, sn and a number p, prints all the ways to share the words between p subsets.

Input consists of a natural number n > 0, followed by s1, …, sn, followed by a natural number p > 0.

Print all the ways to share the words between p subsets. The elements of each set must appear in the same order than in the input. Print an empty line after each partition.
*/
#include <iostream>
#include <vector>

using namespace std;

using Matrix = vector<vector<string>>;

void w(Matrix& M, int sb)
{
    for (int i = 0; i < sb; ++i) {
        cout << "subconjunt " << i + 1 << ": {";
        bool f = true;
        for (string& a : M[i]) {
            if (f) {
                f = false;
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
        w(M, sb);

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
