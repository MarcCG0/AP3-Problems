#include <iostream>
#include <vector>

using namespace std;

using lint = long long int;
using Matrix = vector<vector<lint>>;

int main()
{
    Matrix M0(31, vector<lint>(31, 0)); // M1[0][0]=M2[0][0]= 0
    Matrix M1(31, vector<lint>(31, 0));
    Matrix M2(31, vector<lint>(31, 0));
    M1[0][1] = M2[0][1] = 0;
    M0[0][0] = M0[0][1] = 1; // Word 0
    // set up base cases
    for (int z = 2; z < 31; ++z) {
        M0[0][z] = M0[0][z - 1];
        M1[0][z] = M2[0][z - 1];
        M2[0][z] = M1[0][z - 1];
    }

    // build recurrence
    for (int u = 1; u < 31; ++u) {
        for (int z = 0; z < 31; ++z) {
            if (z > 0) {
                M0[u][z] += M0[u][z - 1];
                M1[u][z] += M2[u][z - 1];
                M2[u][z] += M1[u][z - 1];
            }
            M0[u][z] += M1[u - 1][z];
            M1[u][z] += M0[u - 1][z];
            M2[u][z] += M2[u - 1][z];
        }
    }

    int us, zs;

    while (cin >> zs >> us) {
        cout << M0[us][zs] << endl;
    }
}