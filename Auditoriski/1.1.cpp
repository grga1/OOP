//Потсетување за референци
#include <iostream>
using namespace std;

void swapWithReferences(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void swapWithoutReferences(int a, int b) {
    int tmp = a;
    a = b;
    b = tmp;
}


int main() {
    int a,b;
    cin >> a >> b; //5 6

    swapWithoutReferences(a,b);

    cout << a << " " << b << endl; // 5 6 (no change )

    swapWithReferences(a,b);

    cout << a << " " << b << endl; //6 5 (swap happens)

    return 0;
}
