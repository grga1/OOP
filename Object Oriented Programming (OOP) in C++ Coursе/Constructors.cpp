/* Constructors */

#include <iostream>
#include <string>
using namespace std;
class Employee{
private:
    string Name;
    string Company;
    int Age;
public:
    Employee(string a,string b,int c) {
        Name = a;
        Company = b;
        Age = c;
    }
    void IntroduceYourself(){
        cout<<"Name - "<<Name<<endl;
        cout<<"Company - "<<Company<<endl;
        cout<<"Age - "<<Age<<endl;
    }
};
int main() {

    Employee employee1("Filip","GOOGLE",19);
    
    employee1.IntroduceYourself();
    
    return 0;
}
