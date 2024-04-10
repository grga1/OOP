// Потребно е да се имплементираат класи File (датотека) и Folder (директориум) за работа со едноставен податочен систем.

// Во класата File треба да се чуваат следниве податоци:

// Име на датотеката (динамички алоцирана низа од знаци)
// Екстензија на датотеката (енумерација со можни вредности: txt, pdf, exe)
// Име на сопственикот на датотеката (динамички алоцирана низа од знаци)
// Големина на датотеката (цел број на мегабајти)
// Дополнително, во класата потребно е да се напишат и:

// Конструктор без параметри
// Конструктор со параметри
// Конструктор за копирање
// Деструктор
// Преоптоварување на операторот =
// Метод за печатење на информациите за една датотека (видете го излезот од тест примерите за структурата на печатење) - print()
// Метод за проверка на еднаквост помеѓу две датотеки со потпис bool equals(const File & that) кој ќе враќа true ако датотеките имаат исто име, екстензија и сопственик
// Метод за споредба на типот помеѓу две датотеки со потпис bool equalsType(const File & that) кој ќе враќа true ако датотеките се од ист тип, т.е. имаат исто име и екстензија
// Во класата Folder треба да се чуваат следниве податоци:

// Име на директориумот (динамички алоцирана низа од знаци)
// Број на датотеки во него (на почеток директориумот е празен)
// Динамички алоцирана низа од датотеки, објекти од класата File
// Дополнително, во класата потребно е да се напишат и:

// Конструктор со потпис Folder(const char* name)
// Деструктор
// Метод за печатење на информациите за еден директориум (видете го излезот од тест примерите за структурата на печатење) - print()
// Метод за бришење на датотека од директориумот со потпис void remove(const File & file) кој ќе ја избрише првата датотека од директориумот која е еднаква според equals методот
// Метод за додавање на датотека во директориумот со потпис void add(const File & file) кој ќе додава датотеката во директориумот
// Не го менувајте почетниот код.

#include<iostream>
#include<cstring>

using namespace std;

enum Extension{txt=0,pdf=1,exe=2};

class File{
private:
    char *ime;
   enum Extension e;
    char *ime_na_sopstvenikot;
    int golemina;

    void copyfile(const File &other){
        this->ime = new char[strlen(other.ime)+1];
        strcpy(this->ime,other.ime);
        this->e=other.e;
        this->ime_na_sopstvenikot = new char[strlen(other.ime_na_sopstvenikot)+1];
        strcpy(this->ime_na_sopstvenikot,other.ime_na_sopstvenikot);
        this->golemina=other.golemina;
    }

public:

  File(){
      this->ime = new char[0];
      strcpy(this->ime,"");
      this->e=txt;
      this->ime_na_sopstvenikot = new char[0];
      strcpy(this->ime_na_sopstvenikot,"");
      this->golemina=0;
  }
  File(char *ime, char *ime_na_sopstvenikot,int golemina, enum Extension e){
      this->ime = new char[strlen(ime)+1];
      strcpy(this->ime,ime);
      this->e=e;
      this->ime_na_sopstvenikot = new char[strlen(ime_na_sopstvenikot)+1];
      strcpy(this->ime_na_sopstvenikot,ime_na_sopstvenikot);
      this->golemina=golemina;
  }
  File(const File &other){
      copyfile(other);
    }
    File &operator=(const File &other){
        if(this==&other)
            return *this;
        delete [] this->ime;
        delete [] this->ime_na_sopstvenikot;
        copyfile(other);
        return *this;
    }
    void print(){
        cout<<"File name: "<<ime<<".";
        switch (e) {
            case 1:
                cout << "txt" << endl;
                break;
            case 0:
                cout << "pdf" << endl;
                break;
            case 2:
                cout << "exe" << endl;
                break;
            default:
                cout << "Unknown" << endl;
                break;
        }
        cout<<"File owner: "<<ime_na_sopstvenikot<<endl;
        cout<<"File size: "<<golemina<<endl;
    }
    bool equals(const File & that){
         bool flag=false;
        if(strcmp(this->ime,that.ime)==0)
        {
            if(this->e==that.e)
            {
                if(strcmp(this->ime_na_sopstvenikot,that.ime_na_sopstvenikot)==0)
                     flag=true;
            }
        }
        return flag;
    }
    bool equalsType(const File & that){
        bool flag=false;
        if(strcmp(this->ime,that.ime)==0) {
            if (this->e == that.e) {
                flag = true;
            }
        }
      return flag;
    }
    ~File(){
        delete [] ime;
        delete [] ime_na_sopstvenikot;
    }
};

class Folder{
private:
char *ime;
int brojNaDatoteki;
File *niza;
void copyfolder(const Folder &other){
    this->ime = new char[strlen(other.ime)+1];
    strcpy(this->ime,other.ime);
    this->brojNaDatoteki=other.brojNaDatoteki;
    this->niza= new File[other.brojNaDatoteki];
    for(int i=0;i<other.brojNaDatoteki;i++)
    {
        this->niza[i]=other.niza[i];
    }
}
public:
    Folder(){
        this->ime = new char[0];
        strcpy(this->ime,"");
        this->brojNaDatoteki=0;
        this->niza= nullptr;
    }
    Folder(const char *name){
        this->ime = new char[strlen(name)+1];
        strcpy(this->ime,name);
        this->brojNaDatoteki=0;
        this->niza= nullptr;
    }

    Folder(const Folder &other){
        copyfolder(other);
    }

    Folder &operator=(const Folder &other){
        if(this==&other)
            return *this;
        delete [] this->ime;
        delete [] this->niza;
        copyfolder(other);
        return *this;
    }
    void remove(const File & file){
    int index=-1;
    for(int i=0;i<brojNaDatoteki;i++) {
        if (niza[i].equals(file) == true) {
            index = i;
            break;
        }
    }
        File *tmp = new File[brojNaDatoteki-1];
        int j=0;
        for(int i=0;i<brojNaDatoteki;i++)
        {
            if(index!=i)
            {
                tmp[j++]=this->niza[i];
            }
        }
        delete [] this->niza;
        brojNaDatoteki--;
        this->niza = new File[brojNaDatoteki];
        for(int i=0;i<brojNaDatoteki;i++)
        {
            this->niza[i]=tmp[i];
        }
        delete [] tmp;
        }
    void add(const File & file){
    File *tmp = new File[brojNaDatoteki+1];
    for(int i=0;i<brojNaDatoteki;i++){
        tmp[i]=this->niza[i];
    }
    tmp[brojNaDatoteki++]=file;
    delete [] this->niza;
    this->niza = new File[brojNaDatoteki];
    for(int i=0;i<brojNaDatoteki;i++)
    {
        this->niza[i]=tmp[i];
    }
    delete [] tmp;
 }
  void print(){
    cout<<"Folder name: "<<ime<<endl;
    for(int i=0;i<brojNaDatoteki;i++)
    {
        niza[i].print();
    }
}

    ~Folder(){
        delete [] ime;
        delete [] niza;
    }
};

int main() {
    char fileName[20];
    char fileOwner[20];
    int ext;
    int fileSize;

    int testCase;
    cin >> testCase;
    if (testCase == 1) {
        cout << "======= FILE CONSTRUCTORS AND = OPERATOR =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File created = File(fileName, fileOwner, fileSize, (Extension) ext);
        File copied = File(created);
        File assigned = created;

        cout << "======= CREATED =======" << endl;
        created.print();
        cout << endl;
        cout << "======= COPIED =======" << endl;
        copied.print();
        cout << endl;
        cout << "======= ASSIGNED =======" << endl;
        assigned.print();
    }
    else if (testCase == 2) {
        cout << "======= FILE EQUALS & EQUALS TYPE =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File first(fileName, fileOwner, fileSize, (Extension) ext);
        first.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File second(fileName, fileOwner, fileSize, (Extension) ext);
        second.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File third(fileName, fileOwner, fileSize, (Extension) ext);
        third.print();

        bool equals = first.equals(second);
        cout << "FIRST EQUALS SECOND: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equals = first.equals(third);
        cout << "FIRST EQUALS THIRD: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        bool equalsType = first.equalsType(second);
        cout << "FIRST EQUALS TYPE SECOND: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equalsType = second.equals(third);
        cout << "SECOND EQUALS TYPE THIRD: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

    }
    else if (testCase == 3) {
        cout << "======= FOLDER CONSTRUCTOR =======" << endl;
        cin >> fileName;
        Folder folder(fileName);
        folder.print();

    }
    else if (testCase == 4) {
        cout << "======= ADD FILE IN FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        folder.print();
    }
    else {
        cout << "======= REMOVE FILE FROM FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File file(fileName, fileOwner, fileSize, (Extension) ext);
        folder.remove(file);
        folder.print();
    }
    return 0;
}
