/*
Write a program that computes how many strictly increasing subsequences with at least two letters are contained in a given word. For instance, the word arrow (we have written the second r in bold italics to distinguish it) contains the increasing subsequences arw, ar, arw, ar, aow, ao, aw, rw, rw and ow.

Input consists of several cases, each with a word made up of between 1 and 100 lowercase letters.

For every case, print the number of strictly increasing subsequences with at least two letters contained in the word. That number will always be less than 109.
*/
#include <iostream>
#include <vector>

using namespace std; 

int main(){
    string s; 
    while(cin>>s){
        int n = s.size(); 
        // Memo table to store the increasing subseq's starting in a certain position
        vector<int> dp(n, 0); 
        dp[n-1] =0; 
        int t = 0; 
        for(int i = n-2; i>= 0; --i){
            for(int j = i+1; j<n; ++j){
                if(s[i]< s[j])dp[i] += dp[j] +1;
            }
            t+=dp[i]; 
        }
        cout << t << endl; 
    }
}
