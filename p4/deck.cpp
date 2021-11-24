#include "deck.h"
#include <iostream>
using namespace std;
//////////////////
Deck::Deck()
{
    next = 0;
    int count = 0;
    for(int i =0;i < 4; i++)
    {
        for(int j = 0;j < 13; j++)
        {
            deck[count].suit = Suit(i);
            deck[count].spot = Spot(j);
            count ++;
        }
    }
    //////////////////
}

void Deck::reset()
{
    *this = Deck();
}

void Deck::shuffle(int n)
{
    next = 0;

    Card newdeck[DeckSize];
    int leftSize = n;
    int rightSize = DeckSize-n;
    int min = leftSize < rightSize ? leftSize : rightSize;
    for(int i = 0; i < min ; i ++)
    {
        newdeck[2*i] = deck[n+i];
        newdeck[2*i+1] = deck[i];
    }
    if(n < DeckSize - n)
    {
        for(int i = 2*n; i < DeckSize; i ++)
        {
            newdeck[i] = deck[i];
        }
    }
    else if (n > DeckSize - n)
    {
        for(int i = 2*(DeckSize - n); i < DeckSize; i++)
        {
            newdeck[i] = deck[i-DeckSize+n];
            //DeckSize - n + i - 2*(DeckSize-n)
        }
    }
    for(int i = 0; i < DeckSize ; i++)
    {   
        deck[i] = newdeck[i];
        //cout<<(int)deck[i].spot<<"\t"<<(int)deck[i].suit<<endl;
    }
}

Card Deck::deal()
{
    if(!cardsLeft())
    {
        throw DeckEmpty();
    }
    else
    {
        next++;
        return deck[next-1];
    }
    //////////////////
}

int Deck::cardsLeft()
{
    return DeckSize-next;
    //////////////////
}