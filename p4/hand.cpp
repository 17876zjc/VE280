#include "hand.h"

Hand::Hand()
{
    curValue.count = 0;
    curValue.soft = false;
}

void Hand::discardAll()
{
    *this = Hand();
}

void Hand::addCard(Card c)
{
    // If adding A to a hand containing A
    int pt = static_cast<int>(c.spot);
    if (pt <= 8)
    {
        pt += 2;
    }
    else if(pt <= 11)
    {
        pt = 10;
    }
    else
    {
        pt = 1;
    }
    curValue.count += pt;
    if(curValue.count > 11)
    {
        curValue.soft = false;
    }
    else if(pt == 1)
    {
        if(curValue.count <= 11)
        {
            curValue.soft = true;
        }
    }
}

HandValue Hand::handValue() const
{
    if(curValue.soft)
    {
        HandValue temp = curValue;
        temp.count+=10;
        return temp;
    }
    else
    {
        return curValue;
    }
}