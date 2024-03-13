#include <iostream>
using namespace std;

struct transaction{
    int identifikaciski_broj;
    int platena_suma;
    int provizija;
    int karticka;
};
void vnesi( transaction &obj){
 cin>>obj.identifikaciski_broj>>obj.platena_suma>>obj.provizija>>obj.karticka;
}
int main()
{
    int n;
    cin>>n;
    transaction niza[n];
    for(int i=0;i<n;i++)
    {
        vnesi(niza[i]);
    }
    int brojac=0;
    for(int i=0;i<n;i++)
    {
        if(niza[i].karticka==1)
        {
            cout<<niza[i].identifikaciski_broj<<" "<<niza[i].platena_suma+niza[i].provizija<<endl;
            brojac++;
        }
    }
    if(brojac==0)
    {
        cout<<"No credit card transaction"<<endl;
    }
    return 0;
}
