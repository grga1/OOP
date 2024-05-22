// Да се напише програма која што од датотека со име "text.txt" ќе ги одреди и ќе ги испечати на стандарден излез:

// релативната фреквенција на сите мали букви
// релативната фреквенција на сите големи букви
// Релативната фреквенција на даден(и) карактер(и) се пресметува како количник на вкупното појавување на тој/тие карактер/и со вкупниот број на карактери во текстот (да се игнорираат празните места и специјалните знаци).

// Да не се менува функцијата writeToFile().

// ----------------------------------------------------

#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
using namespace std;
void writeToFile() {
    std::ofstream outFile("text.txt");
    char c;
    while((c = std::cin.get()) != '#') {
        outFile.put(c);
    }
    outFile.close();
}

int main() {
    writeToFile();

    ifstream infile("text.txt");

    char c;
    double n=0;
    double mali=0;
    double golemi=0;
    while(infile.get(c)){
        if(islower(c)){
            mali++;
        }
        if(isupper(c))
        {
            golemi++;
        }
        if(isalpha(c))
        {
            n++;
        }
    }
    cout<<fixed<<setprecision(4);
    cout<<golemi/n<<endl;
    cout<<mali/n<<endl;
    infile.close();
    return 0;
}
