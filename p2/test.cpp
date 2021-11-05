#include <iostream>
#include "recursive.h"
#include "p2.h"
using namespace std;

int add(int x,int y)
{
    return x+y;
}

int main()
{
    tree_t l1 = tree_make();
    cout<<endl;
    tree_print(l1);
    cout<<endl;
    cout<<endl;
    tree_print(insert_tree(1,l1));
    return 0;
}