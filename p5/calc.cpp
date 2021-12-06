#include <iostream>
#include <string>
#include "dlist.h"
using namespace std;

void RPN();
bool isInt(string& str);
bool isMinusOp(char c){return c=='-';}
bool isNumber(char c){return (c >= '0' && c <= '9');}
int RPNop(char c, Dlist<int>& stack);
int RPNadd_minus_times(char c, Dlist<int> &stack);
int RPNdivide(Dlist<int> &stack);
int RPNn(Dlist<int> &stack);
int RPNd(Dlist<int> &stack);
int RPNr(Dlist<int> &stack);
int RPNp(Dlist<int> &stack);
int RPNc(Dlist<int> &stack);
int RPNa(Dlist<int> &stack);
//Return value::
//0: No error
//1: "Bad input\n"
//2: "Not enough operands\n"
//3: "Divide by zero\n"


int main()
{
    RPN();
}

void RPN()
{
    Dlist<int> stack;
    string str;
    while(true)
    {
        cin>>str;
        if(isInt(str))
        {
            int* a = new int; 
            *a = stoi(str);
            stack.insertFront(a);
            continue;
        }
        else{
            if(str.length()>1)
            {
                cout<<"Bad input!\n";
                continue;
            }
            else
            {
                int res = RPNop(str[0],stack);
                if(res == -1)
                {
                    break;
                }
                else if(res == 1)
                {
                    cout << "Bad input\n";
                }
                else if(res == 2)
                {
                    cout << "Not enough operands\n";
                }
                else if(res == 3)
                {
                    cout << "Not enough operands\n";
                }
            }   
        }
    }
}

bool isInt(string& str)
{
    if(str.length() == 1)
    {
        return isNumber(str[0]);
    }
    else
    {
        if(!isMinusOp(str[0]) && !isNumber(str[0])) return false;
        for(int i = 1; (unsigned long)i < str.length(); i++)
        {
            if(!isNumber(str[i])) return false;
        }
    }
    return true;
}

int RPNop(char c, Dlist<int>& stack)
{
    switch (c)
    {
    case '+':
    case '-':
    case '*':
        return RPNadd_minus_times(c,stack);
    case '/':
        return RPNdivide(stack);
    case 'n':
        return RPNn(stack);
    case 'd':
        return RPNd(stack);
    case 'r':
        return RPNr(stack);
    case 'p':
        return RPNp(stack);
    case 'c':
        return RPNc(stack);
    case 'a':
        return RPNa(stack);
    case 'q':
        return -1;
    default:
        return 1;
    }
}

int RPNadd_minus_times(char ch,Dlist<int> &stack)
{
    int *a = NULL, *b = NULL;
    try
    {
        a = stack.removeFront();
        b = stack.removeFront();
    }
    catch(const emptyList& ex)
    {
        if(a!=NULL)
        {
            stack.insertFront(a);
        }
        return 2;
    }
    int *c = new int;
    switch(ch)
    {
        case '+':
            *c = *a + *b;
            break;
        case '-':
            *c = *b - *a;
            break;
        case '*':
            *c = (*a) * (*b);
            break;
    }
    stack.insertFront(c);
    delete a;
    delete b;
    return 0;
}

int RPNdivide(Dlist<int> &stack)
{
    int *a = NULL, *b = NULL;
    try
    {
        a = stack.removeFront();
        b = stack.removeFront();
    }
    catch(const emptyList& ex)
    {
        if(a!=NULL)
        {
            stack.insertFront(a);
        }
        return 2;
    }
    
    if (*a == 0)
    {
        stack.insertFront(b);
        stack.insertFront(a);
        return 3;
    }
    int *c = new int;
    *c = (float)(*b)/(*a);
    stack.insertFront(c);
    delete a;
    delete b;
    return 0;
}

int RPNn(Dlist<int> &stack)
{
    int *a = NULL;
    try
    {
        a = stack.removeFront();
    }
    catch(const emptyList& ex)
    {
        return 2;
    }
    *a = (*a)*(-1);
    stack.insertFront(a);
    return 0;
}

int RPNd(Dlist<int> &stack)
{
    int *a = NULL;
    try
    {
        a = stack.removeFront();
    }
    catch(const emptyList& ex)
    {
        return 2;
    }
    int *b  = new int;
    *b = *a;
    stack.insertFront(a);
    stack.insertFront(b);
    return 0;
}

int RPNr(Dlist<int> &stack)
{
    int *a = NULL; int *b = NULL;
    try
    {
        a = stack.removeFront();
        b = stack.removeFront();
    }
    catch(const exception& ex)
    {
        if(a!=NULL)
        {
            stack.insertFront(a);
        }
        return 2;
    }
    stack.insertFront(a);
    stack.insertFront(b);
    return 0;
}

int RPNp(Dlist<int> &stack)
{
    int *a = NULL;
    try
    {
        a = stack.removeFront();
    }
    catch(const emptyList& ex)
    {
        return 2;
    }
    cout<<*a<<endl;
    stack.insertFront(a);
    return 0;
}

int RPNc(Dlist<int> &stack)
{
    while(!stack.isEmpty())
    {
        delete stack.removeFront();
    }
    return 0;
}

int RPNa(Dlist<int> &stack)
{
    int *first = NULL;
    try 
    {
        first = stack.removeFront();
    }
    catch(const emptyList& ex)
    {
        cout<<endl;
        return 0;
    }
    if(stack.isEmpty())
    {
        cout<<(*first)<<endl;
        stack.insertBack(first); // ??
        return 0;
    }
    int *current = first;
    do
    {
        cout<<(*current)<<endl;
        stack.insertBack(current);
        current = stack.removeFront();
    }while(current != first);
    stack.insertFront(current);
    return 0;
}