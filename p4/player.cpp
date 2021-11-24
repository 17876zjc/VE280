#include "player.h" 

class SimplePlayer:public Player
{
    public:
        int bet(unsigned int bankroll,unsigned int minimum)
        {
            return minimum;
        };
        //////////////////
        bool draw(Card dealer, const Hand &player)
        {
            HandValue hand = player.handValue();
            int dealerPoint = static_cast<int>(dealer.spot) + 2;
            if(player.handValue().soft == false)
            {
                if(hand.count <= 11)
                {
                    return true;
                }
                else if (hand.count == 12)
                {
                    if(dealerPoint == 4 ||dealerPoint == 5||dealerPoint == 6)
                    {
                        return false;
                    }
                    else
                    {
                        return true;
                    }
                }//////////////////   
                else if (hand.count >= 13 && hand.count <= 16)
                {
                    if(dealerPoint >= 2 && dealerPoint <= 6)
                    {
                        return false;
                    }
                    else
                    {
                        return true;
                    }
                }
                else
                {
                    return false;
                }
            }
            else
            {
                if(hand.count <= 17)
                {
                    return true;
                }
                else if(hand.count == 18)
                {
                    if(dealerPoint == 2||dealerPoint == 7||dealerPoint == 8)
                    {
                        return false;
                    }
                    else
                    {
                        return true;
                    }
                }
                else
                {
                    return false;
                }
            }//////////////////        
        };
        void expose(Card c){};
        void shuffled(){};
};

static SimplePlayer simplePlayer;
extern Player *get_Simple()
{
    return &simplePlayer;
};


class CountingPlayer : public Player
{   
    private:
        int count = 0;
    public:
        int bet(unsigned int bankroll,unsigned int minimum)
        {
            if(count >= 2 && bankroll >= 2* minimum)
            {
                return 2 * minimum;
            }
            else
            {
                return minimum;
            }//////////////////
        };

        bool draw(Card dealer, const Hand &player)
        {
            return simplePlayer.draw(dealer,player);
        };

        void expose(Card c)
        {
            int point = static_cast<int>(c.spot)+2;
            if(point >= 2 && point <= 6)
            {
                count++;
            }
            else if(point >= 10)
            {
                count--;
            }//////////////////
        };
        void shuffled()
        {
            count = 0;
        };
};

static CountingPlayer countingPlayer;
extern Player *get_Counting()
{   
    return &countingPlayer;//////////////////   
};