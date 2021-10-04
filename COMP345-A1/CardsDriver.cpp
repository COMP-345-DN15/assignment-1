#include<iostream>
#include <vector>

using namespace std;

// Cards Class
class Cards {
    enum cardType { bomb, reinforcement, blockade, airlift, diplomacy };
	cardType ctype;    


public:
    //constructor

    Cards() {}

    Cards(int x){

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

    //
    string display_card(){
    if (ctype==0)
        return "bomb";

    if (ctype==1)
        return "reinforcement";

    if (ctype==2)
        return "blockade";

    if (ctype==3)
        return "airlift";

    if (ctype==4)
        return "diplomacy";
    }




// };

class Deck {

    private:
	// vector that contains a list of Card objects
	Cards card;
	vector<Cards> cards;
	

    public:
        Deck() {
            // std::cout << "Deck()" << endl;
            
            for (int count= 0; count<5; count++)
            {
                
                    for (int count = 0; count < 5; count++) {
                         Cards c = Cards(count);
                         add_to_deck(c);
                    }

            }

        }   

        //adding the card to the deck
            void add_to_deck(Cards c){
                
                cards.push_back(c);
            }


            void print_deck(){
            for (int i=0; i<cards.size(); i++)

             std::cout << cards.at(i).display_card() << endl;

            }

            void shuffle_deck(){

            }


;
};

    



//  Cards Driver

int main(){

    Deck d;
    d.print_deck();

    return 0;

};