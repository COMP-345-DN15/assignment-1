#include "Cards.h"
#include<iostream>
using namespace std;



int const deck_size=25;
int const limit_card_type= 5;


enum cardType { bomb, reinforcement, blockade, airlift, diplomacy };

//Card constructor


Cards::Cards(int x){

if (x ==0)
    ctype=bomb;
if (x==1)
    ctype=reinforcement;
if (x==2)
    ctype=blockade;
if (x==3)
    ctype=airlift;
if (x==4)
    ctype=diplomacy;

}

int Cards::display_card(){
    return ctype;
}

//adding the card to the deck
void Deck::add_to_deck(Cards c){
    cards.push_back(c);
}

void Deck::print_deck(){
    for (int i=0; i<cards.size(); i++)
       std::cout << cards.at(i).display_card() << endl;

}

//Deck Constructor
//initializing a deck of cards 
Deck::Deck() {

    cout << "initializing Deck()" << endl;
    
        for (int count= 0; count<5; count++)
        {
            Cards card;

                for (int count = 0; count < 5; count++) {
                    card = Cards(count);
                    add_to_deck(card);
                }

        }


}





//Hand cobstructor

