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