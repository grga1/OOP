#include <iostream>
using namespace std;

struct Student{
    char ime[50];
    int index;
    int brojNaKursevi;
    int nizaNaKodoviOdKursevite[50];
};

struct Course{
    char imeNaKursot[50];
    int kodNaKursot;
    int brojNaStudentiKojGoSlusat;
};

int get_most_popular_course(Course niza[],int n){
    Course max=niza[0];
    for(int i=0;i<n;i++)
    {
        if(niza[i].brojNaStudentiKojGoSlusat>max.brojNaStudentiKojGoSlusat)
        {
            max=niza[i];
        }
    }
    return max.kodNaKursot;
}

int main()
{
    int brojNaStudenti,brojNaKursevi;
    cin>>brojNaStudenti>>brojNaKursevi;
    Student nizas[brojNaStudenti];
    Course nizac[brojNaKursevi];
    for(int i=0;i<brojNaKursevi;i++)
    {
        cin>>nizac[i].imeNaKursot>>nizac[i].kodNaKursot;
    }
    for(int i=0;i<brojNaStudenti;i++)
    {
        cin>>nizas[i].ime>>nizas[i].index;
        cin>>nizas[i].brojNaKursevi;
        for(int j=0;j<nizas[i].brojNaKursevi;j++){
            cin>>nizas[i].nizaNaKodoviOdKursevite[j];
            if(nizas[i].nizaNaKodoviOdKursevite[j]==nizac[i].kodNaKursot)
            {
                nizac[i].brojNaStudentiKojGoSlusat++;
            }
        }
    }
    for(int i=0;i<brojNaKursevi;i++)
    {
        if(nizac[i].kodNaKursot==get_most_popular_course(nizac,brojNaKursevi))
            cout<<nizac[i].imeNaKursot;
    }


    return 0;
}
