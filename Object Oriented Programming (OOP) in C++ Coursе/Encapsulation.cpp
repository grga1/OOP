/* Encapsulation */

#include <iostream>
#include <string>
using namespace std;
class Employee {
private:
    string Name;
    string Company;
    int Age;
public:
    void setName(string name) {
        Name = name;
    }
    string getName() {
        return Name;
    }
    void setCompany(string company){
        Company=company;
    }
    string getCompany(){
        return Company;
    }
    void setAge(int age){
        Age=age;
    }
    int getAge(){
        return Age;
    }
    void IntroduceYourself(){
        cout<<"Name - "<<Name<<endl;
        cout<<"Company - "<<Company<<endl;
        cout<<"Age - "<<Age<<endl;
    }
};
int main() {
 Employee employee1;
  employee1.setAge(19);
  employee1.setName("Filip");
  employee1.setCompany("Google");
  cout<<employee1.getName()<<" is "<<employee1.getAge()<<" years ";
    return 0;
}
