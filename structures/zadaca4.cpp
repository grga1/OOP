#include <iostream>
#include <iomanip>
using namespace std;

struct item{
    char ime[50];
    int cena;
};

struct shoppingcart{
    int id;
    int brojnaproizvodi;
    item niza[50];
};

void printAveragePriceOfLowestItems(shoppingcart niza[],int n){
  float average=0;
  int low;
    for(int i=0;i<n;i++)
  {
        low=niza[i].niza[0].cena;
        for(int j=0;j<niza[i].brojnaproizvodi;j++)
        {
            if(niza[i].niza[j].cena<low){
                low=niza[i].niza[j].cena;
            }
        }
        cout<<low<<endl;
       average+=low;
  }
    cout<<"Average:"<<setprecision(2)<<fixed<<average/2<<endl;
}

void printHighestPriceItem(shoppingcart niza[],int n){
    shoppingcart max=niza[0];
    int indexi=0;
    int indexj=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<niza[i].brojnaproizvodi;j++)
        {
            if(niza[i].niza[j].cena>max.niza[j].cena)
            {
                max=niza[i];
                indexi=i;
                indexj=j;
            }
        }
    }
    cout<<"Shopping cart id:"<<max.id<<endl;
    cout<<"Product:"<<max.niza[indexj].ime<<endl;
}
int main()
{
    int n;
    cin>>n;
    shoppingcart niza[n];
    for(int i=0;i<n;i++)
    {
        cin>>niza[i].brojnaproizvodi;
        cin >> niza[i].id;
        for(int j=0;j<niza[i].brojnaproizvodi;j++) {
            cin>> niza[i].niza[j].ime>>niza[i].niza[j].cena;
        }
    }
    printAveragePriceOfLowestItems(niza,n);
    printHighestPriceItem(niza, n);

    return 0;
}
