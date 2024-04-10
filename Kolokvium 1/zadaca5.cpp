// За потребите на една продавница за гитари, потребно е да се направи програма за менаџирање на магацинот.

// За таа цел, треба да се креира класа Gitara (5 поени). Класата треба да содржи:

// Сериски број (низа од 25 знаци)
// Набавна цена (реален број)
// Година на производство (цел број)
// Тип (низа од 40 знаци)
// Да се дефинира метод daliIsti кој како аргумент ќе добие објект од тип Gitara и ќе ги спореди двете гитари според нивниот сериски број (5 поени)

// Дополнително, за оваа класа да се направи функција pecati() за печатење на објектот во следниот формат (5 поени):

// [СерискиБрој] [Тип] [Цена]

// Да се креира класа Magacin (5 поени) која содржи:

// Име на магацинот (низа од 30 знаци)
// Локација на магацинот (низа од 60 знаци)
// Низа од гитари кои ги поседува магацинот (динамички алоцирана низа од објекти од класата Gitara)
// Број на објекти во низата (цел број)
// Година на отвoрање (цел број)
// За класата Magacin да се дефинира метод double vrednost() што ќе ја пресметува моменталната вредност на гитарите кои се наоѓаат во магацинот. Таа се пресметува како збир од вредноста на сите гитари од кои е составен магацинот (5 поени).

// Дополнително, за класата да се дефинираат функциите:

// -void dodadi(Gitara d) за сместување на нова гитара во магацин (додавање на нов објект од класата Gitara во динамички алоцираната низа со гитари) (10 поени)

// -void prodadi(Gitara p) за бришење на дадена гитара од магацинот (бришење на сите објекти кои се исти како аргументот проследен во фунцијата)(10 поени)

// -void pecati(bool daliNovi) за печатење на информации за магацинот така што во првиот ред ќе биде прикажано имете и локацијата на магацинот, а потоа во секој нареден ред ќе бидат прикажани гитарите кои се наоѓаат во магацинот. Доколку пратената променлива има вредност true ќе се печатат само гитарите кои имаат година на производство понова од годината на отварање на магацинот. Во спротивно се печатат сите гитари (5 поени).

// За класите да се дефинираат потребните конструктори, деструктор и сите останати методи за правилно функционирање на програмата (5 поени). Сите податочни членови во класите се приватни.

#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;

class Gitara{
private:
    char seriski_broj[25];
    double cena;
    int godina_na_proizvodstvo;
    char tip[40];

    void copygitara(const Gitara &other){
        strcpy(this->seriski_broj,other.seriski_broj);
        this->cena=other.cena;
        this->godina_na_proizvodstvo=other.godina_na_proizvodstvo;
        strcpy(this->tip,other.tip);
    }

public:
    Gitara(){
        strcpy(this->seriski_broj,"broj");
        this->cena=0;
        this->godina_na_proizvodstvo=0;
        strcpy(this->tip,"tip");
    }
    Gitara(char *tip,char *seriski,int godina,float cena){
        strcpy(this->seriski_broj,seriski);
        this->cena=cena;
        this->godina_na_proizvodstvo=godina;
        strcpy(this->tip,tip);
    }

    Gitara(const Gitara &other){
        copygitara(other);
    }

    Gitara &operator=(const Gitara &other){
        if(this==&other)
            return *this;
        copygitara(other);
        return *this;
    }
    bool daliIsti(Gitara &other){
        if(strcmp(this->seriski_broj,other.seriski_broj)==0)
            return true;
        else
            return false;
    }
    void pecati(){
        cout<<seriski_broj<<" "<<tip<<" "<<cena<<endl;
    }
    char *getTip(){
        return tip;
    }
    char *getSeriski(){
        return seriski_broj;
    }
    int getGodina(){
        return godina_na_proizvodstvo;
    }
    double getNabavna(){
        return cena;
    }
    ~Gitara(){}
};

class Magacin{
private:
    char ime[30];
    char lokacija[60];
    Gitara *niza;
    int brojNaObjektiVoNizata;
    int godinaNaOtvoranje;

    void copymagacin(const Magacin &other){
        strcpy(this->ime,other.ime);
        strcpy(this->lokacija,other.lokacija);
        this->niza= new Gitara[other.brojNaObjektiVoNizata];
        for(int i=0;i<other.brojNaObjektiVoNizata;i++)
            this->niza[i]=other.niza[i];
        this->brojNaObjektiVoNizata=other.brojNaObjektiVoNizata;
        this->godinaNaOtvoranje=other.godinaNaOtvoranje;
    }

public:

    Magacin(){
        strcpy(this->ime,"ime");
        strcpy(this->lokacija,"lokacija");
        this->niza= nullptr;
        this->brojNaObjektiVoNizata=0;
        this->godinaNaOtvoranje=0;
    }

    Magacin(char *ime,char *lokacija){
        strcpy(this->ime,ime);
        strcpy(this->lokacija,lokacija);
        this->niza= nullptr;
        this->brojNaObjektiVoNizata=0;
        this->godinaNaOtvoranje=0;
    }

    Magacin(char *ime,char *lokacija,int godina){
        strcpy(this->ime,ime);
        strcpy(this->lokacija,lokacija);
        this->niza= nullptr;
        this->brojNaObjektiVoNizata=0;
        this->godinaNaOtvoranje=godina;
    }

    Magacin &operator=(const Magacin &other){
        if(this==&other)
            return *this;
        delete [] this->niza;
        copymagacin(other);
        return *this;
    }

    double vrednost(){
        double s=0;
        for(int i=0;i<brojNaObjektiVoNizata;i++)
        {
            s+=niza[i].getNabavna();
        }
        return s;
    }

    void dodadi(Gitara d){
        Gitara *tmp = new Gitara[brojNaObjektiVoNizata+1];

        for(int i=0;i<brojNaObjektiVoNizata;i++)
        {
            tmp[i]=this->niza[i];
        }
        tmp[brojNaObjektiVoNizata++]=d;

        delete [] this->niza;
        this->niza = new Gitara[brojNaObjektiVoNizata];
        for(int i=0;i<brojNaObjektiVoNizata;i++)
        {
            this->niza[i]=tmp[i];
        }
        delete [] tmp;
    }

    void prodadi(Gitara p){
        int brojac=0;
        for(int i=0;i<brojNaObjektiVoNizata;i++)
        {
            if(niza[i].daliIsti(p)==false)
                ++brojac;
        }
        if(brojac==0)
            return;
        Gitara *tmp = new Gitara[brojac];
        int j=0;
        for(int i=0;i<brojNaObjektiVoNizata;i++)
        {
            if(niza[i].daliIsti(p)==false)
            {
                tmp[j++]=this->niza[i];
            }
        }
        delete [] this->niza;
        this->niza = new Gitara[brojac];
        for(int i=0;i<brojac;i++)
        {
            this->niza[i]=tmp[i];
        }
        this->brojNaObjektiVoNizata=brojac;
        delete [] tmp;
    }

    void pecati(bool daliNovi){
        cout<<ime<<" "<<lokacija<<endl;
        if(daliNovi==false){
            for(int i=0;i<brojNaObjektiVoNizata;i++)
            {
                niza[i].pecati();
            }
        }
        else{
            for(int i=0;i<brojNaObjektiVoNizata;i++)
            {
                if(niza[i].getGodina()>godinaNaOtvoranje)
                    niza[i].pecati();
            }
        }
    }
    ~Magacin(){
        delete [] niza;
    }

};


int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, godina;
    float cena;
    char seriski[50],tip[50];

    if(testCase == 1) {
        cout << "===== Testiranje na klasata Gitara ======" << endl;
        cin>>tip;
        cin>>seriski;
        cin >> godina;
        cin >> cena;
        Gitara g(tip,seriski, godina,cena);
        cout<<g.getTip()<<endl;
        cout<<g.getSeriski()<<endl;
        cout<<g.getGodina()<<endl;
        cout<<g.getNabavna()<<endl;
    } else if(testCase == 2){
        cout << "===== Testiranje na klasata Magacin so metodot print() ======" << endl;
        Magacin kb("Magacin1","Lokacija1");
        kb.pecati(false);
    }
    else if(testCase == 3) {
        cout << "===== Testiranje na klasata Magacin so metodot dodadi() ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2005);
        cin>>n;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;
            Gitara g(tip,seriski, godina,cena);
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
        kb.pecati(true);
    }

    else if(testCase == 4) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2012);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
        kb.pecati(false);
        kb.prodadi(brisi);
        kb.pecati(false);
    }
    else if(testCase == 5) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() i pecati(true) ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2011);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
        kb.pecati(true);
        kb.prodadi(brisi);
        cout<<"Po brisenje:"<<endl;
        Magacin kb3;
        kb3=kb;
        kb3.pecati(true);
    }
    else if(testCase ==6)
    {
        cout << "===== Testiranje na klasata Magacin so metodot vrednost()======" << endl;
        Magacin kb("Magacin1","Lokacija1",2011);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            kb.dodadi(g);
        }
        cout<<kb.vrednost()<<endl;
        kb.prodadi(brisi);
        cout<<"Po brisenje:"<<endl;
        cout<<kb.vrednost();
        Magacin kb3;
        kb3=kb;
    }
    return 0;
}
