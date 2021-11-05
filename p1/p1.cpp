#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;
bool test1(int);
bool test2(int);
bool test3(int);
bool test4(int);

//Main function
int main()
{
    int number = 0;
    int index = 0; 

    do
    {
        cout << "Please enter the integer and the test choice: ";
        cin >> number;
        cin >> index;
    }
    while(number <= 0 || number >= 10000000 || index <= 0 || index > 4);

    bool flag = false;

    switch (index) 
    {
        case 1 : flag = test1(number);
            break;
        case 2 : flag = test2(number);
            break;
        case 3 : flag = test3(number);
            break;
        case 4 : flag = test4(number);
            break;
    }

    if(flag)
    {
        cout<<"Pass";
    }
    else
    {
        cout<<"Fail";
    }

    return 0;
}

//Test function 1 for Triangle number
bool test1(int origin_num)
{
    int root = static_cast<int>(sqrt(origin_num*2));
    return (root*(root+1) == origin_num*2);
}

//Test function 2 for Power number
bool test2(int origin_num)
{
    int max_test = static_cast<int>(sqrt(origin_num));
    for (int i = 2; i <= max_test; i++)
    {
        int power = 1;
        while(power++)
        {
            int result = pow(i,power);
            if (result > origin_num)
            {
                break;
            }
            else if (result == origin_num)
            {
                return true;
            }
        }
        
    }
    return false;
}

//Test function 3 for Sum of consecutive squares
bool test3(int origin_num)
{
    int max_test = static_cast<int>(sqrt(origin_num));
    for(int i = 0; i<= max_test ; i++)
    {
        int sum = 0;
        int j = i;
        while(true)
        {
            sum += pow(j,2);
            if (sum == origin_num)
            {
                return true;
            }
            else if(sum > max_test)
            {
                break;
            }
            j++;
        }
    }
    return false;
}

//Test function 4 for Abundant number
bool test4(int origin_num)
{
    int max_test = static_cast<int>(sqrt(origin_num));
    int sum = 1;
    for (int i = 2; i <= max_test; i++)
    {
        
        double division = static_cast<double>(origin_num)/static_cast<double>(i);
        if(origin_num == i*i)
        {
            sum += i;
        }
        else if(division == static_cast<double>(origin_num/i))
        {
            sum = sum + i + origin_num/i;
        }
    }
    return(sum > origin_num);
} 