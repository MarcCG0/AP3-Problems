/*
In this problem we consider the expressions defined as follows:

Every variable is a correct expresion;
if x is a correct expression, so is (x);
if x1 and x2 are correct expressions, so are (x1) − (x2);
nothing else is a correct expression.
For instance, if the set of variables is A, B, C, these are some correct expressions:

A      (A)      ((C))      (A)−(B)      ((A)−(B))−(A)
Write a program that, given two numbers n and m, prints the number of correct expressions of length exactly n that can be made up with m variables.

For instance, for n =7 and m=2 the result should be 6, corresponding to

(((A)))      (((B)))      (A)−(A)      (A)−(B)      (B)−(A)      (B)−(B)

Input consists of several cases, each with two natural numbers n and m between 1 and 25.

For every case, print the number of correct expressions of length exactly n that can be made up with m variables. This number will always be smaller than 109.
*/
#include <iostream>
#include <vector>

using namespace std;

vector<int> nth_number_of_expressions(int n, int m)
{
    vector<int> v(n + 1, 0);

    v[1] = m;

    for (int i = 3; i <= n; ++i) {

        for (int j = 1; j <= i - 6; ++j) {
            v[i] += v[j] * v[i - 5 - j]; // (dim n-5) (expr)-(expr)
        }

        v[i] += v[i - 2]; // parenthesized dim(n-2)
    }
    return v;
}

int main()
{
    int n, m;
    while (cin >> n >> m) {
        if (n % 2 == 0)
            cout << 0 << endl;
        else {

            // Algorithm: Observe that any expression can be built from one of
            // level n-2 by putting parenthesis on it. Or from from other levels by
            // doing (expr1)-(expr2). The difficult thing is to observe that
            // dim(expr1)+dim(expr2) = n-5. Therefore some combinations can be:
            // dim(expr1) = 1 & dim(expr2) = n-6 or dim(expr1) = 2 & dim(expr2) = n-7 (these are only some instances).

            vector<int> v = nth_number_of_expressions(n, m);
            cout << v[n] << endl;
        }
    }
}