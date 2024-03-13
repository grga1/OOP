#include <iostream>
using namespace std;

struct FootballPlayer{
    char ime[50];
    int broj_na_dres;
    int broj_na_golovi;
};

struct FootballTeam{
    char ime_na_tim[50];
    FootballPlayer niza[11];
};

void print(FootballTeam obj){
    cout<<obj.ime_na_tim<<endl;
}
void bestTeam(FootballTeam *teams,int n){
 FootballTeam max=teams[0];
 int s=0;
 int maxx=-100;
 for(int i=0;i<n;i++)
 {
     for(int j=0;j<11;j++)
     {
         s+=teams[i].niza[j].broj_na_golovi;
     }
     if(s>maxx)
     {
         s=0;
         maxx=s;
         max=teams[i];
     }
 }
    print(max);
}

int main()
{
    int n;
    cin>>n;
    FootballTeam niza[n];

    for(int i=0;i<n;i++)
    {
     cin>>niza[i].ime_na_tim;
        for(int j=0;j<11;j++) {
            cin>>niza[i].niza[j].ime>>niza[i].niza[j].broj_na_dres>>niza[i].niza[j].broj_na_golovi;
        }
    }

    bestTeam(niza,n);

    return 0;
}
