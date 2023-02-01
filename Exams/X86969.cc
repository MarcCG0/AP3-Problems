/*
Teniu al vostre càrrec la gestió de la producció de farina en una indústria farinera. Cal produir d kilograms de farina, tasca per a la qual es disposa de n molins. En una hora, el molí i-èsim pot produir pi kg de farina, i consumeix ci kWh (kilowatts hora). A més, cada molí té una autonomia de ui hores, i no pot estar en funcionament més temps per raons de manteniment. Amb els preus actuals de l’energia, és primordial minimitzar el consum elèctric. Podeu dissenyar un pla de producció òptim?

Per exemple, suposem que per a produir 3500 kg de farina tenim dos molins tals que:

el primer en una hora produeix 50 kg de farina i consumeix 10 kWh, i pot funcionar fins a 20 hores.
el segon en una hora produeix 75 kg de farina i consumeix 10 kWh, i pot funcionar fins a 40 hores.
Com que el segon molí consumeix el mateix que el primer però produeix més farina, aleshores un pla òptim consisteix en fer servir el segon molí durant 40 hores i el primer durant 10 hores, fabricant així 40 · 75 + 10 · 50 = 3500 kg de farina amb un consum elèctric total de 40 · 10 + 10 · 10 = 500 kWh.

L’entrada consisteix en diversos casos. Cada cas comença amb n, el nombre de molins, seguit de n enters positius ui, seguit de n enters positius pi, seguit de n enters positius ci, els quals representen l’autonomia, la productivitat i el consum de cadascun dels molins, respectivament. El cas acaba amb un enter d, que representa la demanda de farina. Podeu assumir que 1 ≤ n ≤ 104, que 1 ≤ ui, pi, ci ≤ 100 per tot 0 ≤ i ≤ n−1, i que 0 ≤ d ≤ ∑i=0n−1 ui · pi (és a dir, segur que la demanda es pot satisfer).

Per cada cas, escriviu amb quatre dígits decimals el consum mínim d’electricitat per tal de poder satisfer la demanda de farina.
*/
#include <iostream>
#include <algorithm> 
#include <vector>

using namespace std; 

struct Mill{
int u,p,c; 
};

using Mills = vector<Mill>; 

// Ordenem en funció del següent ratio: kg's de farina produits per kWh. 
bool cmp(Mill& a, Mill& b){
    return double(a.p)/a.c >= double(b.p)/b.c; 
}

void opt(Mills& M, double& nG, double d){
    int i = 0; 
    // Mentre no aconseguim la demanda
    while(d>0){
            // Produccio/h del moli més efficient 
            int prod_t = M[i].p*M[i].u; 
            if(d>=prod_t){
                d-=prod_t; 
                // Actualitzem l'energia gastada
                nG += M[i].c*M[i].u; 
            }
            else{ // Si el temps necesitat és menor a la producció sencera d'un molí
                double time_needed = (d*M[i].u)/double(prod_t);
                nG += time_needed * double(M[i].c); 
                d = 0; 
            }
            ++i;
        }
    }




int main(){
    int n; 
    while(cin>>n){
        Mills M(n);
        for(Mill& m: M)cin>>m.u; 
        for(Mill& m: M)cin>>m.p; 
        for(Mill& m: M)cin>>m.c; 
        int d; cin>>d; 
        sort(M.begin(),M.end(), cmp); 
        double nG = 0;
        opt(M, nG, d);  
        cout.setf(ios::fixed);
        cout.precision(4); 
        cout << nG << endl;       
    }
}