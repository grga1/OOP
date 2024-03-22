/*
Во програмскиот јазик С++ да се креира структура Vozenje за опишување на адреналински возења во забавен парк.
Структурата треба да содржи: (5 поени)

Име на возењето ( низа од 100 знаци)
Времетраење во минути (цел број)
Цена (децимален број)
Дали има студентски попуст (1-да, 0-не)
Да се креира структура ZabavenPark, што содржи: (10 поени)

Име на забавниот парк (низа од 100 знаци)
Локација (низа од 100 знаци)
Низа од адреналински возења во паркот (низа од максимум 100 елементи од структурата Vozenje)
Број на елементи во низата (цел број)
Да се креира функција print за печатење на информациите за сите возења во забавниот парк во формат: (10 поени)

[Ime na parkot] [Lokacija]
[Ime1] [Vremetraenje1] [Cena1]
[Ime2] [Vremetraenje2] [Cena2]
[Ime3] [Vremetraenje3] [Cena3]
...
Да се креира функција najdobar_park, што прима низа од променливи од типот ZabavenPark и
го печати името и локацијата на паркот кој е најефтин за посета од страна на студенти. 
Најефтин парк е оној што содржи најголем број возења со студентски попуст.
Ако повеќе паркови ги делат овие карактеристики,
да се испечати паркот со најголемото времетраење од сите возења.* (20 поени)*

Да се дополни функцијата main (5 поени). 
*/

#include <iostream>
#include <cstring>
#include <iomanip>
using  namespace  std;

struct Vozenje{
    char imeNaVozenje[100];
    int vremetraenje;
    float cena;
    bool popust;
};
struct ZabavenPark{
    char ime[100];
    char lokacija[100];
    Vozenje niza[100];
    int brNaElementi;
    void print(){
        cout<<ime<<" "<<lokacija<<endl;
        for(int i=0;i<brNaElementi;i++)
        {
            cout<<niza[i].imeNaVozenje<<" "<<niza[i].vremetraenje<<" "<<fixed<<setprecision(2)<<niza[i].cena<<" "<<endl;
        }
    }
};
void najdobar_park(ZabavenPark *niza,int n){
    int max=-100;
    int brojac=0;
    int index=0;
    bool flag=1;
    int index2=0;
    int s=0;
    int max2=-100;
    for(int i=0;i<n;i++) {
        for (int j = 0; j < niza[i].brNaElementi; j++) {
            if (niza[i].niza[j].popust == 1) {
                brojac++;
            }
        }
        if(brojac>max)
        {
            index=i;
            max=brojac;
            brojac=0;
        }else if(brojac==max)
        {

            flag=0;
            s=0;
            for(int i=0;i<n;i++) {
                for (int j = 0; j < niza[i].brNaElementi; j++) {
                    {

                        s += niza[i].niza[j].vremetraenje;
                    }
                }
                if(s>max2)
                {
                    max2=s;
                    index2=i;
                s=0;
                }

            }
        }
    }
    if(flag==1)
    cout<<"Najdobar park: "<<niza[index].ime<<" "<<niza[index].lokacija;
    else
        cout<<"Najdobar park: "<<niza[index2].ime<<" "<<niza[index2].lokacija;
};
int main(){
int n;
cin>>n;
  ZabavenPark niza[n];
  for(int i=0;i<n;i++)
  {
    cin>>niza[i].ime>>niza[i].lokacija>>niza[i].brNaElementi;
    for(int j=0;j<niza[i].brNaElementi;j++)
    {
        cin>>niza[i].niza[j].imeNaVozenje;
        cin>>niza[i].niza[j].vremetraenje>>niza[i].niza[j].cena>>niza[i].niza[j].popust;
    }
  }
  for(int i=0;i<n;i++)
  {
      niza[i].print();
  }
    najdobar_park(niza,n);
    return 0;
}
