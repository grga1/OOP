#include <iostream>
using namespace std;
class A{
private:
    int a;
public:
    void seta(int A){
        a=A;
    }
    int geta(){
        return a;
    }
    friend void friendfunkcija(A &obj);
};

void friendfunkcija(A &obj){
 obj.a=15;
}
int main() {
    A obj1;
    obj1.seta(10);
    cout<<obj1.geta()<<endl;
    friendfunkcija(obj1);
    cout<<obj1.geta();
    return 0;
}
