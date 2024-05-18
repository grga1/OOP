// Да се креира класа за опишување на еден сервис за мобилни уреди. За секој мобилен телефон се чуваат податоци за модел (низа од 100 знаци), тип на уред (смартфон или компјутер), потребни часови за основна проверка (децимален број), година на производство (цел број). (5 поени)

// Сите уреди имаат исто времетраење за основна проверка и истата изнесува 1 час. Оваа вредност може да се смени со одлука на сервисот. Дополнително, уредите кои се понови од 2015 година имаат потреба од дополнителени 1.5 часа за проверка. При проверка, лаптопите имаат потреба од дополнителни 2 часа за софтверска дијагностика (5 поени).

// За оваа класа да се имплементира оператор << за печатење на уред во формат:

// [modelnauredotl]
// [tipnaured] [casovizaproverka]

// Каде часовите за проверка се оние од основната проверка+ дополнителни 2 часа доколку уредот е понов од 2015 + 2 часа доколу уредот е лаптоп (5 поени)

// Да се креира класа MobileServis во која се чува адреса (низа од 100 знаци), низа од уреди (динамички алоцирана низа) и број на уреди.(5 поени)

// За класата да се обезбедат:

// operatoror+= за додавање на нов уред во сервисот.(5 поени) Не смее да се дозволи годината на производство на уредот да биде поголема од 2019 или помала од 2000. Ако се направи обид за додавање на уред со невалидна година, треба да се генерира исклучок InvalidProductionDate. (10 поени)

// Функција pecatiUredi со која се печатат сите уреди со времето потребно за нивната проверка во сервисот (5 поени).

// Да се обезбедат сите дополнителни методи потребни за правилно функционирање на програмата. (5 поени)

#include <iostream>
#include <cstring>

using namespace std;

enum tip{Mobilen,Laptop};

class InvalidProductionDate{
public:
    void print(){
        cout<<"Невалидна година на производство"<<endl;
    }
};

class Device{
protected:
    char model[100];
    tip ured;
   static double casovi_za_osnovna_proverka;
    int godina;
    void copy_device(const Device &other){
        strcpy(this->model,other.model);
        this->ured=other.ured;
        this->godina=other.godina;
    }
public:
    Device(){
        strcpy(this->model,"");
        this->ured=Mobilen;
        this->godina=0;
    }
    Device(char *ime,tip tipDevice,int godina){
        strcpy(this->model,ime);
        this->ured=tipDevice;
        this->godina=godina;
    }
    Device(const Device &other){
        copy_device(other);}
    Device &operator=(const Device &other){
        if(this==&other)
            return *this;
        copy_device(other);
        return *this;
    }
    friend ostream &operator<<(ostream  &os,Device &other){
        os<<other.model<<"\n";
        if(other.ured==0)
            os<<"Mobilen"<<" ";
        else
            os<<"Laptop"<<" ";
        os<<other.proverka()<<endl;
        return os;
    }
    static void setPocetniCasovi( double cas){
        casovi_za_osnovna_proverka=cas;
    }
    int getgodina(){
        return godina;
    }
    double proverka(){
        int s=0;
if(godina>2015){
    s+=2;
}
if(ured==Laptop)
{
    s+=2;
}
return casovi_za_osnovna_proverka+s;
    }
    ~Device(){}
};

double Device::casovi_za_osnovna_proverka=1;

class MobileServis:public Device{
private:
    char adresa[100];
    Device *niza;
    int n;
    void copy_mobileservirs(const MobileServis &other){
        strcpy(this->adresa,other.adresa);
        this->niza = new Device[other.n];
        for(int i=0;i<other.n;i++)
        {
            this->niza[i]=other.niza[i];
        }
        this->n=other.n;
    }
public:
    MobileServis(){
        strcpy(this->adresa,"");
        this->niza= nullptr;
    this->n=0;
    }
    MobileServis(char *ime){
        strcpy(this->adresa,ime);
    }
    MobileServis(const MobileServis &other):Device(other){
        copy_mobileservirs(other);
    }
    MobileServis &operator=(const MobileServis &other){
        if(this==&other)
            return *this;
        copy_mobileservirs(other);
        Device::operator=(other);
        return *this;
    }
    MobileServis &operator+=(Device &d){
          if(d.getgodina()>2019||d.getgodina()<2000)
          {
              throw InvalidProductionDate();
          }
          Device *tmp = new Device[n+1];
          for(int i=0;i<n;i++)
          {
              tmp[i]=this->niza[i];
          }
          tmp[n++]=d;
          delete [] this->niza;
          this->niza = new Device[n];
          for(int i=0;i<n;i++){
              this->niza[i]=tmp[i];
          }
          delete [] tmp;
          return *this;
    }
    void pecatiCasovi(){
        cout<<"Ime: "<<adresa<<endl;
        for(int i=0;i<n;i++)
        {
            cout<<niza[i];
        }
    }
    ~MobileServis(){
        delete [] niza;
    }
};
int main()
{
    int testCase;
    cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> tipDevice;
        cin >> godina;
        Device ig(ime,(tip)tipDevice,godina);
        cin>>ime;
        MobileServis t(ime);
        cout<<ig;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            t+=tmp;
        }
        t.pecatiCasovi();
    }
    if (testCase == 3){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try {
                t += tmp;
            }catch (InvalidProductionDate &i){
                i.print();
            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 4){
        cout <<"===== Testiranje na konstruktori ======"<<endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try {
                t += tmp;
            }catch (InvalidProductionDate &i){
                i.print();
            }
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }
    if (testCase == 5){
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);

            t+=tmp;
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
        Device::setPocetniCasovi(2);
        t.pecatiCasovi();
    }

    if (testCase == 6){
        cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try {
                t += tmp;
            }catch(InvalidProductionDate &i){
                i.print();
            }
        }
        Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }

    return 0;

}

