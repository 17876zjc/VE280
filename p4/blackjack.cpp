#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>

#include "deck.h"
#include "hand.h"
#include "player.h"
#include "rand.h"

using namespace std;

void deckShuffle(Deck& deck, Player * player);

int main(int argc, char*argv[])
{
    const int minimum = 5;
    int bankroll = atoi(argv[1]);
    int hands = atoi(argv[2]);
    string type = string(argv[3]);
    Player* player;
    if(type == "simple") player = get_Simple();
    else if(type == "counting") player = get_Counting();
    else
    {
        cerr<<"No matching player type!"; exit(0);
    }
    
    Deck deck= Deck();
    deckShuffle(deck,player);
    int thishand;
    for(thishand = 1; thishand <= hands; thishand++)
    {
        if(bankroll < minimum)
        {
            break;   
        }
        cout << "Hand " << thishand << " bankroll " << bankroll << endl;
        if(deck.cardsLeft() < 20)
        {
            deckShuffle(deck,player);
        }
        Hand playerHand = Hand();
        Hand dealerHand = Hand();

        int wager = player->bet(bankroll,minimum);
        cout << "Player bets " << wager << endl;
        
        Card card;
        card = deck.deal();
        cout << "Player dealt "<<SpotNames[static_cast<int>(card.spot)]<<" of "<<SuitNames[static_cast<int>(card.suit)]<<endl;
        player->expose(card);
        playerHand.addCard(card);

        card = deck.deal();
        cout << "Dealer dealt "<<SpotNames[static_cast<int>(card.spot)]<<" of "<<SuitNames[static_cast<int>(card.suit)]<<endl;
        player->expose(card);
        dealerHand.addCard(card);
        Card dealerExp = card;

        card = deck.deal();
        cout << "Player dealt "<<SpotNames[static_cast<int>(card.spot)]<<" of "<<SuitNames[static_cast<int>(card.suit)]<<endl;
        player->expose(card);
        playerHand.addCard(card);

        card = deck.deal();
        //cout << "Dealer dealt "<<SpotNames[static_cast<int>(card.spot)]<<" of "<<SuitNames[static_cast<int>(card.suit)]<<endl;
        dealerHand.addCard(card);
        Card dealerHole = card;

        if(playerHand.handValue().count == 21)
        {
            cout << "Player dealt natural 21\n";
            bankroll += static_cast<int>(wager * 3 / 2);
            continue;
        }
        while(playerHand.handValue().count < 21)
        {
            if(player->draw(dealerExp,playerHand))
            {
                card = deck.deal();
                cout << "Player dealt "<<SpotNames[static_cast<int>(card.spot)]<<" of "<<SuitNames[static_cast<int>(card.suit)]<<endl;
                player->expose(card);
                playerHand.addCard(card);
                continue;
            }
            break;
        }
        cout << "Player's total is " << playerHand.handValue().count << endl;
        if(playerHand.handValue().count > 21)
        {
            cout << "Player busts\n";
            bankroll -= wager;
            continue;
        }

        cout<<"Dealer's hole card is "<<SpotNames[static_cast<int>(dealerHole.spot)]<<" of "<<SuitNames[static_cast<int>(dealerHole.suit)]<<endl;
        player->expose(dealerHole);
        while (dealerHand.handValue().count < 17)
        {
            card = deck.deal();
            cout << "Dealer dealt "<<SpotNames[static_cast<int>(card.spot)]<<" of "<<SuitNames[static_cast<int>(card.suit)]<<endl;
            player->expose(card);
            dealerHand.addCard(card);
        }
        cout << "Dealer's total is " << dealerHand.handValue().count << endl;
        if(dealerHand.handValue().count > 21)
        {
            cout << "Dealer busts\n";
            bankroll += wager;
            continue;
        }

        if(playerHand.handValue().count > dealerHand.handValue().count)
        {
            cout << "Player wins\n";
            bankroll += wager;
        }
        else if(playerHand.handValue().count < dealerHand.handValue().count)
        {
            cout << "Dealer wins\n";
            bankroll -= wager;
        }
        else
        {
            cout << "Push\n";
        }
    }

    cout << "Player has " << bankroll << " after " << thishand-1 << " hands\n";
    return 0;
}

void deckShuffle(Deck& deck, Player * player)
{
    cout << "Shuffling the deck\n";
    for(int i = 0;i < 7;i++)
    {
        int cut = get_cut();
        cout << "cut at " << cut << endl;
        deck.shuffle(cut);
        player->shuffled();
    }
}