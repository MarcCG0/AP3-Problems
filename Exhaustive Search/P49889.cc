/*
Write a program that reads n consonants and n vowels, and prints all the words that can be made up by using each letter exactly once. The words must begin with a consonant, and alternate consonants and vowels. In this exercise, we will assume that ‘y’ is a vowel.

Input consists of a natural number n between 1 and 6, followed by n different consonants and n different vowels. Both consonants and vowels are given in alphabetical order.

Print the words that can be made up with the 2n given letters, starting with a consonant and always alternating consonants and vowels. Print the words in alphabetical order, one per line.
*/
#include <iostream>
#include <vector>
using namespace std;

void write(const vector<char>& sol)
{
    for (char a : sol)
        cout << a;
    cout << endl;
}

void exh(vector<char>& sol, const vector<char>& c, const vector<char>& vowels,
    vector<bool>& u_vowel, vector<bool>& u_consonant, int k, int n)
{
    if (2 * n == k) {
        write(sol);
    
    /*
        Choose whether it`s time to place a vowel or consonant and recurse
    */
    } else if (k % 2 == 0) {
        for (int i = 0; i < n; ++i) {
            if (not u_consonant[i]) {
                sol[k] = c[i];
                u_consonant[i] = true;
                exh(sol, c, vowels, u_vowel, u_consonant, k + 1, n);
                u_consonant[i] = false;
            }
        }
    } else {
        for (int j = 0; j < n; ++j) {
            if (not u_vowel[j]) {
                sol[k] = vowels[j];
                u_vowel[j] = true;
                exh(sol, c, vowels, u_vowel, u_consonant, k + 1, n);
                u_vowel[j] = false;
            }
        }
    }
}

int main()
{
    int n;
    cin >> n;
    vector<char> c(n);
    for (int i = 0; i < n; ++i)
        cin >> c[i];
    vector<char> vowels(n);
    for (int i = 0; i < n; ++i)
        cin >> vowels[i];

    vector<bool> u_vowel(n, false);
    vector<bool> u_consonant(n, false);
    vector<char> sol(2 * n);
    exh(sol, c, vowels, u_vowel, u_consonant, 0, n);
}