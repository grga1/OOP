// Да се имплементира класа List во којашто ќе се чуваат информации за:

// броеви што се дел од листата (динамички алоцирана низа од цели броеви)
// бројот на броеви што се дел од листата
// За класата да се дефинираат следните методи:

// конструктор (со аргументи), copy-конструктор, деструктор, оператор =
// void pecati()метод што ќе ги печати информациите за листата во форматот: [број на елементи во листата]: x1 x2 .. xn sum: [сума] average: [просек]
// int sum() метод што ја враќа сумата на елементите во листата
// double average() метод што ќе го враќа просекот на броевите во листата
// Дополнително, креирајте класата ListContainer, во која што ќе се чуваат информации за:

// низа од листи (динамички алоцирана низа од објекти од класата List)
// број на елементи во низата од листи (цел број)
// број на обиди за додавање на листа во контејнерот (цел број првично поставен на нула)
// За класата потребно е да ги дефинирате следните методи:

// конструктор (default), copy-конструктор, деструктор, оператор =
// void pecati() метод што ќе ги печати информациите за контејнерот во форматот: List number: [реден број на листата] List info: [испечатени информации за листата со методот List::pecati()] \n sum: [сума] average: [просек]
// доколку контејнерот е празен се печати само порака The list is empty.
// void addNewList(List l) метод со којшто се додава листа во контејнерот
// Напомена: една листа се додава во контејнерот ако и само ако има различна сума од сите листи што се веќе додадени во контејнерот
// int sum() метод што ја враќа сумата на сите елементи во сите листи
// double average() метод што го враќа просекот на сите елементи во сите листи во контејнерот


#include <iostream>
using namespace std;

class List{
private:
    int *niza;
    int brojNaBroeviStoSeDelOdListata;

    void copylist(const List &other){
        this->niza = new int[other.brojNaBroeviStoSeDelOdListata];
        for(int i=0;i<other.brojNaBroeviStoSeDelOdListata;i++)
            this->niza[i]=other.niza[i];
        this->brojNaBroeviStoSeDelOdListata=other.brojNaBroeviStoSeDelOdListata;
    }
public:

    List(){
        this->niza= nullptr;
        this->brojNaBroeviStoSeDelOdListata=0;
    }

    List(int *niza,int n){
        this->niza = new int[n];
        for(int i=0;i<n;i++)
            this->niza[i]=niza[i];
        this->brojNaBroeviStoSeDelOdListata=n;
    }

    List(const List &other){
        copylist(other);
    }

    List &operator=(const List &other){
        if(this==&other)
            return *this;
        delete [] this->niza;
        copylist(other);
        return *this;
    }

    int sum(){
        int s=0;
        for(int i=0;i<brojNaBroeviStoSeDelOdListata;i++)
        {
            s+=niza[i];
        }
        return s;
    }

    double average(){
        return (double)sum()/brojNaBroeviStoSeDelOdListata;
    }

    void pecati(){
        cout<<brojNaBroeviStoSeDelOdListata<<": ";
        for(int i=0;i<brojNaBroeviStoSeDelOdListata;i++)
        {
            cout<<niza[i]<<" ";
        }
        cout<<"sum: "<<sum()<<" average: "<<average()<<endl;
    }
    int getbroevi(){
        return brojNaBroeviStoSeDelOdListata;
    }

    ~List(){
        delete [] niza;
    }
};

class ListContainer{
private:
    List *niza;
    int brojNaElementiVoNizata;
    int brojNaObidi;

    void copy_listcontainer(const ListContainer &other){
        this->niza = new List[other.brojNaElementiVoNizata];
        for(int i=0;i<other.brojNaElementiVoNizata;i++)
        {
            this->niza[i]=other.niza[i];
        }
        this->brojNaElementiVoNizata=other.brojNaElementiVoNizata;
        this->brojNaObidi=other.brojNaObidi;
    }

public:

    ListContainer(){
        this->niza= nullptr;
        this->brojNaElementiVoNizata=0;
        this->brojNaObidi=0;
    }

    ListContainer(const ListContainer &other){
        copy_listcontainer(other);
    }

    ListContainer &operator=(const ListContainer &other){
        if(this==&other)
            return *this;
        delete [] niza;
        copy_listcontainer(other);
        return *this;
    }
    int sum(){
        int s=0;
        for(int i=0;i<brojNaElementiVoNizata;i++)
        {
            s+=niza[i].sum();
        }
        return s;
    }
    double average(){
        int s=0;
        for(int i=0;i<brojNaElementiVoNizata;i++)
            s+=niza[i].getbroevi();
        return  (double)sum()/s;
    }

    void print(){
        if(brojNaElementiVoNizata<=0)
        {
            cout<<"The list is empty \n";
            return;
        }
        for(int i=0;i<brojNaElementiVoNizata;i++) {
            cout << "List number: " <<i+1<<" List info: ";
          niza[i].pecati();
        }
        cout<<"Sum: "<<sum()<<" Average: "<<average()<<endl;
        cout<<"Successful attempts: "<<brojNaElementiVoNizata<<" Failed attempts: "<<brojNaObidi-brojNaElementiVoNizata<<endl;
    }
    void addNewList(List l){
        brojNaObidi++;
     for(int i=0;i<brojNaElementiVoNizata;i++)
     {
         if(niza[i].sum()==l.sum())
             return;
     }

     List *tmp = new List[brojNaElementiVoNizata+1];
     for(int i=0;i<brojNaElementiVoNizata;i++){
         tmp[i]=this->niza[i];
     }
     delete [] this->niza;
     tmp[brojNaElementiVoNizata++]=l;
     this->niza = new List[brojNaElementiVoNizata];
     for(int i=0;i<brojNaElementiVoNizata;i++)
     {
         this->niza[i]=tmp[i];
     }
     delete [] tmp;
    }

    ~ListContainer(){
        delete [] niza;
    }
};

int main() {

    ListContainer lc;
    int N;
    cin>>N;

    for (int i=0;i<N;i++) {
        int n;
        int niza[100];

        cin>>n;

        for (int j=0;j<n;j++){
            cin>>niza[j];

        }

        List l=List(niza,n);

        lc.addNewList(l);
    }


    int testCase;
    cin>>testCase;

    if (testCase==1) {
        cout<<"Test case for operator ="<<endl;
        ListContainer lc1;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1=lc;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1.sum();
        lc1.average();

    }
    else {
        lc.print();
    }
}
