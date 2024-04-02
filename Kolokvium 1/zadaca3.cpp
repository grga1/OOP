// За потребите на еден приватен банкар кој тргува со акции, потребно е да се направи модул за менаџирање со клиентски портфолија.

// За таа цел, треба да се креира класа StockRecord. Класата треба да содржи:

// ID, кој означува која е акцијата која се тргува (низа од 12 знаци)
// Име на компанијата која ја издала акцијата (низа од 50 знаци)
// Цена според која се купени акциите (реален број)
// Моментална цена на акцијата (реален број)
// Број на акции кои се купени (цел број)
// За класата да се дефинираат потребните конструктори и set метода за моменталната цена со потпис void setNewPrice(double c) (10 поени). Исто така, да се имплементираат методи double value() и double profit(). Првата треба да ја пресметува вредноста на акциите, а втората треба да го пресметува моменталниот профит од акциите. Пресметката се врши на следниот начин (5 поени):

// Вредност = број на акции * моментална цена 
// Профит = број на акции * (моментална цена - цена по која се купени)
// Дополнително, да се преоптовари операторот << за печатење на објектот во следниот формат (5 поени): Компанија БројНаАкции КуповнаЦена МоменталнаЦена Профит

// Да се креира класа Client која содржи:

// Име и презиме на клиентот (низа од 60 знаци)
// ID на сметка (цел број)
// Низа од компании кои ги поседува клиентот (динамичка низа од објекти од класата StockRecord)
// Број на објекти во низата (цел број)
// За класата Client да се дефинираат потребните конструктори, деструктор и метода double totalValue() која ќе ја пресметува моменталната вредност на акциите кои ги поседува клиентот. Таа се пресметува како збир од вредноста на сите акции од секоја компанија од кои е составено клиентското портфолио (15 поени). Дополнително, за класата да се преоптоварат операторите:

// += за купување на нова компанија во портфолиото (додавање на нов објект од класата StockRecord во низата со компании) (10 поени)

// << за печатење на информации за портфолиото на клиентот така што во првиот ред ќе бидат прикажани ID на сметката и моменталната вредност на портфолиото одделени со празно место, а во секој нареден ред ќе бидат прикажани компаниите од кои е составено портфолиото, секоја во посебен ред (5 поени)

// Комплетна функционанлост (5 поени)

#include <iostream>
#include <cstring>
using namespace std;

class StockRecord{

private:

    char ID[12];
    char ime[50];
    float cena;
    float momentalnaCena;
    int brojNaAkcii;

    void copy_stockrecord(const StockRecord &other){
        strcpy(this->ID,other.ID);
        strcpy(this->ime,other.ime);
        this->cena=other.cena;
        this->momentalnaCena=other.momentalnaCena;
        this->brojNaAkcii=other.brojNaAkcii;
    }

public:

    StockRecord(){
        strcpy(this->ID,"ID");
        strcpy(this->ime,"ime");
        this->cena=0;
        this->momentalnaCena=0;
        this->brojNaAkcii=0;
    }

    StockRecord(char *id,char *ime,float cena,int brakcii){
        strcpy(this->ID,id);
        strcpy(this->ime,ime);
        this->cena=cena;
        this->momentalnaCena=0;
        this->brojNaAkcii=brakcii;
    }

    StockRecord(const StockRecord &other){
        copy_stockrecord(other);
    }

    StockRecord &operator=(const StockRecord &other){
        if(this==&other)
            return *this;
        copy_stockrecord(other);
        return *this;
    }

    void setNewPrice(float price){
        this->momentalnaCena=price;
    }

    double value(){
        return  brojNaAkcii*momentalnaCena;
    }

    double profit() const{
        return  brojNaAkcii*(momentalnaCena-cena);
    }

    friend ostream &operator<<(ostream &os, const StockRecord &other){
        os<<other.ime<<" "<<other.brojNaAkcii<<" "<<other.cena<<" "<<other.momentalnaCena<<" "<<other.profit()<<endl;
        return  os;
    }

    ~StockRecord(){}
};

class Client{

private:

    char ime_prezime[60];
    int ID;
    StockRecord *niza;
    int brojNaObjektiVoNizata;

    void copy_client(const Client &other){

        strcpy(this->ime_prezime,other.ime_prezime);
        this->ID=other.ID;
        this->brojNaObjektiVoNizata=other.brojNaObjektiVoNizata;

        this->niza = new StockRecord[other.brojNaObjektiVoNizata];
        for(int i=0;i<other.brojNaObjektiVoNizata;i++)
            this->niza[i]=other.niza[i];

    }
public:
       Client(){
           strcpy(this->ime_prezime,"ime_prezime");
           this->ID=0;
           this->niza= nullptr;
           this->brojNaObjektiVoNizata=0;
       }

       Client(char *ime, int id){
           strcpy(this->ime_prezime,ime);
           this->ID=id;
           this->niza= nullptr;
           this->brojNaObjektiVoNizata=0;
       }

       Client(const Client &other){
           copy_client(other);
       }

       Client &operator=(const Client &other){
        if(this==&other)
            return *this;
        delete [] this->niza;
           copy_client(other);
           return *this;
       }

       double totalValue(){
        double s=0;
        for(int i=0;i<brojNaObjektiVoNizata;i++)
        {
            s+=niza[i].value();
        }
        return s;
       }

       Client &operator+=(StockRecord &other){

        StockRecord *tmp = new StockRecord[brojNaObjektiVoNizata+1];

        for(int i=0;i<brojNaObjektiVoNizata;i++)
            tmp[i]=this->niza[i];

        delete [] this->niza;
        tmp[brojNaObjektiVoNizata++]=other;
        this->niza = new StockRecord[brojNaObjektiVoNizata];

           for(int i=0;i<brojNaObjektiVoNizata;i++)
            this->niza[i]=tmp[i];

           delete [] tmp;
    }

    friend ostream &operator<<(ostream &os,Client &other){
        os<<other.ID<<" "<<other.totalValue()<<endl;
        for(int i=0;i<other.brojNaObjektiVoNizata;i++)
        {
            os<<other.niza[i];
        }
        return os;
    }

       ~Client(){
        delete [] niza;
       }

};

int main(){

    int test;
    cin >> test;

    if(test == 1){
        double price;
        cout << "=====TEST NA KLASATA StockRecord=====" << endl;
        StockRecord sr("1", "Microsoft", 60.0, 100);
        cout << "Konstruktor OK" << endl;
        cin >> price;
        sr.setNewPrice(price);
        cout << "SET metoda OK" << endl;
    }
    else if(test == 2){
        cout << "=====TEST NA METODITE I OPERATOR << OD KLASATA StockRecord=====" << endl;
        char id[12], company[50];
        double price, newPrice;
        int n, shares;
        cin >> n;
        for(int i = 0; i < n; ++i){
            cin >> id;
            cin >> company;
            cin >> price;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(id, company, price, shares);
            sr.setNewPrice(newPrice);
            cout << sr.value() << endl;
            cout << sr;
        }
    }
    else if(test == 3){
        cout << "=====TEST NA KLASATA Client=====" << endl;
        char companyID[12], companyName[50], clientName[50];
        int clientID, n, shares;
        double oldPrice, newPrice;
        bool flag = true;
        cin >> clientName;
        cin >> clientID;
        cin >> n;
        Client c(clientName, clientID);
        cout << "Konstruktor OK" << endl;
        for(int i = 0; i < n; ++i){
            cin >> companyID;
            cin >> companyName;
            cin >> oldPrice;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(companyID, companyName, oldPrice, shares);
            sr.setNewPrice(newPrice);
            c += sr;
            if(flag){
                cout << "Operator += OK" << endl;
                flag = false;
            }
        }
        cout << c;
        cout << "Operator << OK" << endl;
    }
    return 0;

}
