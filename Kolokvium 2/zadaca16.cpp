// Туристичка агенција нуди различни понуди за транспорт на патници. За секоја понуда се чуваат податоци за дестинацијата (низа од знаци), основна цена (цел број) и податок за растојанието до дестинацијата изразено во km (цел број).

// Од класата Transport да се изведат класите AvtomobilTransport и KombeTransport за моделирање на понудите за транспорт кои нудат транспорт со автомобил или комбе, соодветно. За секоја понуда за транспорт со автомобил се чува податок за тоа дали во понудата има платен шофер (булова променлива), а за транспорт со комбе бројот на луѓе кои може да се превезат во комбето (цел број). (5 поени)

// За секој објект од двете изведени класи треба да бидат на располагање следниве методи:

// конструктор со аргументи што одговараат на податочните членови и set и get методи за податочните членови (5 поени)
// метод cenaTransport, за пресметување на цената на понудата на следниот начин:
// За транспорт со автомобил - основната цена се зголемува за 20% ако има платен шофер
// За транспорт со комбе - основната цена ќе се намали зависно од бројот на патници во комбето. За секој патник во комбето цената се намалува за 200 (10 поени)
// преоптоварен оператор < за споредба на две понуди за транспорт на патник според растојанието до дестинацијата. (5 поени)
// Да се имплементира функција pecatiPoloshiPonudi што на влез прима низа од понуди за транспорт на патник, бројот на елементите од низата и една понуда T. Функцијата ја печати дестинацијата, растојанието до дестинацијата и цената за понудите од низата кои се поскапи од понудата T сортирани во растечки редослед по растојанието до дестинацијата (погледни го повикот на функцијата) (10 поени)

// Комплетна функционалност на кодот (5 поени)
#include <iostream>
#include <cstring>
using namespace std;

class Transport {
protected:
    char destinacija[100];
    int osnovna_cena;
    int rastojanie;

    void copy_transport(const Transport &other) {
        strcpy(this->destinacija, other.destinacija);
        this->osnovna_cena = other.osnovna_cena;
        this->rastojanie = other.rastojanie;
    }

public:
    Transport() {
        strcpy(this->destinacija, "");
        this->osnovna_cena = 0;
        this->rastojanie = 0;
    }
Transport(char *destinacija,int cena,int rastojanie){
    strcpy(this->destinacija, destinacija);
    this->osnovna_cena = cena;
    this->rastojanie = rastojanie;
    }
    Transport(const Transport &other) {
        copy_transport(other);
    }

virtual int cenaTransport(){
        return osnovna_cena;
    }
    Transport &operator=(const Transport &other){
        if(this==&other)
            return *this;
        copy_transport(other);
        return *this;
    }
bool operator<(Transport &a){
        if(this->rastojanie<a.rastojanie)
            return 1;
        return 0;
    }
    char *getDestinacija(){
        return destinacija;
    }
    int getRastojanie(){
        return rastojanie;
    }
    ~Transport() {}
};


class AvtomobilTransport:public Transport {
private:
    bool platen_sofer;
public:
    AvtomobilTransport(){
        this->platen_sofer=0;
    }
    AvtomobilTransport(char *destinacija, int cena, int rastojanie, bool shofer) : Transport(destinacija, cena,
                                                                                             rastojanie) {
        this->platen_sofer = shofer;
    }
    int cenaTransport() {
        if (platen_sofer== true)
            return osnovna_cena *1.20;
            return osnovna_cena;
        }
~AvtomobilTransport(){}
    };

    class KombeTransport : public Transport {
    private:
        int broj_lugje;
    public:
        KombeTransport(){
            this->broj_lugje=0;
        }
        KombeTransport(char *destinacija, int cena, int rastojanie, bool lugje) : Transport(destinacija, cena,
                                                                                            rastojanie) {
            this->broj_lugje = lugje;
        }

        int cenaTransport() {

            if (broj_lugje > 0)
                return osnovna_cena - (broj_lugje+1) * 200;

            return osnovna_cena;

        }


        ~KombeTransport() {}
    };
 void pecatiPoloshiPonudi(Transport **niza,int n, Transport t){
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n-1;j++)
        {
            if(niza[j]->getRastojanie()>niza[j+1]->getRastojanie()){
                Transport *tmp=niza[j];
                niza[j]=niza[j+1];
                niza[j+1]=tmp;
            }
        }
    }
    int cenax;
    for(int i=0;i<n;i++)
    {
        if(niza[i]->cenaTransport()>t.cenaTransport())
        cout<<niza[i]->getDestinacija()<<" "<<niza[i]->getRastojanie()<<" "<<niza[i]->cenaTransport()<<endl;
    }
 }
    int main() {

        char destinacija[20];
        int tip, cena, rastojanie, lugje;
        bool shofer;
        int n;
        cin >> n;
        Transport **ponudi;
        ponudi = new Transport *[n];

        for (int i = 0; i < n; i++) {

            cin >> tip >> destinacija >> cena >> rastojanie;
            if (tip == 1) {
                cin >> shofer;
                ponudi[i] = new AvtomobilTransport(destinacija, cena, rastojanie, shofer);

            } else {
                cin >> lugje;
                ponudi[i] = new KombeTransport(destinacija, cena, rastojanie, lugje);
            }


        }

        AvtomobilTransport nov("Ohrid", 2000, 600, false);
        pecatiPoloshiPonudi(ponudi, n, nov);

        for (int i = 0; i < n; i++) delete ponudi[i];
        delete[] ponudi;
        return 0;
    }
