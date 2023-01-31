/*
The firefighters of a distant country want to protect the grannies inside n schools. All the schools are in a row on a street, numbered in order from 1 to n. At each school j there are ij grannies. The firefighters can form g groups, and each group can only go to a single school. If a group goes to school j, it protects all the grannies there. In addition, it also indirectly protects half the grannies in school j−1, assuming that it exists and that it is not already fully protected by another group; and similarly with school j+1.

What is the maximum number of grannies that can be protected?

Input consists of several cases, each one with g and n, followed by the ij’s. You can assume 1 ≤ g ≤ n ≤ 20, and that all the ij’s are even natural numbers between 2 and 105.

For every case, print how many grannies can be protected.
*/

#include <iostream>
#include <vector>

using namespace std; 

void opt(vector<int>& gr, vector<bool>& prot,int k, int& mx, int mx_p, int g, bool prev_prot, int total){
    if(g == 0 or k == gr.size()){
        mx = max(mx, mx_p);
        return; 
    }
    if(gr.size()- k < g)return; 
    if(mx_p + total <= mx)return ; 
    /*
        Decide if we put a group in the k-th school.
    */
    opt(gr, prot, k+1, mx, mx_p, g, false, total); 
    int new_prot = 0; 
    /*
        In case that we place a group, compute the protection
        that this group adds to the situation and store it in 
        new_prot. 
    */
    if(k == 0)new_prot+= gr[k]; 
    if(k>0 && not prev_prot)new_prot += gr[k]+gr[k-1]/2; 
    if(k > 0 && prev_prot)new_prot+= gr[k]/2; 
    if(k< gr.size()-1)new_prot+= gr[k+1]/2; 
    opt(gr, prot, k+1, mx, mx_p+new_prot, g-1, true, total-new_prot); 
}

int main(){
    int g, n; 
    while(cin>>g>>n){
        vector<int> gr(n); 
        int t = 0; 
        for(int& grs: gr){
            cin>>grs;
            t += grs; 
            } 
        int mx = 0; 
        // Indicates fully protection.
        vector<bool> prot(n, false); 
        opt(gr, prot, 0, mx, 0, g, false, t);
        cout << mx << endl;  
    }
}