/*  Classes and objects */
#include <iostream>
#include <string>
using namespace std;
class Employee{
public:
    string Name;
    string Company;
    int Age;
};
int main(){

  Employee employee1;
  employee1.Name="Filip";
  employee1.Age=19;
  employee1.Company="GOOGLE";
  cout<<employee1.Name<<" "<<employee1.Age<<" "<<employee1.Company<<endl;
}
