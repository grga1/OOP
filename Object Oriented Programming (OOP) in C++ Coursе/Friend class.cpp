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
    friend class B;
};

class B{
private:
    int b;
public:
    void setb(int B){
        b=B;
    }
    int getb(){
        return b;
    }
    int zbir(A obj){
        return obj.a+b;
    }
};
int main() {
    A obj1;
    B obj2;
    obj1.seta(10);
    obj2.setb(10);
    cout<<obj2.zbir(obj1);
    return 0;
}
