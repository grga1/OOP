// Да се дефинира класа IceCream во која се чуваат податоци за:

// име (динамичка низа од знаци),
// состав (низа од знаци, најмногу 100)
// цена (децимален број),
// попуст (цел број, изразен во проценти) иницијална вредност 0.
// За потребите на класата да се имплементираат:

// соодветни конструктори и деструктор (да се погледнат повиците во функцијата main)
// оператор << за печатење на податоците за сладоледот во следниов формат:
// име: состав цена [цена на попуст]

// делот „цена на попуст“ се печати само ако за сладоледот се нуди попуст (вредноста на попустот е поголема од нула)

// оператор ++ во префикс нотација за зголемување на попустот за 5
// оператор + - за собирање на објект од класата IceCream со низа од знаци. Собирањето се реализира на начин што името на новиот сладолед се добива со спојување на името на сладоледот и низата од знаци одделени со „ + “. Цената на новиот сладолед се зголемува за 10, а попустот и составот на сладоледот остануваат исти.
// метод void setDiscount(int discount) со кој може да се смени вредноста на попустот. Дозволените вредности на попустот се во интервалот [0,100]
// метод void setName(char* name) со кој се менува името на сладоледот.
// Да се креира класа IceCreamShop во која се чува:

// име на продавницата (низа од знаци, најмногу 50)
// динамички резервирано поле од објекти од класата IceCream
// број на сладоледи во полето (цел број).
// За оваа класа да се обезбедат:

// соодветни конструктори и деструктор (погледнете ги повиците во main функцијата)
// оператор += за додавање нов објект од класата IceCream во полето
// оператор << за печатење на листа од сите сладоледи во продавницата. Прво се печати името на продавницата, а потоа се печатат податоците за сите сладоледи одделени со нов ред.

#include <iostream>
#include <cstring>
using namespace std;

class IceCream{
private:
    char *ime;
    char sostav[100];
    float cena;
    int popust;
    void copy_icecream(const IceCream &other){
        this->ime = new char[strlen(other.ime)+1];
        strcpy(this->ime,other.ime);
        strcpy(this->sostav,other.sostav);
        this->cena=other.cena;
        this->popust=other.popust;
    }
public:
    IceCream(){
        this->ime = new char[0];
        strcpy(this->ime,"");
        strcpy(this->sostav,"sostav");
        this->cena=0;
        this->popust=0;
    }
    IceCream(char *ime,char *sostav,float cena){
        this->ime = new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        strcpy(this->sostav,sostav);
        this->cena=cena;
        this->popust=0;
    }

    IceCream(const IceCream &other){
        copy_icecream(other);
    }

    IceCream &operator=(const IceCream &other){
        if(this==&other)
            return *this;
        delete [] this->ime;
        copy_icecream(other);
        return *this;
    }
    friend ostream &operator<<(ostream &os,IceCream &other){
        os<<other.ime<<": "<<other.sostav<<" "<<other.cena<<" ";
        if(other.popust>0)
        {
            float tmp=other.cena/100;
            tmp*=other.popust;
            os<<"("<<other.cena-tmp<<")";
        }
        return os;
    }
    IceCream &operator++(){
        this->popust+=5;
    }
    IceCream &operator+(char *zbor){
        char* tmp = new char[strlen(ime) + strlen(zbor) + 1];
        strcat(tmp, ime);
        strcat(tmp, " + ");
        strcat(tmp, zbor);
        strcpy(this->ime, tmp);
        cena+= 10;
    }

    void setDiscount(int discount){
        this->popust=discount;
    }
    void setName(char* name){
        this->ime = new char[strlen(name)+1];
        strcpy(this->ime,name);
    }
    ~IceCream(){
        delete [] ime;
    }

};

class IceCreamShop{
private:
    char ime[50];
    IceCream *niza;
    int brojNaSladoledi;
    void copy_shop(const IceCreamShop& other){
        strcpy(this->ime,other.ime);
        this->niza= new IceCream[other.brojNaSladoledi];
        for(int i=0;i<other.brojNaSladoledi;i++)
        {
            this->niza[i]=other.niza[i];
        }
        this->brojNaSladoledi=other.brojNaSladoledi;
    }
public:
    IceCreamShop(){
        strcpy(this->ime,"ime");
        this->niza= nullptr;
        this->brojNaSladoledi=0;
    }
    IceCreamShop(char *ime){
        strcpy(this->ime,ime);
        this->niza= nullptr;
        this->brojNaSladoledi=0;
    }
    IceCreamShop(const IceCreamShop &other){
        copy_shop(other);
    }
    IceCreamShop &operator+=(IceCream &other){
        IceCream *tmp = new IceCream[brojNaSladoledi+1];
        for(int i=0;i<brojNaSladoledi;i++)
        {
            tmp[i]=this->niza[i];
        }
        tmp[brojNaSladoledi++]=other;
        delete [] this->niza;
        this->niza = new IceCream[brojNaSladoledi];
        for(int i=0;i<brojNaSladoledi;i++)
        {
            this->niza[i]=tmp[i];
        }
        delete [] tmp;
return *this;
    }
    friend ostream &operator<<(ostream &os,IceCreamShop &other){
        os<<other.ime<< "\n";
        for(int i=0;i<other.brojNaSladoledi;i++){
            os<<other.niza[i]<<"\n";
        }
        return os;
    }
    ~IceCreamShop(){
        delete [] niza;
    }


};

int main() {
    char name[100];
    char ingr[100];
    float price;
    int discount;

    int testCase;

    cin >> testCase;
    cin.get();
    if(testCase == 1) {
        cout << "====== TESTING IceCream CLASS ======" << endl;
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        ic1.setDiscount(discount);
        cin.get();
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        IceCream ic2(name, ingr, price);
        ic2.setDiscount(discount);
        cout << "OPERATOR <<" << endl;
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR ++" << endl;
        ++ic1;
        cout << ic1 << endl;
        cout << "OPERATOR +" << endl;
        IceCream ic3 = ic2 + "chocolate";
        cout << ic3 << endl;
    } else if(testCase == 2) {
        cout << "====== TESTING IceCream CONSTRUCTORS ======" << endl;
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        //cin >> discount;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        cout << ic1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        IceCream ic2(ic1);
        cin.get();
        cin.getline(name,100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR =" << endl;
        ic1 = ic2;
        cin.getline(name,100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;

        cin >> discount;
        ic1.setDiscount(discount);


    } else if(testCase == 3) {
        cout << "====== TESTING IceCreamShop ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        cout << "CONSTRUCTOR" << endl;
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        cout << "OPERATOR +=" << endl;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
            cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        cout << ics;
    } else if(testCase == 4) {
        cout << "====== TESTING IceCreamShop CONSTRUCTORS ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
            cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        IceCream x("FINKI fruits", "strawberry ice cream, raspberry ice cream, blueberry ice cream", 60);
        IceCreamShop icp = ics;
        ics+=x;
        cout << ics << endl;
        cout << icp << endl;
    }


    return 0;
}
