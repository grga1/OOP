// Да се дефинира класа Vozac во која се чуваат информации за:

// име (низа од максимум 100 знаци)
// возраст (цел број)
// број на трки (цел број)
// дали е ветеран (да/не).
// Да се преоптоварат:

// операторот << за печатење кој ќе ги печати името, возраст, бројот на трки и дали е ветеран (се печати VETERAN)
// операторот == за споредување на два возачи според заработувачката по трка.
// Од оваа класа да се изведат две нови класи Avtomobilist и Motociklist.

// За автомобилистот дополнително се чува:

// цена на автомобилот (децимален број).
// За мотоциклистот дополнително се чува:

// моќност на мотор (цел број).
// Заработувачката по трка на возачите се пресметува како:

// за автомобилостот заработувачката по трка е $\frac{CENA_{AVTOMOBIL}}{5}$
// за мотоциклистот заработувачката по трка е $MOKJNOST_NA_MOTOR * 20$
// Секој автомобилист плаќа данок на заработка. Да се напишат соодветни методи за пресметување данок:

// за автомобилисти: ако бројот на трки е поголем од 10 стапката на данок е 15% од заработката, инаку 10% од заработката.
// за мотоциклисти: ако е ветеран стапката на данок е 25% од заработката, инаку 20% од заработката.
// Да се напше надворешна функција soIstaZarabotuvachka која како аргументи прима низа од покажувачи од класата Vocac, нивниот број, како и покажувач кон ојбект од возач и враќа како резултат бројот на возачи кои имаат иста заработувачка по трка со проследениот возач.
// #include <iostream>
#include <cstring>
using namespace  std;
class Vozac{
protected:
    char ime[100];
    int vozrast;
    int broj_na_trki;
    bool veteran;
    void copy_vozac(const Vozac &other){
        strcpy(this->ime,other.ime);
        this->vozrast=other.vozrast;
        this->broj_na_trki=other.broj_na_trki;
        this->veteran=other.veteran;
    }
public:
    Vozac(){
        strcpy(this->ime,"");
        this->vozrast=0;
        this->broj_na_trki=0;
        this->veteran=0;
    }
    Vozac(char *ime, int vozrast, int trki, bool vet){
        strcpy(this->ime,ime);
        this->vozrast=vozrast;
        this->broj_na_trki=trki;
        this->veteran=vet;
    }
    Vozac(const Vozac &other){
        copy_vozac(other);
    }
    Vozac &operator=(const Vozac &other){
        if(this==&other)
            return *this;
        copy_vozac(other);
        return *this;
    }
    friend ostream  &operator<<(ostream &os,Vozac &other){
        os<<other.ime<<endl;
        os<<other.vozrast<<endl;
        os<<other.broj_na_trki;
        if(other.veteran) {
          os<<endl;
            os << "VETERAN" << endl;
        }else
            os<<endl;
        return os;
    }
    virtual float zarabotuvacka()=0;
  virtual float danok()=0;
    bool operator==(Vozac &v){
        if(this->zarabotuvacka()>v.zarabotuvacka())
            return 1;
        else
            return 0;
    }
    ~Vozac(){}
};

class Avtomobilist:public Vozac{
private:
    float cena;
    void copy_avtomobilist(const Avtomobilist &other){
        strcpy(this->ime,other.ime);
        this->vozrast=other.vozrast;
        this->broj_na_trki=other.broj_na_trki;
        this->veteran=other.veteran;
        this->cena=other.cena;
    }
public:
    Avtomobilist(){
        strcpy(this->ime,"");
        this->vozrast=0;
        this->broj_na_trki=0;
        this->veteran=0;
    }
    Avtomobilist(char *ime,int vozrast,int trki, bool vet,float cena_avto):Vozac(ime, vozrast, trki, vet){
         this->cena=cena_avto;
    }
    Avtomobilist(const Avtomobilist &other){
        copy_avtomobilist(other);
    }
    Avtomobilist &operator=(const Avtomobilist &other){
        if(this==&other)
            return *this;
        Vozac::operator=(other);
        copy_avtomobilist(other);
        return *this;
    }
    float zarabotuvacka(){
 return this->cena/5.0;
    }
    float danok(){
        if(broj_na_trki>10)
        {
            return zarabotuvacka()/100*15;
        }
        else
            return zarabotuvacka()/100*10;
    }
    ~Avtomobilist(){};
};

class Motociklist:public Vozac{
private:
    int moknost;
    void copy_motociklist(const Motociklist &other){
        strcpy(this->ime,other.ime);
        this->vozrast=other.vozrast;
        this->broj_na_trki=other.broj_na_trki;
        this->veteran=other.veteran;
        this->moknost=other.moknost;
    }
public:
    Motociklist(){
        strcpy(this->ime,"");
        this->vozrast=0;
        this->broj_na_trki=0;
        this->veteran=0;
        this->moknost=0;
    }

    Motociklist(char *ime,int vozrast,int trki,bool vet,int mokjnost):Vozac(ime, vozrast, trki, vet){
        this->moknost=mokjnost;
    }
    Motociklist(const Motociklist &other){
        copy_motociklist(other);
    }
    Motociklist &operator=(const Motociklist &other){
        if(this==&other)
            return *this;
        Vozac::operator=(other);
        copy_motociklist(other);
        return *this;
    }
    float zarabotuvacka(){
        return this>moknost*20;
    }
    float danok(){
if(veteran== true)
    return zarabotuvacka()/100*25;
else
    return zarabotuvacka()/100*20;
    }

    ~Motociklist(){}
};

int soIstaZarabotuvachka(Vozac **arr,int n, Vozac *ptr){
 int brojac=0;
 for(int i=0;i<n;i++)
 {
     if(ptr->zarabotuvacka()==arr[i]->zarabotuvacka())
         brojac++;
 }
 return brojac;
}

int main() {
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac*[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for(int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if(i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for(int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
    return 0;
}
