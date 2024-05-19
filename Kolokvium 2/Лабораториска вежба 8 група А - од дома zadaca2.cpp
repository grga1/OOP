// Да се имплементира класа Athlete за која се чува:
// name (низа од карактери)
// age (int)
// Во класата да се имплементира виртуелна функција void displayInfo() која на екран печати информации за дадениот атлетичар.

// Потребно е да се имплементираат класите Runner и Jumper кои што ќе наследуваат од класата Athlete.

// За класата Runner дополнително се чуваат:

// speed - брзина на играчот(double)
// Функцијата displayInfo() ја вклучува и брзината.

// За класата Jumper дополнително се чуваат:

// height- висина на скокачот (double)
// Функцијата displayInfo() ја вклучува и висината.


// Потребно е да се имплементира класата AllRoundAthlete која што ќе наследува од класите Runner и Jumper.

// За класата AllRoundAthlete дополнително се чува:

// stamina - стамина на AllRound играчот(int)

// Функцијата displayInfo() печати вклучувајќи го и нивото на стамина.

// Да се направи глобална функцијаAthlete* findAthleteWithMaxValue(Athlete** athletes, int n) - најголема вредност за тркачите се одредува според брзина, додека кај скокачите според висина, треба да се најде играчот кој ќе има најголема вредност и да се врати покажувач кон него.
#include <iostream>
#include <cstring>

using namespace std;

class Athlete{
protected:
    char name[100];
    int age;
    void coy_athlete(const Athlete &other){
        strcpy(this->name,other.name);
        this->age=other.age;
    }
public:
    Athlete(){
        strcpy(this->name,"");
        this->age=0;
    }
    Athlete(char *name,int age){
        strcpy(this->name,name);
        this->age=age;
    }
    Athlete(const Athlete &other){
        coy_athlete(other);
    }
      virtual void displayInfo(){
        cout<<"Athlete: "<<name<<endl;
        cout<<"Age: "<<age<<endl;
    }
    ~Athlete(){}
};
class Runner:virtual public Athlete{
private:
    double speed;
public:
    Runner(){
        this->speed=0;
    }
    Runner(char *name,int age,double speed):Athlete(name,age){
this->speed=speed;
    }
    void displayInfo(){
        Athlete::displayInfo();
        cout<<"Speed: "<<speed<<" mph"<<endl;
    }
    double getSpeed(){
        return speed;
    }
    ~Runner(){}
};
class Jumper:virtual public Athlete{
private:
    double height;
public:
    Jumper(){
        this->height=0;
    }
    Jumper(char *name,int age,double height):Athlete(name,age){
        this->height=height;
    }
    void displayInfo(){
        Athlete::displayInfo();
        cout<<"Height: "<<height<<" m"<<endl;
    }
    double getHeight(){
        return height;
    }
    ~Jumper(){};
};

class AllRoundAthlete:public Runner,public Jumper{
private:
    int stamina;
public:
    AllRoundAthlete(){
        this->stamina=0;
    }
    AllRoundAthlete(char *name,int age,double speed,double height,int stamina):Athlete(name,age),Runner(name,age,speed),Jumper(name,age,height){
this->stamina=stamina;
    }
    void displayInfo(){
    Athlete::displayInfo();
        cout<<"Speed: "<<getSpeed()<<" mph"<<endl;
        cout<<"Height: "<<getHeight()<<"m"<<endl;
  cout<<"Stamina: "<<stamina<<endl;
    }
    ~AllRoundAthlete(){}
};
Athlete* findAthleteWithMaxValue(Athlete** athletes, int n){
    double maxr=-100;
    double maxj=-100;
    int indexr=-1;
    int indexj=-1;
    bool runner=false;
    for(int i=0;i<n;i++){
        Runner *r =dynamic_cast<Runner*>(athletes[i]);

        if(r&&r->getSpeed()>maxr){
            runner= true;
            maxr=r->getSpeed();
            indexr=i;
        }
        Jumper *j = dynamic_cast<Jumper*>(athletes[i]);
        if(j&&j->getHeight()>maxj){
            maxj=j->getHeight();
            indexj=i;
        }

    }
    if(indexj==-1)
    {
        if(indexr==-1)
            return NULL;
    }
    if(runner==true)
    return athletes[indexr];
    else
        return  athletes[indexj];
}
int main() {
    char name[50];
    int age;
    double speed;
    double height;
    int n;
    int choice;

    cin>>choice;
    if(choice==1)
    {
        cin>>name;
        cin>>age;
        AllRoundAthlete allRoundAthlete(name, age, 13.6, 1.80, 6);
        allRoundAthlete.displayInfo();
    }
    else {

        cin >> n;

        Athlete **athletes = new Athlete *[n];
        for (int i = 0; i < n; i++) {
            cin >> choice;
            if (choice == 1) {
                cin >> name >> age >> speed;

                athletes[i] = new Runner(name, age, speed);
            } else {
                cin >> name >> age >> height;

                athletes[i] = new Jumper(name, age, height);
            }

        }

        findAthleteWithMaxValue(athletes, n)->displayInfo();

    }


    return 0;
}
