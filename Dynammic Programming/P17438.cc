/*
Consider the following variant of the two-player game of Nim, originated in China: There are six sets numbered from 1 to 6, each one with mi marbles. Initially, we have mi = i for every 1 ≤ i ≤ 6. In turns, every player must choose one of the non-empty sets and remove at least one of its marbles. The player that removes the last marble(s) wins the game.

For instance, let Anne and Bill be the players. This is a possible situation of the game after several turns (the first number denotes m1 and so on):

1    1    0    0    5    0 
If it is Anne’s turn, she may choose to remove the five marbles of the fifth set:

1    1    0    0    0    0 
Next Bill has no real option: he must remove one marble from any set (say the first one):

0    1    0    0    0    0 
Now Anne can remove the last marble, and therefore she wins the game. Note, if Anne had made any other movement in the first place, she would had lost the game had Bill played perfectly.

Write a program such that, given the names of the players (first the player to play next) and the current number of marbles of every set, prints the name of the player that wins the game, assuming perfect play from both sides.

Input begins with the number of cases. Every case consists of the names (only letters) of the players, followed by m1, …, m6. You can assume 0 ≤ mi ≤ i and m1 + ⋯ + m6 ≥ 1.

For every case, print its number, followed by the name of the winner assuming perfect play.
*/
#include <iostream>
#include <map>
#include <vector>

using namespace std;
using GameRec = map<vector<int>, bool>;

bool guanya(GameRec& gr, vector<int>& game)
{
    if (gr.count(game))
        return gr[game];

    bool found = false;
    for (int i = 0; i < 6 and not found; ++i) {
        for (int j = 1; j <= game[i] and not found; ++j) {
            game[i] -= j;

            if (not guanya(gr, game))
                found = true;

            game[i] += j;
        }
    }
    gr[game] = found;
    return found;
}

int main()
{
    int n;
    cin >> n;

    GameRec gr;
    gr[{ 0, 0, 0, 0, 0, 0 }] = false;

    for (int i = 0; i < n; ++i) {
        string a, b;
        cin >> a >> b;
        vector<int> game(6);
        for (int j = 0; j < 6; ++j)
            cin >> game[j];
        cout << "Game #" << i + 1 << ": ";
        cout << (guanya(gr, game) ? a : b) << endl;
    }
}