/* Во програмскиот јазик C++ да се креира структура Laptop за опишување на 
спецификациите на даден преносен компјутер. Структурата треба да содржи: (5 поени)

Фирма која го произведува ( низа од 100 знаци)
Големина на монитор во инчи (реален број)
Дали е со touch или не (булова променлива)
Цена (цел број)
Да се креира структура ITStore, што содржи: (5 поени)

Име на продавницата (низа од 100 знаци)
Локација (низа од 100 знаци)
Низа од достапни лаптопи (низа од максимум 100 елементи од структурата Laptop)
Број на елементи во низата (цел број)
Да се креира функција print за печатење на информациите за сите лаптопи во една продавница во формат: (10 поени)

[Ime na prodavnicata] [Lokacija]
[Marka1] [dim_monitor1] [Cena1]
[Marka2] [dim_monitor2] [Cena2]
[Marka3] [dim_monitor3] [Cena3]
...
Да се креира функција najeftina_ponuda, што прима низа од променливи од типот ITStore и го печати името 
и локацијата на онаа продавница која нуди најевтин преносен компјутер и неговата цена.
Најефтин преносен компјутер е оној што има најниска цена и плус опција за touch. Ако има повеќе такви продавници,
се печати прво најдената.* (15 поени)*

Да се дополни функцијата main (10 поени).

Од тастатура се внесува бројот на продавници, па потоа за секоја продавница се внесуваат името и локацијата, 
а потоа бројот на компјутери, па за секој од компјутерите фирма која го произведува, големина на монитор,
дали има touch и цена. Потоа се печатат сите внесени продавници и најевтината понуда.
*/ 


#include <iostream>
#include <cstring>
using namespace std;
struct Laptop{
    char firmaKojaGoProizveduva[100];
    float goleminaNaMonitor;
    bool daliESoTouch;
    int cena;
};
struct ITStore{
    char ime[100];
    char lokacija[100];
    Laptop niza[100];
    int brElementi;
    void print(){
        cout<<ime<<" "<<lokacija<<endl;
        for(int i=0;i<brElementi;i++)
        {
            cout<<niza[i].firmaKojaGoProizveduva<<" "<<niza[i].goleminaNaMonitor<<" "<<niza[i].cena<<endl;
        }
    }
};
void najeftina_ponuda(ITStore *niza,int n){
    int index=0;
    int min=10000000;
    
for(int i=0;i<n;i++)
{
    for(int j=0;j<niza[i].brElementi;j++)
    {
        if(niza[i].niza[j].daliESoTouch==1)
        {
            if(niza[i].niza[j].cena<min)
            {
                min=niza[i].niza[j].cena;
                index=i;
            }
        }
    }
}
cout<<"Najeftina ponuda ima prodavnicata: \n"<<niza[index].ime<<" "<<niza[index].lokacija<<endl;
cout<<"Najniskata cena iznesuva: "<<min;
}
int main() {
    ITStore s[100];
    int n;
    cin>>n; //broj na IT prodavnici

    //vnesuvanje na prodavnicite edna po edna, zaedno so raspolozlivite laptopvi vo niv

 for(int i=0;i<n;i++)
 {
  cin>>s[i].ime>>s[i].lokacija>>s[i].brElementi;
  for(int j=0;j<s[i].brElementi;j++)
  {
      cin>>s[i].niza[j].firmaKojaGoProizveduva>>s[i].niza[j].goleminaNaMonitor>>s[i].niza[j].daliESoTouch>>s[i].niza[j].cena;
  }
 }

    //pecatenje na site prodavnici


 for(int i=0;i<n;i++)
 {
     s[i].print();
 }
    //povik na glavnata metoda
    najeftina_ponuda(s, n);

    return 0;
}
