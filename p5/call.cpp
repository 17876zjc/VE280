#include <iostream>
#include <string>
#include <cstdlib>
#include "dlist.h"
using namespace std;

enum Status{ //Status enum
    regular,silver,gold,platinum
};

string FullStatus(Status a);
//EFFECTS: convert the status enumerate to string
//MODIFIES: Nothing

Status Str2Status(string str);
//EFFECTS: convert a string to the corresponding enumerate
//MODIFIES: Nothing

class Customer //Customer class
{
    private:
        int timestamp;
        string name;
        Status status;
        int duration;
    public:
        Customer(){};
        //EFFECTS: Default constructor
        //MODIFIES: Nothing
        void set(int,string,string,int);
        //EFFECTS: Setup the opject
        //MODIFIES: this
        int getTimestamp()const{return timestamp;};
        //EFFECTS: Return the timestamp
        //MODIFIES: Nothing
        int getStatus()const{return (int)status;};
        //EFFECTS: Return status
        //MODIFIES: Nothing
        int getDuration()const{return duration;};
        //EFFECTS: Return duration
        //MODIFIES: Nothing
        string getName()const{return name;};
        //EFFECTS: Return name
        //MODIFIES: Nothing
        void printGetCall()const;
        //EFFECTS: Print the get call message
        //MODIFIES: Nothing
        void printAnserCall()const;
        //EFFECTS: Print the Anser call message
        //MODIFIES: Nothing
        ~Customer(){};
        //EFFECTS: Default destructor
        //MODIFIES: Nothing
};

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
    if(num == 0)
    {
        cout<<"Starting tick #"<<currTick<<endl;
        return 0;
    }
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

string FullStatus(Status a) //Convert a status enum to string
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

Status Str2Status(string str) //Convert a string to the status enum
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

void Customer::set(int t, string n, string s,int d) //Set a customer
{
    timestamp = t;
    name = n;
    duration = d;
    status = Str2Status(s);
}

void Customer::printGetCall()const //Get call message
{
    cout<<"Call from "<<name<<" a "<<FullStatus(status)<<" member"<<endl;
}

void Customer::printAnserCall()const{ //Answer call message
    cout<<"Answering call from "<<name<<endl;
}
