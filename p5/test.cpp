#include <iostream>

using namespace std;

class A{
    public:
        A(){};
        A(int a){};
};

int main()
{
    A a;
    a = A(1);
    return 0;
}