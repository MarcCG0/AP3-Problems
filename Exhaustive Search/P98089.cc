/*
Given n people and the grade of dislike between them, choose how to make them sit at a long table, in such a way that the sum of the interpersonal dislikes of the neighbor persons is minimum, with one restriction: the leftmost person must be the first person given.

Input consists of several cases, each with n, followed by n different names, followed by an n × n matrix of natural numbers between 0 and 106, where the position (i, j) has the dislike between people i and j. The matrix is symmetric, with zeroes at the diagonal. You can assume 1 ≤ n ≤ 12.

For every case, print the minimum sum of dislikes, followed by the optimum placement of people at the table. The test cases are such that there is always a unique solution.
*/
#include <iostream>
#include <limits>
#include <vector>
using namespace std;
const int MAX = std::numeric_limits<int>::max();

void opt(const vector<string>& people, vector<vector<int>>& dislikes, vector<string>& partial, int k, int s, int u, vector<string>& s_v, int& s_min)
{

    if (s > s_min)
        return;
    if (k == people.size()) {
        if (s_min > s) {
            s_min = s;
            s_v = partial;
        }
        return;
    }
    for (int v = 0; v < int(people.size()); ++v) {
        if (dislikes[v][v] == 0) {
            dislikes[v][v] = 1;
            partial[k] = people[v];
            opt(people, dislikes, partial, k + 1, s + dislikes[u][v], v, s_v, s_min);
            dislikes[v][v] = 0;
        }
    }
}

void print(vector<string>& v)
{
    for (int i = 0; i < int(v.size()); ++i) {
        if (i == 0)
            cout << v[i];
        else
            cout << " " << v[i];
    }
    cout << endl;
}

int main()
{
    int n;
    while (cin >> n) {
        vector<string> people(n);
        for (string& a : people)
            cin >> a;
        vector<vector<int>> dislikes(n, vector<int>(n));
        for (vector<int>& a : dislikes)
            for (int& b : a)
                cin >> b;
        vector<string> partial(n);
        partial[0] = people[0];
        /*
            Consider the diagonal of the matrix of dislikes as a boolean
            vector to avoid repeating people.
        */
        dislikes[0][0] = 1;
        int s_min = MAX;
        vector<string> s_v;
        opt(people, dislikes, partial, 1, 0, 0, s_v, s_min);
        cout << s_min << endl;
        print(s_v);
    }
}