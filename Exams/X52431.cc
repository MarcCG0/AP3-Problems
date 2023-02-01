/*
L’entrada comença amb n, el nombre d’estats de l’autòmat finit, que es representen amb nombres naturals entre 0 i n−1. A continuació es descriu la funció de transició δ de l’autòmat: en primer lloc vénen n nombres, corresponents a les imatges dels estats amb el símbol 0: δ(0, 0), δ(1, 0), …, δ(n−1, 0). Després vénen un altres n nombres, corresponents a les imatges dels estats amb el símbol 1: δ(0, 1), δ(1, 1), …, δ(n−1, 1). A continuació vénen n zeros i uns, que indiquen per cada estat 0, …, n−1 si és d’acceptació (1) o no (0). L’estat inicial sempre és l’estat 0. Finalment l’entrada acaba amb el nombre m, la màxima longitud que es vol considerar.

Per cada valor l entre 0 i m, escriviu el nombre de paraules acceptades per l’autòmat de longitud l. Es garanteix que tots els nombres són més petits que 109.
*/
#include <iostream>
#include <vector>

using namespace std; 
using Matrix = vector<vector<int>>; 

int main(){
    int n; 
    while(cin>>n){
        // [0][1] -> Estant a j, menjant i vaig a [i][j]
        Matrix tr(2, vector<int>(n)); 
        for(int i = 0; i<2; ++i){
            for(int j = 0; j<n; ++j){
                cin>>tr[i][j]; 
            }
        }
        vector<int> acceptations(n); 
        for(int& a: acceptations)cin>>a; 

        int m; cin>>m; 

        // Matriu que guarda a les files la long de les paraules i a les columnes l'estat on es troben les paraules.
        Matrix dp(m+1, vector<int>(n, 0));  

        dp[0][0] = 1; 
        // omplim la matriu de dp
        for(int i = 1; i<=m; ++i){
            for(int j = 0; j<n; ++j){
                dp[i][tr[0][j]] += dp[i-1][j];
                dp[i][tr[1][j]] += dp[i-1][j];
            }
        }
        // Per a cada longitud de paraula, per totes les paraules sumem les que estan a un estat d'acceptacio
        for(int i = 0; i<=m; ++i){
            int res = 0; 
            for(int j = 0; j<n; ++j){
                if(acceptations[j]){
                    res+=dp[i][j]; 
                }
            }
            cout << res << endl; 
        }
    }
}