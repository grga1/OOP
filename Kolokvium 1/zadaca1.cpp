// Да се дефинира класата Pesna во која се чуваат информации за (5 поени):

// име на песна (динамички алоцирано поле од знаци)
// времетраење на песната во минути
// тип на песна кој може да биде: поп, рап или рок (енумерација tip)
// Да се обезбедат сите потребни методи за класата за правилно функционирање на програмата. (10 поени)

// Дополнително за оваа класа да се дефинира методот:

// pecati() - функција во која ќе се печатат одделени со цртичка(-): името на песната во наводници и времетраењето на песната со постфикс min. (5 поени)
// Да се креира класата CD во која се чуваат информации за (5 поени):

// низа од песни снимени на CD-то (Поле од најмногу 10 објекти од класата Pesna )
// број на песни снимени на CD-то
// максимално времетраење на песните на CD-то (во минути)
// Да се обезбедат сите потребни методи за класата за правилно функционирање на програмата. (5 поени)

// Дополнително за оваа класа да се дефинираат методите:

// dodadiPesna (Pesna p) - со кој се додава песната p на CDто, но само ако има доволно преостанато место (земајќи го предвид максималното времетраење на песните на CDто и времетраењата на песните на CD-то) и ако има помалку од 10 песни на CD-то. (10 поени)
// pecatiPesniPoTip(tip t) – со кој се печатат информациите за сите песни од тип t (поп, рап или рок). (10 поени)
// Комплетна функционалност (5 поени).

#include <iostream>
#include <cstring>
using namespace  std;

enum tip{POP=0,RAP=1,ROK=2};

class Pesna{
private:
    char *ime;
    int vremetraenje;
    tip t;

    void copy_pesna(const Pesna &other){
        this->ime= new char[strlen(other.ime)+1];
        strcpy(this->ime,other.ime);
        this->vremetraenje=other.vremetraenje;
        this->t=other.t;
    }

public:
    Pesna(){
        this->ime= nullptr;
        this->vremetraenje=0;
        this->t=POP;
    }
    Pesna(char *ime,int vremetraenje,enum tip t){
        this->ime= new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        this->vremetraenje=vremetraenje;
        this->t=t;
    }
    Pesna(const Pesna &other){
        copy_pesna(other);
    }
    void pecati(){
        cout<<"\""<<ime<<"\""<<"-"<<vremetraenje<<"min"<<endl;
    }
    enum tip getip(){
        return t;
    }
    int getVremetraenje(){
        return vremetraenje;
    }
    Pesna &operator=(const Pesna &other){
        if(this==&other)
            return *this;
        delete [] this->ime;
        copy_pesna(other);
        return *this;
    }
    ~Pesna(){
        delete [] ime;
    }
};

class CD{
private:
     Pesna niza[10];
     int brojNaPesni;
     int maxVremetraenjeNaPesniteNaCd;

     void copy_cd(const CD &other){
         for(int i=0;i<other.brojNaPesni;i++)
             this->niza[i]=other.niza[i];
         this->brojNaPesni=other.brojNaPesni;
         this->maxVremetraenjeNaPesniteNaCd=other.maxVremetraenjeNaPesniteNaCd;
     }
public:
    CD(){
        this->brojNaPesni=0;
        this->maxVremetraenjeNaPesniteNaCd=0;
    }
    CD(int vremetranje){
        this->brojNaPesni=0;
        this->maxVremetraenjeNaPesniteNaCd=vremetranje;
    }
    CD(const CD &other){
        copy_cd(other);
     }
    CD &operator=(const CD &other){
        if(this==&other)
            return *this;
        copy_cd(other);
        return *this;
    }
     void pecatiPesniPoTip(tip t){
         for(int i=0;i<brojNaPesni;i++)
         {
             if(niza[i].getip()==t)
                 niza[i].pecati();
         }
     }
     Pesna getPesna(int i){
         return niza[i];
     }
     int vkupnoVremetraenje(){
         int s=0;
         for(int i=0;i<brojNaPesni;i++)
         {
             s+=niza[i].getVremetraenje();
         }
         return s;
     }

     int getBroj(){
         return brojNaPesni;
     }
     void dodadiPesna(Pesna &p){
         int s=0;
         for(int i=0;i<brojNaPesni;i++)
         {
             s+=niza[i].getVremetraenje();
         }

         if(brojNaPesni<10&&p.getVremetraenje()+s<=maxVremetraenjeNaPesniteNaCd){
             niza[brojNaPesni++] = p;
         }

     }
     ~CD(){}
};

int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, minuti, kojtip;
    char ime[50];

    if(testCase == 1) {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime,minuti,(tip)kojtip);
        p.pecati();
    } else if(testCase == 2) {
        cout << "===== Testiranje na klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i=0; i<n; i++)
            (omileno.getPesna(i)).pecati();
    }
    else if(testCase == 3) {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i=0; i<omileno.getBroj(); i++)
            (omileno.getPesna(i)).pecati();
    }
    else if(testCase == 4) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }
    else if(testCase == 5) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }

    return 0;
}
