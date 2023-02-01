/*
L’entrada només conté nombres enters. Comença amb n, el nombre de cançons que es poden escollir. Segueix m, el nombre d’amics, i després m línies, cadascuna de les quals comença amb si, el nombre de cançons preferides de l’amic i-èsim, seguit de les corresponents si cançons. Cada cançó s’identifica amb un nombre entre 0 i n−1. L’entrada acaba amb k, el nombre màxim de cançons que es poden escollir. Podeu assumir que 1 ≤ n ≤ 25, que 1 ≤ m ≤ 250, i que 1 ≤ si, k ≤ n.

Escriviu totes les seleccions de com a molt k cançons tals que cada amic pot escoltar almenys una de les seves cançons preferides. A cada selecció cal escriure les cançons en ordre creixent d’identificador. Les seleccions es poden escriure en ordre arbitrari.
*/
#include <iostream>
#include <vector>
#include <map>

using namespace std; 
using Matrix = vector<vector<int>>;
const int UNHAPPY = -1; 
const int UNPLACED = -2; 
int n, m, k; 

void write(const vector<bool>& perm){
    bool first = true; 
    for(int i = 0; i<n; ++i){
        if(first && perm[i]){
            first = false; 
            cout << i;
        }
        else if(perm[i])cout << ","<< i; 
    }
    cout << endl; 
}

bool constraints(vector<int>& happy){
    for(int& a: happy)if(a == UNHAPPY)return false; 
    return true; 
}

bool possible(const vector<int>& n_fav){
    for(int a: n_fav)if(a == 0)return false; 
    return true; 
}

void opt(vector<int>& n_fav, Matrix& R, vector<int>& happy, vector<bool>& perm, int l, int r, bool nw){ // Note l stands for song & r for chosen songs
    if(not possible(n_fav))return; 
    if(k>=r && constraints(happy) && nw)write(perm); 
    if(r<k && l<n){

    for(int i = 0; i<m; ++i){
        // if song is in playlist and person is still unhappy, make them happy
        if(R[l][i] && happy[i] == UNHAPPY){
            happy[i] = l;
        }
    }

    perm[l] = true; 
    opt(n_fav, R, happy , perm, l+1, r+1, true); 
    perm[l] = false;

    // undo assigned happinesses
    for(int i = 0; i<m; ++i){
        if(happy[i] == l){
            happy[i] = UNHAPPY;
        }
    }
    // unplace songs that are being skipped
    for(int i = 0; i<m; ++i){
        if(R[l][i]){
            R[l][i] = UNPLACED; 
            --n_fav[i]; 
        }
    }
    opt(n_fav, R, happy, perm, l+1, r, false); 

    // undo unplacements
    for(int i = 0; i<m; ++i){
        if(R[l][i] == UNPLACED){
            R[l][i] = 1; 
            ++n_fav[i]; 
        }
    }
    }
}


int main(){
     // number songs
    while(cin>>n){
        cin>>m; // number friends
        // rows songs , cols friends 
        Matrix R(n, vector<int>(m, 0)); 
        // n_fav[i] contains # fav songs of i-th friend
        vector<int> n_fav(m, -1); 
        // for each friend
        for(int i = 0; i<m; ++i){
            int s_i; cin>>s_i; 
            n_fav[i] = s_i; 
            // for each song in friend's playlist
            for(int j = 0; j<s_i; ++j){
                int song; cin>> song; 
                R[song][i] = 1; 
            }
        }
        cin>>k; // max songs in perm
       vector<bool> perm(n); 
       vector<int> happy(m, UNHAPPY); 
       opt(n_fav,R, happy , perm, 0, 0, false); 
    }
}