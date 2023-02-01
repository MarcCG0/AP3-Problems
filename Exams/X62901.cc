/*
L’entrada comença amb n, el nombre de partits polítics. El segueixen parells ei, pi, un per cada 0 ≤ i < n, on ei és un natural que indica el nombre d’escons al parlament aconseguits pel partit i-èsim en les darreres eleccions, i pi és un natural entre 0 i 1000 que mesura el perfil polític del partit (sent 0 extrema esquerra, i 1000 extrema dreta). L’entrada conclou amb un natural m, que és la diferència màxima de perfil polític permesa entre els partits que no estan en contra de la investidura. Podeu assumir també que 2 ≤ n ≤ 20, que 1 ≤ ei ≤ 300, i que 0 ≤ m ≤ 1000.

Escriviu cadascuna de les diferents possibilitats per investir president del govern (en segona ronda). Per a que això sigui possible, cal que hi hagi majoria simple: això és, que la suma dels vots a favor sigui més gran estrictament que la suma dels vots en contra; les abstencions no compten. Assumiu que els parlamentaris poden votar a favor, en contra, o abtenir-se; i que segueixen la disciplina de partit, això és, tots els membres d’un partit voten el mateix. També cal que la diferència de perfil polític entre dos partits qualssevol que estiguin a favor de la investidura o que s’abstinguin sigui no superior a m.

Seguiu el format donat en els jocs de prova. Per cada 0 ≤ i < n, el partit i-èsim s’identifica amb i. A més d’escriure els partits a favor, els que s’abstenen i els que hi estan en contra, indiqueu també, dels partits a favor, els que tinguin més escons (ja que el candidat a president del govern serà d’un d’aquests partits).

No importa l’ordre de les solucions, però a cada solució, els partits que voten a favor han d’estar ordenats de forma creixent; i igualment per als que s’abstenen i per als que voten en contra. També els partits a favor amb el màxim d’escons s’han d’escriure ordenats de la mateixa manera.

Escriviu una línia en blanc després de cada solució.
*/
#include <iostream>
#include <vector>
#include <climits>

using namespace std; 

struct Party{
    int e, p; 
}; 

struct Solution{
vector<int> pr, f, a, c; // presidents, favour, abstention, against
vector<int> fav; 
};

int n, m; 


void write_investiture(const vector<Party>& P,const Solution& S, int presi){
cout << "President de";
  for(int i = 0; i<n; ++i){
    if(presi == -1)break; 
    if(P[i].e == presi && S.fav[i]) cout << " " << i; 
  }
  cout << endl; 
  cout << "A favor";
  for(int partit: S.f)cout << " " << partit; 
  cout << endl;
  cout << "Abstencio";
  for (int partit : S.a) cout << " " << partit;
  cout << endl;
  cout << "En contra";
  for (int partit : S.c) cout << " " << partit;
  cout << endl << endl;
}

void exh_investiture(vector<Party>& P, int k, int mn,int mx, int f_e, int c_e, int left, Solution& S, int presi){
    if(k == n){
        if(f_e>c_e) write_investiture(P, S, presi);
        return ; 
         }
    // we prune useless branches 
    if(left + f_e <= c_e)return ; 


    // in any case, put the party against
    S.c.push_back(k); 
    exh_investiture(P, k+1, mn, mx, f_e, c_e+P[k].e, left - P[k].e, S, presi); 
    S.c.pop_back(); 

    // put party not against the investiture
    // in order to do so max ideological differences have to be accomplished
    if(mn == INT_MAX || (abs(P[k].p-mx)<=m && abs(P[k].p -mn) <= m)){
        // put current party in favour
        // update president
        S.fav[k] = 1; 
        S.f.push_back(k); 
        exh_investiture(P,k+1, min(mn, P[k].p), max(mx, P[k].p),  f_e+P[k].e,  c_e, left - P[k].e, S, max(presi, P[k].e));

        // undo recursion
        S.f.pop_back(); 
        S.fav[k] = 0;

        // put currenty party in abstention
        S.a.push_back(k); 
        exh_investiture(P, k+1, min(mn, P[k].p), max(mx, P[k].p), f_e, c_e, left - P[k].e, S, presi);
        S.a.pop_back(); 
    }

}



int main(){
    cin>>n; 
    vector<Party> P(n); 
    int total_e = 0; 
    for(Party& pt: P){
        cin>>pt.e>>pt.p; 
        total_e +=pt.e; 
        }
    // max ideological differences between two parties not against 
    // the decision (that is, in favour or abstention)
    cin>>m; 
    Solution S; 
    S.fav = vector<int>(n, 0); 
    exh_investiture(P, 0, INT_MAX, INT_MIN, 0, 0, total_e, S, -1); 
}
