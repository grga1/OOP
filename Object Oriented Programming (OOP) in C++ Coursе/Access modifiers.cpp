/* Access modifiers */

#include <iostream>
#include <string>
using namespace std;
class Employee{
public:
    string Name;
    string Company;
    int Age;

    void IntroduceYourself(){
        cout<<"Name - "<<Name<<endl;
        cout<<"Company - "<<Company<<endl;
        cout<<"Age - "<<Age<<endl;
    }
};
int main() {

    Employee employee1;
    employee1.Name = "Filip";
    employee1.Age = 19;
    employee1.Company = "GOOGLE";
 employee1.IntroduceYourself();
    return 0;
}
