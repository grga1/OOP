#include <iostream>
#include <cstring>

using namespace std;

class NegativnaVrednost{
public:
   static void message(){
        cout<<"Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!\n";
    }
};

class Oglas{
protected:
    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    void copy_oglas(const Oglas &other){
        strcpy(this->naslov,other.naslov);
        strcpy(this->kategorija,other.kategorija);
        strcpy(this->opis,other.opis);
        this->cena=other.cena;
    }
public:
    Oglas(){
        strcpy(this->naslov,"");
        strcpy(this->kategorija,"");
        strcpy(this->opis,"");
        this->cena=0;
    }
    Oglas(char *naslov, char *kategorija,char *opis,float cena){
        strcpy(this->naslov,naslov);
        strcpy(this->kategorija,kategorija);
        strcpy(this->opis,opis);
        this->cena=cena;
    }
    Oglas &operator=(const Oglas &other){
        if(this==&other)
            return *this;
        copy_oglas(other);
        return *this;
    }
     const bool operator>(Oglas &o){
        if(this->cena>o.cena)
            return 1;
        return 0;
    }
    friend ostream  &operator<<(ostream  &os, Oglas &other){
        os<<other.naslov<<"\n"<<other.opis<<"\n"<<other.cena<<" evra"<<endl;
        return os;
    }
  float getcena(){
        return cena;
    }
    char *getnaslov(){
        return naslov;
    }
    char *getopis(){
        return opis;
    }
    char *getkategorija(){
        return kategorija;
    }

     ~Oglas(){};
};
class Oglasnik{
private:
    char ime[20];
    Oglas *niza;
    int n;
    void copy_oglasnik(const Oglasnik &other){
        strcpy(this->ime,other.ime);
        this->niza = new Oglas[other.n];
        for(int i=0;i<other.n;i++)
        {
            this->niza[i]=other.niza[i];
        }
        this->n=other.n;
    }
public:
    Oglasnik(){
        strcpy(this->ime,"");
        this->niza = nullptr;
        this->n=0;
    }
    Oglasnik(char *naziv){
        strcpy(this->ime,naziv);
        this->niza = nullptr;
        this->n=0;
    }
    Oglasnik(char* name, Oglas* oglasi, int n) {
        strcpy(this->ime, name);
        this->niza = new Oglas[n];
        for(int i = 0; i < n; i++) {
            this->niza[i] = oglasi[i];
        }
        this->n = n;
    }

    Oglasnik(const Oglasnik &other){
        copy_oglasnik(other);
    }
    Oglasnik &operator=(const Oglasnik &other){
        if(this==&other)
            return *this;
        delete [] this->niza;
        copy_oglasnik(other);
        return *this;
    }
    Oglasnik &operator+=(Oglas &o){
         if(o.getcena()<0)
             throw NegativnaVrednost();

        Oglas *tmp = new Oglas[n+1];
        for(int i=0;i<n;i++)
        {
            tmp[i]=this->niza[i];
        }
        tmp[n++]=o;
        delete [] this->niza;
        this->niza = new Oglas[n];
        for(int i=0;i<n;i++)
        {
            this->niza[i] = tmp[i];
        }
        delete [] tmp;
        return *this;
    }

    friend  ostream &operator<<(ostream &os,Oglasnik &other){
        os<<other.ime<<"\n";
        for(int i=0;i<other.n;i++)
        {
            os<<other.niza[i]<<"\n";
        }
        return os;
    }
    void oglasiOdKategorija(char *k){
        for(int i=0;i<n;i++)
        {
            if(!strcmp(niza[i].getkategorija(),k)){
                cout<<niza[i]<<"\n";
            }
        }
    }
    void najniskaCena(){
        int index=-1;
        int min=10000000;
        for(int i=0;i<n;i++)
        {
            if(niza[i].getcena()<min){
                min=niza[i].getcena();
                index=i;
            }
        }
        cout<<niza[index]<<"\n";
    }
    ~Oglasnik(){
        delete [] niza;
    }
};

int main(){

    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin>>tip;

    if (tip == 1) {
        cout << "-----Test Oglas & operator <<-----" << endl;
        cin.get();
        cin.getline(naslov, 49);
        cin.getline(kategorija, 29);
        cin.getline(opis, 99);
        cin >> cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout << o;
    } else if (tip == 2) {
        cout << "-----Test Oglas & operator > -----" << endl;
        cin.get();
        cin.getline(naslov, 49);
        cin.getline(kategorija, 29);
        cin.getline(opis, 99);
        cin >> cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
        cin.getline(naslov, 49);
        cin.getline(kategorija, 29);
        cin.getline(opis, 99);
        cin >> cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1 > o2) cout << "Prviot oglas e poskap." << endl;
        else cout << "Prviot oglas ne e poskap." << endl;
    } else if (tip == 3) {
        cout << "-----Test Oglasnik, operator +=, operator << -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl += o;
        }
        cout << ogl;
    } else if (tip == 4) {
        cout << "-----Test oglasOdKategorija -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl += o;
        }
        cin.get();
        cin.getline(k, 29);
        cout << "Oglasi od kategorijata: " << k << endl;
        ogl.oglasiOdKategorija(k);

    } else if (tip == 5) {
        cout << "-----Test Exception -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            try {
                ogl += o;
            }
            catch (NegativnaVrednost &n){
                n.message();
            }
        }
        cout << ogl;

    } else if (tip == 6) {
        cout << "-----Test najniskaCena -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl += o;
        }
        cout << "Oglas so najniska cena:" << endl;
        ogl.najniskaCena();

    } else if (tip == 7) {
        cout << "-----Test All -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            try {

                ogl += o;
            }catch (NegativnaVrednost &n){
                n.message();
            }
        }
        cout << ogl;

        cin.get();
        cin.get();
        cin.getline(k, 29);
        cout << "Oglasi od kategorijata: " << k << endl;
        ogl.oglasiOdKategorija(k);

        cout << "Oglas so najniska cena:" << endl;
        ogl.najniskaCena();

    }

    return 0;
}
