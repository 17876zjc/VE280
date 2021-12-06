#include <iostream>
#include <string>
#include <cstdlib>
#include "dlist.h"
using namespace std;

enum Status{
    regular,silver,gold,platinum
};

string FullStatus(Status a)
{
    switch (a)
    {
    case regular:
        return string("regular");
    case silver:
        return string("silver");
    case gold:
        return string("gold");
    case platinum:
        return string("platinum");
    }
    cout<<"Wrong Status!"<<endl;
    exit(20);
}

Status Str2Status(string str)
{
    if(str == "regular")
    {
        return regular;
    }
    if(str == "silver")
    {
        return silver;
    }
    if(str == "gold")
    {
        return gold;
    }
    if(str == "platinum")
    {
        return platinum;
    }
    cout<<"No matching status!"<<endl;
    exit(30);
}

class Customer
{
    private:
        int timestamp;
        string name;
        Status status;
        int duration;
    public:
        Customer(){};
        void set(int,string,string,int);
        int getTimestamp(){return timestamp;};
        int getStatus(){return (int)status;};
        int getDuration(){return duration;};
        string getName(){return name;};
        void printGetCall()const;
        void printAnserCall()const;
        ~Customer(){};
};

void Customer::set(int t, string n, string s,int d)
{
    timestamp = t;
    name = n;
    duration = d;
    status = Str2Status(s);
}

void Customer::printGetCall()const
{
    cout<<"Call from "<<name<<" a "<<FullStatus(status)<<" member"<<endl;
}

void Customer::printAnserCall()const{
    cout<<"Ansering call from "<<name<<endl;
}

int main()
{
    Dlist<Customer>customer[4];//0 1 2 3

    int num;
    int currTick = 0;
    int remainTick = 0;
    bool flag = true;
    //Initial: True
    //When the last customer stored and nothing to read: False
    Customer* tempCustomer = NULL;
    cin >> num;
    while(num > 0 || 
        !customer[0].isEmpty() || !customer[1].isEmpty() || 
        !customer[2].isEmpty() || !customer[3].isEmpty() || 
        remainTick > 0 || flag) // End statement: No one left to read, Nothing to handle
    {
        cout<<"Starting tick #"<<currTick<<endl;
        //Input part
        int t; string n; string s; int d;
        //cout<<"-----1-----"<<endl;
        if(tempCustomer == NULL && flag) // Init the first one
        {
            tempCustomer = new Customer;
            cin>>t>>n>>s>>d;
            tempCustomer->set(t,n,s,d);
            //customer[tempCustomer->getStatus()].insertBack(tempCustomer);
            num --;
        }
        //cout<<"-----2-----"<<endl;
        while(flag) //Still have customers to handle
        {
            if( currTick >= tempCustomer->getTimestamp()) //Can store the customer
            {
                tempCustomer->printGetCall();
                customer[tempCustomer->getStatus()].insertBack(tempCustomer);
                //Store it
                //cout<<"\tStoring "<<tempCustomer->getName()<<" to stack\n";
                if(num <= 0)//nothing to read: set to false
                {
                    flag = false;
                    break;
                }
                else//If something else to read
                {
                    //cout << "\tNum is: "<<num<<endl;
                    tempCustomer = new Customer;
                    cin>>t>>n>>s>>d;
                    tempCustomer->set(t,n,s,d);
                    //cout << "\tReading "<<tempCustomer->getName()<<endl;
                    num --;//Remain num minus
                }

            }
            else break; //Time not meet, break it.
        }
        //Handle Part:
        //cout<<"-----3-----"<<endl;
        if(remainTick == 0)
        {
            Customer* T = NULL;
            for(int i = 3;i >= 0;i --)
            {
                if(!customer[i].isEmpty())
                {
                    T = customer[i].removeFront();
                    break;
                }
            }
            if(T!=NULL)
            {
                T->printAnserCall();
                remainTick = T->getDuration();
                delete T;
            }
        }
        if(remainTick > 0) remainTick--;
        currTick++;
    }
    cout<<"Starting tick #"<<currTick<<endl;
}
    