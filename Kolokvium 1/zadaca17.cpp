// Фирмата FINKI Cloud има потреба од решение за управување со image датотеките од различните оперативни системи кои ги користат при сетирање на нови сервери. За таа цел потребно е да се дефинираат следниве класи:

// OperativenSistem
// Во класата OperativenSistem треба да се чуваат следниве податоци:

// име на оперативниот систем (динамички алоцирана низа од знаци)
// верзија (float)
// тип (енумерација со можни вредности LINUX, UNIX, WINDOWS)
// големина (во GB) (float)
// Дополнително, во рамките на класата потребно е да се дефинира:

// конструктори со и без параметри
// copy constructor
// destructor
// преоптоварување на операторот =
// метод за печатење на информациите - void pecati() (видете го излезот од тест примерите за структурата)
// метод за проверка на еднаквост помеѓу два оперативни системи (два оперативни системи се еднакви ако имаат исто име, верзија, тип и големина) - bool ednakviSe(const OperativenSistem &os)
// метод за споредба на верзии помеѓу два оперативни система - int sporediVerzija(const OperativenSistem &os), кој ќе враќа 0 доколку верзиите се исти, -1 доколку верзијата на оперативниот систем од аргументот е поголема и 1 во преостанатиот случај.
// метод за проверка дали два оперативни системи се од иста фамилија. Два оперативни системи се од иста фамилија доколку имаат исто име и се од ист тип. bool istaFamilija(const OperativenSistem &sporedba)
// Repozitorium
// Во класата Repozitorium треба да се чуваат следниве податоци:

// име на репозиториумот (низа од 20 знака)
// динамички алоцирана низа од OperativenSistem
// број на оперативни системи кои моментално се наоѓаат во репозиториумот (int)
// Дополнително, во рамките на класата потребно е да се дефинира:

// конструктор Repozitorium(const char *ime)
// деструктор
// метод void pecatiOperativniSistemi() кој ќе ги печати сите оперативни системи кои се дел од репозиториумот
// метод void izbrishi(const OperativenSistem &operativenSistem) кој ќе го избрише оперативниот систем проследен како аргумент, доколку тој се наоѓа во репозиториумот. Да се користи методот ednakviSe за споредба на два оперативни система.
// метод за додавање на оперативен систем (void dodadi(const OperativenSistem &nov)) кој ќе го има следново однесување:
// Доколку веќе постои оперативен систем од иста фамилија (да се користи методот за проверка на фамилија) кој е постар од проследениот оперативен систем, тогаш постоечкиот оперативен систем се заменува со новиот.
// Во секој друг случај, проследениот оперативен систем се додава како дополнителен во репозиториумот.

#include <iostream>
#include <cstring>
using namespace std;

enum Tip{LINUX=0,UNIX=1,WINDOWS=2};

class  OperativenSistem{
private:
    char *ime;
    float verzija;
    Tip t;
    float golemina;

    void copy_operativnisistemi(const OperativenSistem &other){
        this->ime = new char[strlen(other.ime)+1];
        strcpy(this->ime,other.ime);
        this->verzija=other.verzija;
        this->t=other.t;
        this->golemina=other.golemina;
    }

public:
    OperativenSistem(){
         this->ime = new char[0];
        strcpy(this->ime,"");
        this->verzija=0;
        this->t=LINUX;
        this->golemina=0;
    }
    OperativenSistem(char *ime,float verzija,enum Tip t,float golemina){
        this->ime = new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        this->verzija=verzija;
        this->t=t;
        this->golemina=golemina;
    }
    OperativenSistem(const OperativenSistem &other){
        copy_operativnisistemi(other);
    }
    OperativenSistem &operator=(const OperativenSistem &other){
        if(this==&other){
            return *this;
        }
        delete [] this->ime;
        copy_operativnisistemi(other);
        return *this;
    }
    void pecati(){
        cout<<"Ime: "<<ime<<" Verzija: "<<verzija<<" Tip: "<<t<<" Golemina:"<<golemina<<"GB"<<endl;
    }

    bool ednakviSe(const OperativenSistem &os){
        bool flag=false;
        if(strcmp(ime,os.ime)==0){
            if(verzija==os.verzija)
            {
                if(t==os.t)
                {
                    if(golemina==os.golemina)
                        flag= true;
                }
            }
        }
        return flag;
    }
    int sporediVerzija(const OperativenSistem &os){
        if(verzija==os.verzija)
            return 0;
        else
            if(verzija<os.verzija)
                return -1;
            else
                if(verzija>os.verzija)
                    return 1;
    }
    bool istaFamilija(const OperativenSistem &sporedba){
        bool flag=false;
          if(strcmp(ime,sporedba.ime)==0)
          {
              if(t==sporedba.t)
                  flag= true;
          }
          return flag;
    }
    ~OperativenSistem(){
        delete [] ime;
    }
};

class Repozitorium{
private:
    char ime[20];
    OperativenSistem *niza;
    int brojNaOperativniSistemi;

    void copy_repozitorium(const Repozitorium &other){
        this->niza= new OperativenSistem[other.brojNaOperativniSistemi];

        for(int i=0;i<other.brojNaOperativniSistemi;i++)
        {
            this->niza[i]=other.niza[i];
        }
        strcpy(this->ime,other.ime);
        this->brojNaOperativniSistemi=other.brojNaOperativniSistemi;
    }

public:

    Repozitorium(){
        this->niza= nullptr;
        strcpy(this->ime,"ime");
        this->brojNaOperativniSistemi=0;
    }
    Repozitorium(char *ime){
        this->niza= nullptr;
        strcpy(this->ime,ime);
        this->brojNaOperativniSistemi=0;
    }

    Repozitorium(const Repozitorium &other){
        copy_repozitorium(other);
    }

    Repozitorium &operator=(const Repozitorium &other){
        if(this==&other)
            return *this;
        delete [] niza;
        copy_repozitorium(other);
        return *this;
    }

    void pecatiOperativniSistemi(){
        cout<<"Repozitorium: "<<ime<<endl;
        for(int i=0;i<brojNaOperativniSistemi;i++)
        {
            niza[i].pecati();
        }
    }
    void izbrishi(const OperativenSistem &operativenSistem){
        int index;
        int brojac=0;
      for(int i=0;i<brojNaOperativniSistemi;i++) {
          if (niza[i].ednakviSe(operativenSistem)== true){
              index=i;
              brojac++;
              break;
          }
      }
  if(brojac==0)
      return;

      OperativenSistem *tmp = new OperativenSistem[brojNaOperativniSistemi-1];

       int j=0;

       for(int i=0;i<brojNaOperativniSistemi;i++){
          if(i!=index)
              tmp[j++]=this->niza[i];
      }

      delete [] this->niza;

      brojNaOperativniSistemi--;

      this->niza = new OperativenSistem [brojNaOperativniSistemi];
        for(int i=0;i<brojNaOperativniSistemi;i++){
                this->niza[i]=tmp[i];
        }
        delete [] tmp;
    }
    void dodadi(const OperativenSistem &nov){
        for(int i=0;i<brojNaOperativniSistemi;i++)
        {
            if(niza[i].istaFamilija(nov)== true)
            {
                if(niza[i].sporediVerzija(nov)==-1)
                {
                    niza[i]=nov;
                    return;
                }
            }
        }

    OperativenSistem *tmp = new OperativenSistem[brojNaOperativniSistemi+1];
     for(int i=0;i<brojNaOperativniSistemi;i++)
     {
         tmp[i]=this->niza[i];
     }
    tmp[brojNaOperativniSistemi++]=nov;
    delete [] this->niza;
    this->niza = new OperativenSistem[brojNaOperativniSistemi];
    for(int i=0;i<brojNaOperativniSistemi;i++)
    {
        this->niza[i] = tmp[i];
    }
    delete [] tmp;
    }
    ~Repozitorium(){
        delete [] niza;
    }
};

int main() {
    char repoName[20];
    cin>>repoName;
    Repozitorium repozitorium=Repozitorium(repoName);
    int brojOperativniSistemi = 0;
    cin>>brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i<brojOperativniSistemi; i++){
        cin>>ime;
        cin>>verzija;
        cin>>tip;
        cin>>golemina;
        OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
        repozitorium.dodadi(os);
    }

    repozitorium.pecatiOperativniSistemi();
    cin>>ime;
    cin>>verzija;
    cin>>tip;
    cin>>golemina;
    OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
    cout<<"=====Brishenje na operativen sistem====="<<endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();
    return 0;
}
