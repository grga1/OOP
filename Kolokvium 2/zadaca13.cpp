// Да се креира класа која претставува слика (Image) во рамките на еден компјутер. За секоја датотека се чуваат (5 поени):

// име на сликата (дин. алоцирана низа од знаци). Предефинирано поставено на untitled.
// име на корисникот кој е сопственик на датотеката (низа од макс. 50 знаци). Предефинирано поставено на unknown.
// димензии на сликата (2 цели броеви кои претставуваат ширина и висина во пиксели). Предефинирано поставени на 800.
// Од класата Imageда се изведе класата TransparentImage, која претставува слика која содржи поддржува транспарентност. За транспарентна слика дополнително се чува :

// дали поддржува нивоа на транспарентност (bool променлива, предефинирано не поддржува транспарентност).
// За класите Image и TransparentImage да биде достапна метода (fileSize)за пресметка на големината на сликата (во бајти). Големината се пресметува на сл. начин (5 поени):

// за објектите од класата Image, големината на датотеката е еднаква на:висината * ширината * 3.
// за TransparentImage, доколку поддржува нивоа на транспарентност, големината на датотеката е еднаква на ширина * висина * 4. Доколку не поддржува транспарентност, големината на сликата се пресметува како ширина * висина + бр._на_пиксели_присутни_во_сликата / 8.
// За класите Image и TransparentImage да се преоптоварат следниве оператори (5 поени):

// оператор << кој ги печати податоците од датотеката во сл. формат:

// ime_fajl avtor golemina_na_fajlot_vo_bajti

// оператор > кој ги споредува сликите според нивната големина.

// Да се дефинира класа Folder, што репрезентира директориум во кој може да се поставуваат слики. За секој фолдер се чува (5 поени):

// име на фолдерот (низа од макс 255 знаци)
// име на корисникот кој е сопственик на фолдерот (низа од макс. 50 знаци). Предефинирано поставено на unknown.
// низа од покажувачи кон Image објекти (макс. 100 во рамките на еден фолдер).
// Да се имплементираат следниве методи (5 поени):

// метода за пресметка на големината на фолдерот (folderSize). Големината на фолдерот е сума од големините од сите слики во рамките на фолдерот.

// метода за пронаоѓање на наголемата слика во рамките на фолдерот (getMaxFile). Методата враќа покажувач кон најголемата слика во фолдерот (сметано во бајти).

// За класата Folder да се имплементира и оператор += кој додава објекти од типот Image/TransparentImage во рамките на фолдерот (5 поени).

// Да се креираат следниве функционалности за класите (5 поени):

// operator << - со кој се печатат податоците за фолдерот во формат (5 поени):

// ime_folder sopstvenik --

// imeslika avtor goleminanafajlotvo_bajti
// imeslika avtor goleminanafajlotvobajti -- goleminanafoldervo_bajti
// operator [] - кој враќа покажувач кон соодветната слика во фолдерот. Доколку не постои слика на тој индекс, треба да се врати NULL (5 поени).

// Да се креира и глобална функција max_folder_size која го прима низа од објекти од типот Folder и го враќа фолдерот кој има зафаќа најмногу простор (во бајти). (5 поени)

// Да се овозможи правилно функционирање на класите (потребни set или get методи/оператори/конструктори/деструктори) според изворниот код кој е веќе зададен. Сите податочни членови на класите се protected. (5 поени)

#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

class Image {
protected:
    char *ime_na_slika;
    char ime_na_korisnik[50];
    int sirina;
    int visina;
    void copy_image(const Image &other) {
        this->ime_na_slika = new char[strlen(other.ime_na_slika) + 1];
        strcpy(this->ime_na_slika, other.ime_na_slika);
        strcpy(this->ime_na_korisnik, other.ime_na_korisnik);
        this->sirina = other.sirina;
        this->visina = other.visina;
    }
public:
    Image() {
        this->ime_na_slika = new char[10];
        strcpy(this->ime_na_slika, "untitled");
        strcpy(this->ime_na_korisnik, "unknown");
        this->sirina = 800;
        this->visina = 800;
    }
    Image(char *name) {
        this->ime_na_slika = new char[strlen(name) + 1];
        strcpy(this->ime_na_slika, name);
        strcpy(this->ime_na_korisnik, "unknown");
        this->sirina = 800;
        this->visina = 800;
    }
    Image(char *name, char *user_name) {
        this->ime_na_slika = new char[strlen(name) + 1];
        strcpy(this->ime_na_slika, name);
        strcpy(this->ime_na_korisnik, user_name);
        this->sirina = 800;
        this->visina = 800;
    }
    Image(char *name, char *user_name, int w, int h) {
        this->ime_na_slika = new char[strlen(name) + 1];
        strcpy(this->ime_na_slika, name);
        strcpy(this->ime_na_korisnik, user_name);
        this->sirina = w;
        this->visina = h;
    }
    Image(const Image &other) {
        copy_image(other);
    }
    Image &operator=(const Image &other) {
        if (this == &other)
            return *this;
        delete[] this->ime_na_slika;
        copy_image(other);
        return *this;
    }
    virtual int fileSize() {
        return visina * sirina * 3;
    }
    friend ostream &operator<<(ostream &os, Image &other) {
        os << other.ime_na_slika << " " << other.ime_na_korisnik << " " << other.fileSize() << endl;
        return os;
    }
    bool operator>(Image &b) {
        return this->fileSize() > b.fileSize();
    }
    ~Image() {
        delete[] ime_na_slika;
    }

};

class TransparentImage : public Image {
private:
    bool transparentnost;
public:
    TransparentImage() : Image() {
        this->transparentnost = 1;
    }
    TransparentImage(char *name, char *user_name, int w, int h, bool tl) : Image(name, user_name, w, h) {
        this->transparentnost = tl;
    }
    TransparentImage(const TransparentImage &other) : Image(other) {
        this->transparentnost = other.transparentnost;
    }
    TransparentImage &operator=(const TransparentImage &other) {
        if (this == &other)
            return *this;
        Image::operator=(other);
        this->transparentnost = other.transparentnost;
        return *this;
    }

    bool operator>(TransparentImage &other) {
        return fileSize() > other.fileSize();
    }
    int fileSize() {
        if (transparentnost == 1) {
            return sirina * visina * 4;
        }
        else {
            return sirina * visina + ((sirina * visina) / 8.0);
        }
    }
};

class Folder {
private:
    char ime[255];
    char ime_korisnik[50];
    Image *niza[100];
    int n;
    void copy_folder(const Folder &other) {
        strcpy(this->ime, other.ime);
        strcpy(this->ime_korisnik, other.ime_korisnik);
        for (int i = 0; i < other.n; i++) {
            this->niza[i] = other.niza[i];
        }
        this->n = other.n;
    }
public:
    Folder() {
        strcpy(this->ime, "unknown");
        strcpy(this->ime_korisnik, "unknown");
        this->n = 0;
    }
    Folder(char *name, char *user_name) {
        strcpy(this->ime, name);
        strcpy(this->ime_korisnik, user_name);
        this->n = 0;
    }
    Folder(const Folder &other) {
        copy_folder(other);
    }
    Folder& operator=(const Folder& other) {
        if (this == &other) {
            return *this;
        }
        copy_folder(other);
        return *this;
    }

    Image *getMaxFile() {
        int index = -1;

        for (int i = 0; i < n; i++) {
            if (index == -1 || niza[i]->fileSize() > niza[index]->fileSize()) {
                index = i;
            }
        }
        if (index == -1)
            return NULL;

        return niza[index];
    }

    Folder &operator+=(Image &i) {
        if (n >= 100)
            return *this;
        niza[n++] = &i;
        return *this;
    }

    int folderSize() {
        int s = 0;
        for (int i = 0; i < n; i++) {
            s += niza[i]->fileSize();
        }
        return s;
    }

    friend ostream &operator<<(ostream &os, Folder &other) {
        os << other.ime << " " << other.ime_korisnik << "\n--\n";
        for (int i = 0; i < other.n; i++) {
            os << *other.niza[i];
        }
        os << "--\nFolder size: " << other.folderSize() << "\n";
        return os;
    }
    Image* operator[](int idx) {
        return idx < n ? niza[idx] : NULL;
    }

    ~Folder() {
    }

};

Folder& max_folder_size(Folder* f, int n) {
    int idx = 0; // Initialize idx to 0 to avoid uninitialized variable issue
    for (int i = 1; i < n; i++) { // Start loop from 1 since idx is initialized to 0
        if (f[i].folderSize() > f[idx].folderSize()) { // Compare folder sizes
            idx = i;
        }
    }
    return f[idx];
}
int main() {

    int tc; // Test Case

    char name[255];
    char user_name[51];
    int w, h;
    bool tl;

    cin >> tc;

    if (tc==1){
        // Testing constructor(s) & operator << for class File

        cin >> name;
        cin >> user_name;
        cin >> w;
        cin >> h;


        Image f1;

        cout<< f1;

        Image f2(name);
        cout<< f2;

        Image f3(name, user_name);
        cout<< f3;

        Image f4(name, user_name, w, h);
        cout<< f4;
    }
    else if (tc==2){
        // Testing constructor(s) & operator << for class TextFile
        cin >> name;
        cin >> user_name;
        cin >> w >> h;
        cin >> tl;

        TransparentImage tf1;
        cout<< tf1;

        TransparentImage tf4(name, user_name, w, h, tl);
        cout<< tf4;
    }
    else if (tc==3){
        // Testing constructor(s) & operator << for class Folder
        cin >> name;
        cin >> user_name;

        Folder f3(name, user_name);
        cout<< f3;
    }
    else if (tc==4){
        // Adding files to folder
        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image * f;
        TransparentImage *tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout<<dir;
    }
    else if(tc==5){
        // Testing getMaxFile for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image* f;
        TransparentImage* tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout<< *(dir.getMaxFile());
    }
    else if(tc==6){
        // Testing operator [] for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image* f;
        TransparentImage* tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }

        cin >> sub; // Reading index of specific file
        cout<< *dir[sub];
    }
    else if(tc==7){
        // Testing function max_folder_size
        int folders_num;

        Folder dir_list[10];

        Folder dir;
        cin >> folders_num;

        for (int i=0; i<folders_num; ++i){
            cin >> name;
            cin >> user_name;
            dir = Folder(name, user_name);


            Image* f;
            TransparentImage *tf;

            int sub, fileType;

            while (1){
                cin >> sub; // Should we add subfiles to this folder
                if (!sub) break;

                cin >>fileType;
                if (fileType == 1){ // Reading File
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    f = new Image(name,user_name, w, h);
                    dir += *f;
                }
                else if (fileType == 2){
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    cin >> tl;
                    tf = new TransparentImage(name,user_name, w, h, tl);
                    dir += *tf;
                }
            }
            dir_list[i] = dir;
        }

        cout<<max_folder_size(dir_list, folders_num);
    }
    return 0;
};
