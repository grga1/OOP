// (40 поени)

// Да се креира класа Patnik во која се чуваат податоци за патниците на еден воз и тоа: име (низа од максимум 100 знаци), класа на вагон во која се вози (цел број 1 или 2) и велосипед (булова променлива).

// За оваа класа да се преоптоварат:

// Оператор << - за печатење на информациите за патникот во формат:
// Име на патник

// Бројот на класата (1 или 2)

// Дали има велосипед?

// Потоа да се креира клaса Voz во која се чува: крајна дестинација (низа од максимум 100 знаци), динамички алоцирана низа од објекти од класата Patnik, како и број на елементи во низата (цел број), број на дозволени велосипеди (цел број).

// За класата да се обезбедат:

// Оператор += – за додавање нов патник во воз. Патник со велосипед ќе може да се качи во воз само ако возот го дозволува тоа.
// Оператор << - за печатење на крајната дестинација до која вози и листата на патници
// Функција со потпис: patniciNemaMesto(). Со оваа функција се пресметува вкупниот број на патници (од 1-ва класа и 2-ра класа) 
// за кои нема место да влезат во возот со велосипед.
// Притоа треба да се внимава дека во пресметувањето на вкупниот број патници со велосипеди кои ќе влезат во возот прво треба да се земат предвид патниците од 1-ва класа, 
//   а потоа се дозволува да влегуваат патниците од 2-ра класа се додека не се достигне максималниот број на дозволени велосипеди во возот. 
//   На крај се печати бројот на патници со велосипеди кои остануваат (не влегуваат во возот) од 1-ва класа, а потоа од 2-ра класа.

#include<iostream>
#include<cstring>
using namespace std;

class Patnik{

private:

    char ime[100];
    int klasaNaVagon;
    bool velosiped;

    void copy_patnik(const Patnik &other){
        strcpy(this->ime,other.ime);
        this->klasaNaVagon=other.klasaNaVagon;
        this->velosiped=other.velosiped;
    }

public:

    Patnik(){
        strcpy(this->ime,"ime");
        this->klasaNaVagon=0;
        this->velosiped=0;
    }

    Patnik(char *ime,int klasa,bool velosiped){
        strcpy(this->ime,ime);
        this->klasaNaVagon=klasa;
        this->velosiped=velosiped;
    }

    Patnik(const Patnik &other){
        copy_patnik(other);
    }

    Patnik &operator=(const Patnik &other){
        if(this==&other)
            return  *this;
        copy_patnik(other);
        return  *this;
    }

    friend ostream &operator<<(ostream &os,const Patnik &other) {
        os << other.ime <<endl;
        os<< other.klasaNaVagon <<endl;
        os<< other.velosiped << endl;
        cout<<endl;
        return os;
    }

    bool getVelosiped(){
        return velosiped;
    }

    int getKlasa(){
        return klasaNaVagon;
    }

    ~Patnik(){}
};

class Voz{
private:

    char krajnaDestinacija[100];
    Patnik *niza;
    int brojNaElementi;
    int brojNaDozvoleniVelosipedi;

    void copy_voz(const Voz &other){
        strcpy(this->krajnaDestinacija,other.krajnaDestinacija);
        this->brojNaElementi=other.brojNaElementi;
        this->brojNaDozvoleniVelosipedi=other.brojNaDozvoleniVelosipedi;
        this->niza= new Patnik[other.brojNaElementi];

        for(int i=0;i<other.brojNaElementi;i++)
        {
            this->niza[i]=other.niza[i];
        }
    }
public:

    Voz(){
        strcpy(this->krajnaDestinacija,"krajnadestinacija");
        this->brojNaElementi=0;
        this->brojNaDozvoleniVelosipedi=0;
        this->niza= nullptr;
    }

    Voz(char *destinacija,int brojdozvelo){
        strcpy(this->krajnaDestinacija,destinacija);
        this->brojNaElementi=0;
        this->brojNaDozvoleniVelosipedi=brojdozvelo;
        this->niza= nullptr;
    }

    Voz(const Voz &other){
        copy_voz(other);
    }

    Voz &operator=(const Voz &other){
        if(this==&other)
            return *this;
      delete [] this->niza;
        copy_voz(other);
        return *this;
    }

    Voz &operator+=( Patnik &other) {
        if (other.getVelosiped() && !brojNaDozvoleniVelosipedi)
            return *this;

        Patnik *tmp = new Patnik[brojNaElementi + 1];

        for (int i = 0; i < brojNaElementi; i++)

            tmp[i] = this->niza[i];

        tmp[brojNaElementi++] = other;

        delete[] this->niza;

        this->niza = new Patnik[brojNaElementi];

        for (int i = 0; i < this->brojNaElementi; i++) {
            this->niza[i] = tmp[i];
        }
        delete[] tmp;
        return *this;
    }

    void patniciNemaMesto(){
        int mesto1=0,mesto2=0,v=brojNaDozvoleniVelosipedi;
        for(int i=0;i<brojNaElementi;i++){
            if(niza[i].getVelosiped()&&niza[i].getKlasa()==1)
            {
                if(v){
                    v--;
                }
                else
                {
                    mesto1++;
                }
            }
        }

        for(int i=0;i<brojNaElementi;i++){
            if(niza[i].getVelosiped()&&niza[i].getKlasa()==2)
            {
                if(v){
                    v--;
                }
                else
                {
                    mesto2++;
                }
            }
        }
        cout<<"Brojot na patnici od 1-va klasa koi ostanale bez mesto e: " << mesto1 << "\n";
        cout << "Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: " << mesto2 << "\n";
    }
    friend ostream &operator<<(ostream &os,Voz &other){
        os<<other.krajnaDestinacija<<endl;
        for(int i=0;i<other.brojNaElementi;i++)
        {
            os<<other.niza[i];
        }
        return os;
    }
    ~Voz(){
        delete [] niza;
    }
};
int main()
{
    Patnik p;
    char ime[100], destinacija[100];
    int n;
    bool velosiped;
    int klasa;
    int maxv;
    cin >> destinacija >> maxv;
    cin >> n;
    Voz v(destinacija, maxv);
    //cout<<v<<endl;
    for (int i = 0; i < n; i++){
        cin >> ime >> klasa >> velosiped;
        Patnik p(ime, klasa, velosiped);
        //cout<<p<<endl;
        v += p;
    }
    cout << v;
    v.patniciNemaMesto();

    return 0;
}
