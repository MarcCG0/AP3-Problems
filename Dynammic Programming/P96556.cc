/*
Write a program that computes how many strictly increasing subsequences with at least two letters are contained in a given word. For instance, the word arrow (we have written the second r in bold italics to distinguish it) contains the increasing subsequences arw, ar, arw, ar, aow, ao, aw, rw, rw and ow.

Input consists of several cases, each with a word made up of between 1 and 100 lowercase letters.

For every case, print the number of strictly increasing subsequences with at least two letters contained in the word. That number will always be less than 109.
*/

#include <iostream>
#include <vector>

using namespace std; 

vector<int> V; 
const int UNDEF = -1; 
int n; 

int td(int k, const string& s){
    if(k == n-1)return V[k] = 0;
    if(V[k] != UNDEF)return V[k]; 

    int r = 0; 
    // Return all the words that start with the i-th letter passed in main
    for(int j = k+1; j<n; ++j){
        if(s[k] < s[j])r+= td(j,s)+1 ; 
    }
    return V[k] = r; 

}

int main(){
    string s; 
    while(cin>>s){
        n = s.size(); 
        V = vector<int>(n, UNDEF); 
        int t = 0; 
        for(int i = 0; i<n; ++i){
            t+= td(i, s); 
        }
        cout << t << endl; 
        }
}
