/*
El Nadal s’acosta. Aquest any hi ha hagut un augment significatiu en el nombre i gravetat de les trapelleries dels nens de tot el món, i els Reis Mags s’han adonat que amb el carbó que tenen en reserva no n’hi haurà prou. Per aquest motiu han decidit obrir la seva mina i extreure’n tot el carbó que es pugui en els dies que queden. Per fer-ho, disposen d’una borsa de n miners i d’un pressupost de b euros. Per cada miner i, es coneix el cost ci de contractar-lo, i la seva productivitat pi en l’extracció de carbó (mesurada en kilograms/dia). El que es vol és maximitzar la productivitat diària de carbó, subjecta al pressupost existent. Hi ha a més una altra restricció per motius de seguretat: l’ascensor que duu de l’entrada de la mina fins a la galeria ha de poder portar tots els miners alhora en cas d’evacuació. L’ascensor té un límit de pes a, i el pes del miner i és mi.

L’entrada consisteix en diversos casos. Cada cas comença amb n, el nombre de miners, seguit de b, el pressupost, seguit de a, el límit de pes de l’ascensor. A continuació vénen n tripletes de nombres pi, ci, mi que representen la productivitat, el cost i el pes del treballador i.

Podeu assumir que tots els nombres són naturals, que els diners es mesuren en euros, les productivitats en kilograms/dia i els pesos en kilograms. També podeu assumir que 1 ≤ n ≤ 500, que 1 ≤ pi ≤ 100, que 1 ≤ ci ≤ b ≤ 50, i que 1 ≤ mi ≤ a ≤ 200.

Per cada cas, escriviu la màxima productivitat diària que es pot aconseguir amb un subconjunt dels n treballadors, amb un pressupost de b euros i un ascensor amb límit de pes a.
*/
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;
using triMatrix = vector<vector<vector<int>>>; 
const int UNDEF = -1; 

struct Miner{
int p,c,m;
};

int n,b,a; 
vector<Miner> t; 
triMatrix dp; 

int opt(int k, int pressupost, int pes){
    int& res = dp[pressupost][pes][k];
    if(res != UNDEF)return res; 
    if(k == 0)return res =0 ;
    int n_add = opt(k-1, pressupost, pes);
    if(pressupost < t[k].c || pes < t[k].m)return res = n_add;
    int add = t[k].p+opt(k-1, pressupost - t[k].c, pes - t[k].m);
    return max(n_add, add); 
}

int main(){
    while(cin>>n>>b>>a){
        t = vector<Miner>(n+1); 
        dp = triMatrix(b+1,vector<vector<int>>(a+1, vector<int>(n+1,UNDEF)));
        for(int i = 1; i<=n; ++i){
            cin>>t[i].p >> t[i].c >> t[i].m; 
        }
       cout <<  opt(n, b, a) << endl;
    }
}