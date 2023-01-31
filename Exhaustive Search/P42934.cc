/*
Given several directed graphs with n vertices, each one described with a matrix m of size n × n such that m[i][j] is the cost of going from vertex i to vertex j, calculate the minimum cost of the Hamiltonian cycles of every graph. A Hamiltonian cycle is a path that visits each vertex exactly once, and that ends at the starting vertex.

Input consists of the description of several graphs. Each one begins with a natural number n ≥ 2, followed by the matrix n × n of costs (n lines, each with n natural numbers, with zeroes at the diagonal).

Print the minimum cost of the Hamiltonian cycles of every graph.
*/

#include <climits>
#include <iostream>
#include <vector>

using namespace std;

using Graph = vector<vector<int>>;

const int MAX = INT_MAX;

Graph read_graph(int n)
{
    Graph g(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> g[i][j];
        }
    }
    return g;
}

void opt(const Graph& g, vector<bool>& vis, int u, int p_cost, int& cost, int k)
{
    if (p_cost > cost)
        return;
    if (g.size() == k) {
        p_cost += g[u][0];
        if (cost > p_cost)
            cost = p_cost;
        return;
    } else {
        for (int v = 0; v < int(g.size()); ++v) {
            if (v != u && not vis[v] and g[u][v] + p_cost < cost) {
                vis[v] = true;
                opt(g, vis, v, p_cost + g[u][v], cost, k + 1);
                vis[v] = false;
            }
        }
    }
}

void minimal_cost(const Graph& g, int n)
{
    vector<bool> vis(n);
    int cost = MAX;
    vis[0] = true;
    opt(g, vis, 0, 0, cost, 1);
    cout << cost << endl;
}

int main()
{
    int n;
    while (cin >> n) {
        Graph g = read_graph(n);
        minimal_cost(g, n);
    }
}