/* 

Write a program that, given a natural number m and n different words s1, … , sn, prints all the subsets of m elements that can be made up with the words.

Input consists of two natural numbers m and n, followed by s1, …, sn. Assume n > 0 and 0 ≤ m ≤ n.

Print all the subsets of m words that can be made up with s1, …, sn.

*/

#include <iostream>
#include <vector>

using namespace std; 

void write(const vector<string>& sol)
{
    cout << "{";
    bool first = true;
    for (string a : sol) {
        if (first) {
            cout << a;
            first = false;
        } else {
            cout << "," << a;
        }
    }
    cout << "}" << endl;
}

void subsets(vector<string>& w, vector<string>& sol,int k, int m){
    if(m == 0 ){
        // When subset is found, print it.
        write(sol); 
        return; 
    }
    /* 
        Branch & Bound: If there's not enough elements to fill the m 
        required elements we can stop. 
    */
    if(w.size()-k < m)return;
    /*
        Recursively choose whether the k-th element is in the current
        partial subset or not. 
    */  
    subsets(w, sol, k+1, m); 
    sol.push_back(w[k]); 
    subsets(w, sol, k+1, m-1); 
    sol.pop_back(); 
}

int main(){
        int n, m; 
        cin>>m>>n;
        vector<string> w(n); 
        for(string& a: w)cin>>a; 
        vector<string> sol; 
        subsets(w,sol, 0, m);  
}