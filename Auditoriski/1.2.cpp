/* Date
Да се напише програма која ќе споредува два датуми (ден, месец, година) 
и ќе ја пресмета разликата во денови од едниот до другиот датум. Пресметките да се реализираат во посебни функции.
За датумот да се дефинира посебна структура date. */
#include <iostream> 
using namespace std;
struct Date{
    int day;
    int month;
    int year;
};
void vnesi(Date &date){
    cin>>date.day>>date.month>>date.year;
}
void pecati(Date date){
    cout<<date.day<<" "<<date.month<<" "<<date.year<<endl;
}
int razlika(Date d1,Date d2){
    int raz=d1.day-d2.day;
    raz+=(d1.month-d2.month)*30;
    raz+=(d1.year-d2.year)*365;
    if(raz<0)
        raz*=-1;
    return raz;
}
int main(){
    Date d1,d2;
    vnesi(d1);
    vnesi(d2);
    pecati(d1);
    pecati(d2);
    cout<<razlika(d1,d2);
    return 0;
}
