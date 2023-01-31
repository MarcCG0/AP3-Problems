/*
Write a program that prints the number of sequences made up of exactly z zeros and u ones that do not contain two consecutive zeros nor three consecutive ones.

For instance, there are 8 sequences for z = 3 and u = 4:

0101011    0101101    0110101    0110110    1010101    1010110    1011010    1101010

Input consists of several pairs of natural numbers z and u, each between 0 and 90.

For every pair of z and u, print the required number.
*/
#include <iostream>
#include <vector>

using namespace std;

using lint = long long int;
using Matrix = vector<vector<lint>>;

int main()
{
    Matrix w10(91, vector<lint>(91, 0));
    Matrix w11(91, vector<lint>(91, 0));
    Matrix w01(91, vector<lint>(91, 0));
    Matrix M(91, vector<lint>(91, 0));
    w10[1][1] = w11[2][0] = w01[1][1] = 1;
    w10[1][2] = 1;

    // base cases that do not include words of length 2 or more (w10, w11, w01)
    M[0][0] = M[0][1] = M[1][0] = 1;

    // fill 2 first rows with correspoding values
    for (int u = 0; u < 2; ++u) {
        for (int z = 0; z < 91; ++z) {
            M[u][z] += w10[u][z] + w01[u][z] + w11[u][z];
        }
    }

    // fill the remaining empty grid
    for (int u = 2; u < 91; ++u) {
        for (int z = 0; z < 91; ++z) {
            if (z > 0) {
                w10[u][z] += w01[u][z - 1] + w11[u][z - 1];
            }
            w01[u][z] += w10[u - 1][z];
            w11[u][z] += w01[u - 1][z];
            M[u][z] = w10[u][z] + w01[u][z] + w11[u][z];
        }
    }
    int z, u;
    while (cin >> z >> u) {
        cout << M[u][z] << endl;
    }
}