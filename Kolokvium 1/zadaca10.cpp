
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
