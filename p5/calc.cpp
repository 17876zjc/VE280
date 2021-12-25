#include <iostream>
#include <string>
#include "dlist.h"
using namespace std;

void RPN();
//EFFECTS: Simulate the calculator.
//MODIFIES: Stack 
bool isInt(string& str);
//EFFECTS: Check whether a string is a positive integer
//MODIFIES: Nothing
bool isMinusOp(char c){return c=='-';}
//EFFECTS: Check whether a character is a minus operator
//MODIFIES: Nothing
bool isNumber(char c){return (c >= '0' && c <= '9');}
//EFFECTS: Check whether a character is numerical
//MODIFIES: Nothing
int RPNop(char c, Dlist<int>& stack);
//EFFECTS: Check the char and call the corresponding function
//MODIFIES: stack
int RPNadd_minus_times(char c, Dlist<int> &stack);
//EFFECTS: Function for add minus and times
//MODIFIES: stack
int RPNdivide(Dlist<int> &stack);
//EFFECTS: Function for doing divide
//MODIFIES: stack
int RPNn(Dlist<int> &stack);
//EFFECTS: changing the top most mumber to its negative
//MODIFIES: stack
int RPNd(Dlist<int> &stack);
//EFFECTS: Duplicate the top most number
//MODIFIES: stack
int RPNr(Dlist<int> &stack);
//EFFECTS: Reverse the top 2 numbers
//MODIFIES: stack
int RPNp(Dlist<int> &stack);
//EFFECTS: Print the top most number
//MODIFIES: Nothing
int RPNc(Dlist<int> &stack);
//EFFECTS: Clear all the numbers in this stack
//MODIFIES: stack
int RPNa(Dlist<int> &stack);
//EFFECTS: Print all the numbers in this stack
//MODIFIES: Nothing
//Return value::
//0: No error
//1: "Bad input\n"
//2: "Not enough operands\n"
//3: "Divide by zero\n"


int main()
{
    RPN();
}

void RPN()// The main function
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

bool isInt(string& str) //Check whether a string is a positive int
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

int RPNop(char c, Dlist<int>& stack) //Do the opertator check
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

int RPNadd_minus_times(char ch,Dlist<int> &stack)//Add minus and times
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

int RPNdivide(Dlist<int> &stack)//Division
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

int RPNn(Dlist<int> &stack) // negative
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

int RPNd(Dlist<int> &stack)// duplicate
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

int RPNr(Dlist<int> &stack) // reverse
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

int RPNp(Dlist<int> &stack) //print
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

int RPNc(Dlist<int> &stack) //Clear all
{
    while(!stack.isEmpty())
    {
        delete stack.removeFront();
    }
    return 0;
}

int RPNa(Dlist<int> &stack) //Print all
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
