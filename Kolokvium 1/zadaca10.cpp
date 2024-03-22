/*Да се креира структура Igrac во која се чуваат податоци за еден играч на компјутерската игра. 
За играчот се чуваат информации за корисничкото име на играчот (низа од 15 знаци), 
број на ниво до кој играчот е стигнат (цел број) и број на освоени поени (цел број) (10 поени).

Потоа да се креирa структура KompjuterskaIgra во која се чуваат податоци за името на играта (низа од 20 знаци), 
низа од играчи кои ја играат играта (најмногу 30) и бројот на играчи. (10 поени)

Треба да се направи функција со потпис (15 поени)

void najdobarIgrac(KompjuterskaIgra *lista, int n)
Оваа функција треба да го испечати името на најдобриот играч на онаа игра која има најголема популарност
(ја играат наjголем број на играчи). Најдобар играч е играчот кој има најголем број на освоени поени.
Ако има повеќе играчи со ист максимален број на освоени поени, најдобар е играчот кој има достигнато најголемо ниво.

Печатењето е во форматот: "Najdobar igrac e igracot so korisnicko ime XXXXX koj ja igra igrata YYYYYY". 
(XXXXXX е корисничкото име на најдобриот играч,а YYYYY е името на играта која ја играат најголем број на играчи)

(Забелешка: секогаш ќе има точно еден најдобар играч)

Функционалност на задачата и дополнување на main функцијата (10 поени)

Забелешка: Задачата да се реши во програмскиот јазик C+ 
*/
#include <iostream>
#include <cstring>
using namespace std;

struct Igrac{
    char ime[15];
    int brNaNivo;
    int brNaPoeni;
};
struct KompjuterskaIgra{
    char ime[20];
    Igrac niza[30];
    int brNaIgraci;
};
void najdobarIgrac(KompjuterskaIgra *lista, int n){
    Igrac najdobar=lista[0].niza[0];
    int index=0;
    bool flag=1;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<lista[i].brNaIgraci;j++)
        {
            if(lista[i].niza[j].brNaPoeni>najdobar.brNaPoeni)
            {
                najdobar=lista[i].niza[j];
             index=i;
            }
            else
                if(lista[i].niza[j].brNaPoeni==najdobar.brNaPoeni){
                  flag=0;
                    for(int i=0;i<n;i++)
                    {
                        for(int j=0;j<lista[i].brNaIgraci;j++)
                        {
                            if(lista[i].niza[j].brNaNivo>najdobar.brNaNivo)
                            {
                                najdobar=lista[i].niza[j];
                            }
                        }
                    }
                }
        }
    }
    if(flag==0)
    cout<<"Najdobar igrac e igracot so korisnicko ime "<<najdobar.ime<<" koj ja igra igrata "<<lista[index].ime;
 else
        cout<<"Najdobar igrac e igracot so korisnicko ime "<<najdobar.ime<<" koj ja igra igrata "<<lista[index].ime;
}
int main() {

    int n;
    cin>>n;

 KompjuterskaIgra niza[n];

 for(int i=0;i<n;i++)
 {
cin>>niza[i].ime>>niza[i].brNaIgraci;
for(int j=0;j<niza[i].brNaIgraci;j++)
{
    cin>>niza[i].niza[j].ime>>niza[i].niza[j].brNaNivo>>niza[i].niza[j].brNaPoeni;
}
 }
    najdobarIgrac(niza,n);
 return 0;
}
