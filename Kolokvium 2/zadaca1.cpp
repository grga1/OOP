Издавачката куќа FINKI-Education издава онлајн и печатени книги. За секоја книга се чуваат податоци за ISBN бројот (низа од најмногу 20 знаци), насловот (низа од најмногу 50 знаци), авторот (низа од најмногу 30 знаци) и основната цена изразена во $ (реален број). Класата за опишување на книгите е апстрактна (5 поени).

За секоја онлајн книга дополнително се чуваат податоци за url од каде може да се симне (динамички резервирана низа од знаци) и големината изразена во MB (цел број). За секоја печатена книга дополнително се чуваат податоци за масата изразена во килограми (реален број) и дали ја има на залиха (логичка променлива). (5 поени)

За секој објект од двете изведени класи треба да бидат на располагање следниве методи:

Метод bookPrice, за пресметување на продажната цена на книгата на следниот начин: (10 поени)

За онлајн книга - цената се зголемува за 20% од основната цена ако книгата е поголема од 20MB

За печатена книга - цената се зголемува за 15% од основната цена ако масата на книгата е поголема од 0.7kg

Преоптоварен оператор > за споредба на две книги од каков било вид според нивната цена. (5 поени)

Преоптоварен оператор << за печатење на податоците за книгите во формат: (5 поени)
Да се имплементира функција mostExpensiveBook со потпис:

void mostExpensiveBook (Book** books, int n)

во која се печати вкупниот број на онлајн, односно, печатени книги во проследената низа посебно. (5 поени) Потоа се наоѓа и печати најскапата книга. (5 поени)

Да се обезбедат сите потребни функции за правилно функционирање на програмата. (5 поени)
  
#include <iostream>
#include <cstring>
using namespace  std;
class Book{
protected:
    char ISBN[20];
    char naslov[50];
    char avtor[30];
    float osnovna_cena;
    void copy_book(const Book &other){
        strcpy(this->ISBN,other.ISBN);
        strcpy(this->avtor,other.avtor);
        strcpy(this->naslov,other.naslov);
        this->osnovna_cena=other.osnovna_cena;
    }
public:
    Book(){
        strcpy(this->ISBN,"");
        strcpy(this->avtor,"");
        strcpy(this->naslov,"");
        this->osnovna_cena=0;
    }
    Book(char *ISBN,char *naslov,char *avtor,float osnovna_cena){
        strcpy(this->ISBN,ISBN);
        strcpy(this->avtor,avtor);
        strcpy(this->naslov,naslov);
        this->osnovna_cena=osnovna_cena;
    }
    Book(const Book &other){
        copy_book(other);
    }
    Book &operator=(const Book &other){
        if(this==&other)
            return *this;
        copy_book(other);
        return *this;
    }
    virtual float bookPrice()=0;
    friend ostream  &operator<<(ostream &os,Book &other){
        os<<other.ISBN<<": "<<other.naslov<<", "<<other.avtor<<" "<<other.bookPrice()<<endl;
        return os;
    }
    void setISBN(char *ISBN){
        strcpy(this->ISBN,ISBN);
    }
    ~Book(){}
};

class OnlineBook:public Book{
private:
    char *url;
    int golemina;
    void copy_onlinebook(const OnlineBook &other){
        strcpy(this->ISBN,other.ISBN);
        strcpy(this->avtor,other.avtor);
        strcpy(this->naslov,other.naslov);
        this->osnovna_cena=other.osnovna_cena;

        this->url = new char[strlen(other.url)+1];
        strcpy(this->url,other.url);
        this->golemina=other.golemina;
    }
public:
    OnlineBook(){
        strcpy(this->ISBN,"");
        strcpy(this->avtor,"");
        strcpy(this->naslov,"");
        this->osnovna_cena=0;

        this->url = new char[4];
        strcpy(this->url,"url");
        this->golemina=0;
    }
    OnlineBook(char *isbn,char *title,char *author,float price,char *url, int size):Book(isbn,title,author,price){
        this->url = new char[strlen(url)+1];
        strcpy(this->url,url);
        this->golemina=size;
    }
    OnlineBook(const OnlineBook &other):Book(other){
        copy_onlinebook(other);
    }
    OnlineBook &operator=(const OnlineBook &other){
        if(this==&other)
            return *this;
        Book::operator=(other);
        delete [] this->url;
        copy_onlinebook(other);
        return *this;
    }
    float bookPrice(){
        if(golemina>20)
            return osnovna_cena+((osnovna_cena/100)*20);
        else
            return osnovna_cena;
    }
    ~OnlineBook(){
        delete [] url;
    }
};

class PrintBook:public Book{
private:
    float masa;
    bool zaliha;
    void copy_printbook(const PrintBook &other){
        strcpy(this->ISBN,other.ISBN);
        strcpy(this->avtor,other.avtor);
        strcpy(this->naslov,other.naslov);
        this->osnovna_cena=other.osnovna_cena;

        this->masa=other.masa;
        this->zaliha=other.zaliha;
    }
public:
    PrintBook(){
        strcpy(this->ISBN,"");
        strcpy(this->avtor,"");
        strcpy(this->naslov,"");
        this->osnovna_cena=0;

        this->masa=0;
        this->zaliha=0;
    }
    PrintBook(char *isbn,char *title,char *author,float price,int weight,bool inStock):Book(isbn, title, author, price){
        this->masa=weight;
        this->zaliha=inStock;
    }
    PrintBook(const PrintBook &other):Book(other){
        copy_printbook(other);
    }
    PrintBook &operator=(const PrintBook &other){
        if(this==&other)
            return *this;
        Book::operator=(other);
        copy_printbook(other);
        return *this;
    }
    float bookPrice(){
        if(masa>0.7)
            return osnovna_cena+((osnovna_cena/100)*15);
        else
            return osnovna_cena;
    }
    ~PrintBook(){}
};

bool operator>(Book &a,Book &b){
    if(a.bookPrice()>b.bookPrice())
        return 1;
    else
        return 0;
}
void mostExpensiveBook (Book** books, int n){
    int printed=0;
    int online=0;
    int index=-1;
    for(int i=0;i<n;i++){
        if(dynamic_cast<OnlineBook*>(books[i]))
        {
            online++;
        }
        else
        if(dynamic_cast<PrintBook*>(books[i]))
        {
            printed++;
        }
        if(index==-1||books[i]->bookPrice()>books[index]->bookPrice())
            index=i;
    }
    if(index==-1)
        return;
    cout << "FINKI-Education\n";
    cout << "Total number of online books: " << online << "\n";
    cout << "Total number of print books: " << printed << "\n";
    cout << "The most expensive book is:\n";
    cout << *books[index] << "\n";
}
int main(){

    char isbn[20], title[50], author[30], url[100];
    int size, tip;
    float price, weight;
    bool inStock;
    Book  **books;
    int n;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing OnlineBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> url;
            cin >> size;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new OnlineBook(isbn, title, author, price, url, size);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 2){
        cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
        cin >> isbn;
        cin.get();
        cin.getline(title, 50);
        cin.getline(author, 30);
        cin >> price;
        cin >> url;
        cin >> size;
        cout << "CONSTRUCTOR" << endl;
        OnlineBook ob1(isbn, title, author, price, url, size);
        cout << ob1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        OnlineBook ob2(ob1);
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
        cout << "OPERATOR =" << endl;
        ob1 = ob2;
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
    }
    if (testCase == 3){
        cout << "====== Testing PrintBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> weight;
            cin >> inStock;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 4){
        cout << "====== Testing method mostExpensiveBook() ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i<n; i++){

            cin >> tip >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            if (tip == 1) {

                cin >> url;
                cin >> size;

                books[i] = new OnlineBook(isbn, title, author, price, url, size);

            }
            else {
                cin >> weight;
                cin >> inStock;

                books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            }
        }

        mostExpensiveBook(books, n);
    }

    for (int i = 0; i<n; i++) delete books[i];
    delete[] books;
    return 0;
}
