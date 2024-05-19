// Да се имплементира апстрактна класа Hero за која се чува:
// име - низа од знаци од максимум 40 знаци
// attack damage - децимален број
// attack speed - децимален број
// ability power - децимален број
// Во класата да се имплементира виртуелна функција void displayInfo() која на екран печати информации за херојот и виртуелна функција float power() која ја враќа моќта на херојот.

// Потребно е да се имплементира класите LegendaryHero и SuperHero кои што ќе наследуваат од класата Hero.

// За класата LegendaryHero дополнително се чуваат:

// hiddenPowers - број на скриени моќи (цел број)
// Функцијата power() се пресметува со формулата (0.4*attack damage*hiddenPowers)+(0.25*attack speed*hiddenPowers)+(0.35*ability power*hiddenPowers)

// Функцијата displayInfo() печати во формат:

// LegendaryHero: [име] 

// Number of hidden powers: [hiddenPowers]

// Attack damage: [attack damage]

// Attack speed: [attack speed]

// Ability power: [ability power]

// Power: [power]

// За класата SuperHero дополнително се чуваат:

// isShapeshifter - bool
// Функцијата power() се пресметува со формулата attack damage+attack speed+ability power. Доколку е shapeshifter, тогаш неговата моќ се зголемува за два пати.

// Функцијата displayInfo() печати во формат:

// SuperHero: [име] 

// Shapeshifter: [Yes/No]

// Attack damage: [attack damage]

// Attack speed: [attack speed]

// Ability power: [ability power]

// Power: [power]


// Потребно е да се имплементира класата LegendarySuperHero која што ќе наследува од класите LegendaryHero и SuperHero.

// Моќта е пресметана на следниот начин: (моќта на LegendaryHero + моќта на SuperHero)/2

// Функцијата displayInfo() печати во формат:

// LegendarySuperHero: [име] 

// Attack damage: [attack damage]

// Attack speed: [attack speed]

// Ability power: [ability power]

// Power: [power]


// Да се направи глобална функција Hero *mostPowerfulLegendaryHero(Hero **heroes, int n) што ќе врати покажувач до најмоќниот легендарен херој.

#include <iostream>
#include <cstring>

using namespace std;


class Hero{
protected:
    char name[40];
    double attack_damage;
    double attack_speed;
    double ability_power;
    void copy_hero(const Hero &other){
        strcpy(this->name,other.name);
        this->attack_damage=other.attack_damage;
        this->attack_speed=other.attack_speed;
        this->ability_power=other.ability_power;
    }

public:
    Hero(){
        strcpy(this->name,"");
        this->attack_damage=0;
        this->attack_speed=0;
        this->ability_power=0;
    }
    Hero(char *name,double attackDamage,double attackSpeed,double abilityPower){
        strcpy(this->name,name);
        this->attack_damage=attackDamage;
        this->attack_speed=attackSpeed;
        this->ability_power=abilityPower;
    }
    Hero(const Hero &other){
        copy_hero(other);
    }
    virtual void displayInfo()=0;
    virtual float power()=0;
    ~Hero(){}
};
class LegendaryHero:virtual public Hero{
private:
    int hiddenPowers;
public:
    LegendaryHero(){
        this->hiddenPowers=0;
    }
    LegendaryHero(char *name,double attackDamage,double attackSpeed,double abilityPower,int hiddenPowers):Hero(name,attackDamage,attackSpeed,abilityPower){
        this->hiddenPowers=hiddenPowers;
    }

    float power(){
                return (0.4 * attack_damage * hiddenPowers) + (0.25 * attack_speed * hiddenPowers) + (0.35 * ability_power * hiddenPowers);
    }
    void displayInfo(){
        cout<<"LegendaryHero: "<<name<<endl;
        cout<<"Number of hidden powers: "<<hiddenPowers<<endl;
        cout<<"Attack damage: "<<attack_damage<<endl;
        cout<<"Attack speed: "<<attack_speed<<endl;
        cout<<"Ability power: "<<ability_power<<endl;
        cout<<"Power: "<<power()<<endl;
    }
   ~LegendaryHero(){}

};
class SuperHero:virtual public Hero{
private:
    bool isShapeshifter;
public:
    SuperHero(){
        this->isShapeshifter=0;
    }
    SuperHero(char *name,double attackDamage,double attackSpeed, double abilityPower, bool isShapeshifter):Hero(name, attackDamage, attackSpeed, abilityPower){
        this->isShapeshifter=isShapeshifter;
    }
    float power(){
        if(isShapeshifter)
        return (attack_damage+attack_speed+ability_power)*2;
        else
        return attack_damage+attack_speed+ability_power;

    }
    void displayInfo(){
        cout<<"SuperHero:"<<name<<endl;
        cout<<"Shapeshifter:";
        if(isShapeshifter== true)
            cout<<"Yes"<<endl;
        else
            cout<<"No"<<endl;
        cout<<"Attack damage:"<<attack_damage<<endl;
        cout<<"Attack speed:"<<attack_speed<<endl;
        cout<<"Ability power:"<<ability_power<<endl;
        cout<<"Power:"<<power();
    }
    ~SuperHero(){}
};
class LegendarySuperHero:public LegendaryHero,public SuperHero{
public:
    LegendarySuperHero(char *name,double attackDamage,double attackSpeed, double abilityPower,int hiddenPowers, bool isShapeshifter):Hero(name,attackDamage,attackSpeed,abilityPower),
    LegendaryHero(name,attackDamage,attackSpeed,abilityPower,hiddenPowers),
    SuperHero(name,attackDamage,attackSpeed,abilityPower,isShapeshifter){
    }
     float power(){

         return (LegendaryHero::power() + SuperHero::power()) / 2;

     }
     void displayInfo(){
         cout<<"LegendarySuperHero: "<<name<<endl;
         cout<<"Attack damage: "<<attack_damage<<endl;
         cout<<"Attack speed: "<<attack_speed<<endl;
         cout<<"Ability power: "<<ability_power<<endl;
         cout<<"Power: "<<power();
    }
};
Hero *mostPowerfulLegendaryHero(Hero **heroes, int n){
      int index=-1;
      int max=-100;
      for(int i=0;i<n;i++)
      {
         LegendaryHero *lh = dynamic_cast<LegendaryHero*>(heroes[i]);
         if(lh&&lh->power()>max){
             max=lh->power();
             index=i;
         }
      }
      if(index==-1)
          return NULL;
      return heroes[index];
}
int main() {
    char name[50];
    double attackDamage;
    double attackSpeed;
    double abilityPower;
    int hiddenPowers;
    bool isShapeshifter;
    int n;
    int choice;

    cin>>choice;
    if(choice==1)
    {
        cin>>name;
        LegendarySuperHero legendarySuperHero(name, 55, 43, 70, 2, true);
        legendarySuperHero.displayInfo();
    }
    else {

        cin >> n;

        Hero **h = new Hero *[n];
        for (int i = 0; i < n; i++) {
            cin >> choice;
            if (choice == 1) {
                cin >> name >> attackDamage >> attackSpeed >> abilityPower >> hiddenPowers;

                h[i] = new LegendaryHero(name, attackDamage, attackSpeed, abilityPower, hiddenPowers);
            } else {
                cin >> name >> attackDamage >> attackSpeed >> abilityPower >> isShapeshifter;

                h[i] = new SuperHero(name, attackDamage, attackSpeed, abilityPower, isShapeshifter);
            }

        }

        mostPowerfulLegendaryHero(h,n)->displayInfo();

    }


    return 0;
}
