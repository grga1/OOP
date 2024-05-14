// Да се креира класа Customer за опишување на купувачи на една книжара. За секој купувач се чуваат податоци за:

// името (низа од 50 знаци),
// електронска адреса (низа од 50 знаци),
// вид на купувач (стандардни, лојални или вип),
// основен попуст (цел број изразен во проценти),
// дополнителен попуст (цел број изразен во проценти) и
// број на купени производи. (5 поени)
// Сите лојални купувачи со покажување на клуб картичка имаат право на основниот попуст при купување од книжарата. Основниот попуст е ист за сите лојални купувачи и изнесува 10%. Оваа вредност може да се смени со одлука на раководството на книжарата. Дополнителниот попуст е фиксен и може да го користат само вип купувачите и изнесува 20%. Стандардните купувачи немаат право на попуст (5 поени).

// За оваа класа да се имплементира оператор << за печатење на купувач во формат:

// [ime_na_kupuvac]
// [email_na_kupuvac]
// [broj_na_proizvodi]
// [vid_na_kupuvac] [popust_sto_moze_da_go_koristi]
// каде попустот е 0% ако купувачот е стандарден, вредноста на основниот попуст, ако е лојален или збир од основниот и дополнителниот попуст, ако купувачот е вип. (5 поени)

// Да се креира класа за онлајн книжара FINKI-bookstore во која се чува низа од регистрирани купувачи (динамички алоцирана низа) и број на купувачи. (5 поени) За класата да се обезбедат:

// operator+= (10 поени) за додавање купувач во листата од купувачи, но само ако веќе не е дел од неа (ако во листата нема купувач со иста електронска адреса). Ако во листата постои корисник со иста електронска адреса, треба да се генерира исклучок UserExistsException. Потребно е да се обезбеди справување со исклучокот во функцијата main на означеното место. Во ваква ситуација се печати порака "The user already exists in the list" (5 поени).
// Функција update со која сите стандардни купувачи со купени повеќе од 5 производи стануваат лојални, а сите лојални купувачи со над 10 купени производи, стануваат вип (5 поени).
// Оператор << за печатење на информациите за сите регистрирани купувачи (5 поени).
// Да се обезбедат сите дополнителни методи потребни за правилно функционирање на програмата. (10 поени)

#include<iostream>
#include<string.h>
#define MAX 100
using namespace std;
class UserExistsException{
public:
    void message(){
        cout<<"The user already exists in the list!"<<endl;
    }
};
enum typeC{standard,loyal,vip};
class Customer{
private:
    char ime[50];
    char email[50];
    typeC k;
    int osnoven_popust;
    int dopolnitelen_popust;
    int broj_na_kupeni_proizvodi;
    void copy_customer(const Customer &other){
        strcpy(this->ime,other.ime);
        strcpy(this->email,other.email);
        this->k=other.k;
        this->osnoven_popust=other.osnoven_popust;
        this->dopolnitelen_popust=other.dopolnitelen_popust;
        this->broj_na_kupeni_proizvodi=other.broj_na_kupeni_proizvodi;
    }
public:
    Customer(){
        strcpy(this->ime,"");
        strcpy(this->email,"");
        this->k=standard;
        this->osnoven_popust=10;
        this->dopolnitelen_popust=20;
        this->broj_na_kupeni_proizvodi=0;
    }
    Customer(char *name,char *email, typeC tC,int numProducts){
        strcpy(this->ime,name);
        strcpy(this->email,email);
        this->k=tC;
        this->osnoven_popust=10;
        this->dopolnitelen_popust=20;
        this->broj_na_kupeni_proizvodi=numProducts;
    }
    Customer(const Customer &other){
        copy_customer(other);
    }
    Customer &operator=(const Customer &other){
        if(this==&other)
            return *this;
        copy_customer(other);
        return *this;
    }
   void setDiscount1(int x){
        this->osnoven_popust=x;
    }

     friend  ostream &operator<<(ostream &os,Customer &other){
        os<<other.ime<<"\n"<<other.email<<"\n"<<other.broj_na_kupeni_proizvodi<<"\n";
         if(other.k == standard) {
             os << "standard 0"<<endl;
         } else if(other.k == loyal) {
             os << "loyal " << other.osnoven_popust<<endl;
         } else if(other.k == vip) {
             os << "vip " << other.osnoven_popust+ other.dopolnitelen_popust<<endl;
         }

         return os;
    }

    char *getemail(){
        return email;
    }
    int getproizvodi(){
        return broj_na_kupeni_proizvodi;
    }
    typeC getk(){
        return k;
    }
    void setk(typeC kk){
        this->k=kk;
    }

    ~Customer(){}
};

class FINKI_bookstore{
private:
    Customer *niza;
    int n;
    void copy_bookstore(const FINKI_bookstore &other){
        this->niza = new Customer[other.n];
        for(int i=0;i<other.n;i++)
        {
            this->niza[i]=other.niza[i];
        }
        this->n=other.n;
    }
public:
    FINKI_bookstore(){
        this->niza= nullptr;
        this->n=0;
    }
    FINKI_bookstore(const FINKI_bookstore &other){
        copy_bookstore(other);
    }
    FINKI_bookstore &operator=(const FINKI_bookstore &other){
        if(this==&other)
            return *this;
        delete [] this->niza;
        copy_bookstore(other);
        return *this;
    }
    void setCustomers(Customer *array,int n){
        this->n=n;
        this->niza = new Customer[n];
        for(int i=0;i<n;i++)
        {
            this->niza[i]=array[i];
        }
    }
    friend  ostream  &operator<<(ostream &os,FINKI_bookstore &other){
    for(int i=0;i<other.n;i++)
    {
        os<<other.niza[i];
    }
        return os;
    }
    FINKI_bookstore &operator+=(Customer &c){
        for(int i=0;i<n;i++)
        {
            if(!strcmp(this->niza[i].getemail(),c.getemail()))
                throw UserExistsException();
        }
        Customer *tmp = new Customer[n+1];
        for(int i=0;i<n;i++)
        {
            tmp[i]=this->niza[i];
        }
        tmp[n++]=c;
        delete [] this->niza;
        this->niza = new Customer[n];
        for(int i=0;i<n;i++){
            this->niza[i]=tmp[i];
        }
        delete [] tmp;
        return *this;
    }
    void update(){
        for(int i=0;i<n;i++)
        {

            if(this->niza[i].getproizvodi()>5&&this->niza[i].getk()==standard){
                this->niza[i].setk(loyal);
            }
            else
            if(this->niza[i].getproizvodi()>10&&this->niza[i].getk()==loyal){
                this->niza[i].setk(vip);
            }

        }
    }

    ~FINKI_bookstore(){
        delete [] niza;
    }

};
int main(){
    int testCase;
    cin >> testCase;

    char name[MAX];
    char email[MAX];
    int tC;
    int discount;
    int numProducts;


    if (testCase == 1){
        cout << "===== Test Case - Customer Class ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

    }

    if (testCase == 2){
        cout << "===== Test Case - Static Members ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

        c.setDiscount1(5);

        cout << c;
    }

    if (testCase == 3){
        cout << "===== Test Case - FINKI-bookstore ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << fc <<endl;
    }

    if (testCase == 4){
        cout << "===== Test Case - operator+= ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        fc+=c;

        cout << fc;
    }

    if (testCase == 5){
        cout << "===== Test Case - operator+= (exception) ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
try{ Customer c(name,email,(typeC)tC,numProducts);
    fc += c;
}catch (UserExistsException &u){
    u.message();
}
        cout << fc;
    }

    if (testCase == 6){
        cout << "===== Test Case - update method  ======" << endl << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << "Update:" << endl;
        fc.update();
        cout << fc;
    }
    return 0;

}
