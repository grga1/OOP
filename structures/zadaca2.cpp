#include <iostream>
using namespace std;

struct Engine{
    int horsepower;
    int torque;
};

struct Car{
    char ime[100];
    int godina_na_proizvodstvo;
    Engine motor;
};
void vnesi(Car &obj){
    cin>>obj.ime>>obj.godina_na_proizvodstvo>>obj.motor.horsepower>>obj.motor.torque;
}
void print(Car obj){
    cout<<"Manufacturer: "<<obj.ime<<endl;
    cout<<"Horsepower: "<<obj.motor.horsepower<<endl;
    cout<<"Torque: "<<obj.motor.torque<<endl;
}
int main()
{
    int n;
    cin>>n;
    Car niza[n];
    for(int i=0;i<n;i++)
    {
        vnesi(niza[i]);
    }

    Car niza2[2];

    niza2[0]=niza[0];
    niza2[1]=niza[0];

    for(int i=0;i<n;i++)
    {
        if(niza[i].motor.horsepower<niza2[0].motor.horsepower)
        {
            niza2[0]=niza[i];
        }
        else
            if(niza[i].motor.horsepower<niza2[i].motor.horsepower)
            {
                niza2[1]=niza[i];
            }

    }

    Car idealna;

    if(niza2[0].motor.torque<niza2[1].motor.torque)
    {
        idealna=niza2[1];
    }
    else
    {
        idealna=niza2[0];
    }

    print(idealna);
    return 0;
}
