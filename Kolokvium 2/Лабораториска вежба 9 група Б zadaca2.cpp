// Да се имплементира класа Flight во која се чува:

// кодот на летот(низа од најмногу 40 знаци)
// градот на заминување(низа од најмногу 100 знаци)
// градот на пристигнување(низа од најмногу 100 знаци)
// цена на лет(децимален број)
// цена на багаж(децимален број)
// За оваа класа да се имплементираат следните методи:

// функција calculateTotalPrice() што ја враќа збир од цената на летот и цената на багажот
// функција displayInfo() за печатење на летот во формат:
// [ Код Од До Цена]

// Да се имплементира класа EconomyFlight во која покрај основните информации за летот дополнително се чува:

// број на седиште(низа од најмногу 4 карактери)
// Во оваа класа да се препокрие соодветно функцијата calculateTotalPrice() така што на основната цена на летот ќе се пресмета LOYALTY_DISCOUNT што е статичка променлива во класата која изнесува 20% попуст. Дополнително доколку првата буква од кодот на седиштето е C или F цената на летот се зголемува 30% затоа што седиштето е до прозорецот. Доколку при пресметувањето на цената првата буква од кодот на седиштето не е A, B, C, D, E, F да се фрли исклучок InvalidSeatNumberException кој ќе ја печати пораката "Invalid Seat Number Exception". LOYALTY_DISCOUNT е статичка променлива и може да ја промени само авио компанијата. 

// Соодветно во класата исто така да се препокрие функцијата displayInfo која ќе печати во формат:

// [ Код Од До Седиште

// Total price: Вкупната Цена ]

// Дополнително во класите да се имплементираат соодветно сите потребни работи.

// ---------------------------------------
#include <iostream>
#include <cstring>
using namespace std;

class InvalidSeatNumberException {
public:
    void message() {
        cout << "Invalid Seat Number Exception" << endl;
    }
};

class Flight {
protected:
    char kod[40];
    char grad_na_zaminuvanje[100];
    char grad_na_pristignuvanje[100];
    double cena_na_let;
    double cena_na_bagaz;
    
    void copy_flight(const Flight &other) {
        strcpy(this->kod, other.kod);
        strcpy(this->grad_na_zaminuvanje, other.grad_na_zaminuvanje);
        strcpy(this->grad_na_pristignuvanje, other.grad_na_pristignuvanje);
        this->cena_na_let = other.cena_na_let;
        this->cena_na_bagaz = other.cena_na_bagaz;
    }
    
public:
    Flight() {
        strcpy(this->kod, "");
        strcpy(this->grad_na_zaminuvanje, "");
        strcpy(this->grad_na_pristignuvanje, "");
        this->cena_na_let = 0;
        this->cena_na_bagaz = 0;
    }
    
    Flight(char *code, char *from, char *to, double price, double baggagePrice) {
        strcpy(this->kod, code);
        strcpy(this->grad_na_zaminuvanje, from);
        strcpy(this->grad_na_pristignuvanje, to);
        this->cena_na_let = price;
        this->cena_na_bagaz = baggagePrice;
    }
    
    Flight(const Flight &other) {
        copy_flight(other);
    }
    
    virtual double calculateTotalPrice() {
        return cena_na_let + cena_na_bagaz;
    }
    
    virtual void displayInfo() {
        cout << "[" << kod << " " << grad_na_zaminuvanje << "-" << grad_na_pristignuvanje << " " << cena_na_let << "]" << endl;
    }
    
    virtual ~Flight() {}
};

class EconomyFlight : public Flight {
private:
    char broj_na_sediste[5];
    static int LOYALTY_DISCOUNT;

public:
    EconomyFlight() : Flight() {
        strcpy(this->broj_na_sediste, "");
    }
    
    EconomyFlight(Flight f, char *seatNumber) : Flight(f) {
        strcpy(this->broj_na_sediste, seatNumber);
    }
    
    double calculateTotalPrice() override {
        double totalPrice = cena_na_let * (1 - LOYALTY_DISCOUNT / 100.0) + cena_na_bagaz;
        if (broj_na_sediste[0] == 'C' || broj_na_sediste[0] == 'F') {
            totalPrice += cena_na_let * 0.30;
        }
        if (!(broj_na_sediste[0] == 'A' || broj_na_sediste[0] == 'B' || broj_na_sediste[0] == 'C' || broj_na_sediste[0] == 'D' || broj_na_sediste[0] == 'E' || broj_na_sediste[0] == 'F')) {
            throw InvalidSeatNumberException();
        }
        return totalPrice;
    }
    
    static void setLoyaltyDiscount(int n) {
        LOYALTY_DISCOUNT = n;
    }
    
    void displayInfo() override {
        cout << "[" << kod << " " << grad_na_zaminuvanje << "-" << grad_na_pristignuvanje << " " << broj_na_sediste << "]" << endl;
        cout << "Total price: " << calculateTotalPrice() << endl;
    }
};

int EconomyFlight::LOYALTY_DISCOUNT = 20;

int main() {
    int testCase;
    cin >> testCase;
    
    char code[40];
    char from[100];
    char to[100];
    double price;
    double baggagePrice;
    char seatNumber[5];

    if (testCase == 1) {
        cout << "===== Testiranje na klasite ======" << endl;
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> code >> from >> to >> price >> baggagePrice >> seatNumber;
            Flight f = Flight(code, from, to, price, baggagePrice);
            EconomyFlight ec = EconomyFlight(f, seatNumber);
            try {
                ec.displayInfo();
            } catch (InvalidSeatNumberException &i) {
                i.message();
            }
        }
    }
    
    if (testCase == 2) {
        cout << "===== Testiranje na isklucoci ======" << endl;
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> code >> from >> to >> price >> baggagePrice >> seatNumber;
            Flight f = Flight(code, from, to, price, baggagePrice);
            try {
                EconomyFlight ec = EconomyFlight(f, seatNumber);
                ec.displayInfo();
            } catch (InvalidSeatNumberException &i) {
                i.message();
            }
        }
    }
    
    if (testCase == 3) {
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin >> code >> from >> to >> price >> baggagePrice >> seatNumber;
        Flight f = Flight(code, from, to, price, baggagePrice);
        EconomyFlight ec = EconomyFlight(f, seatNumber);
        ec.displayInfo();
        EconomyFlight::setLoyaltyDiscount(50);
        ec.displayInfo();
    }
    
    return 0;
}
