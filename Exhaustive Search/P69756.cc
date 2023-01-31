/*

Write a program that prints all the permutations of { 1, …, n } with k inversions, for a given n and k. An inversion is a pair of elements x and y such that x > y and such that x appears before y in the permutation.

Input consists of two natural numbers n and k, such that n ≥ 1 and 0 ≤ k ≤ n(n − 1)/2.

Print all the permutations of { 1, …, n } with k inversions.

*/

#include <iostream>
#include <vector>

using namespace std; 


void write(const vector<int>& v, int n){
    cout << "("; 
    for(int i = 0; i<n-1; ++i)cout << v[i]+1 << ","; 
    cout << v[n-1]+1 << ")" << endl; 
}

void opt(vector<int>& sol, vector<bool>& mkd, int inv, int pos,int n, int k){
    /*
        Branch & Bound: if there's no elements to generate enough inversions
        to accomplish the k required inversions, then stop recursion. 
    */
    if(inv + (n-pos)*(n-pos-1)/2 < k || inv > k)return; 
    if(pos == n && k == inv){
        write(sol, n); 
    }else{
    for(int i = 0; i<n; ++i){
        if(not mkd[i]){
            mkd[i] = true; 
            sol[pos] = i;
            /*
                If element is skipped, then we add an inversion
                for the next recursive call 
            */
            opt(sol, mkd, inv++, pos+1, n, k);
            mkd[i] = false; 
        }
    }    
    }
}

int main(){
    int n, k; 
    cin>>n>>k;
    vector<int> sol(n); 
    vector<bool> mkd(n, false); 
    opt(sol, mkd, 0, 0, n, k);
}