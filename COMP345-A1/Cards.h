#pragma once
#include <vector>

using namespace std;

class Cards {

	// could have enum values for the card types
	enum cardType { bomb, reinforcement, blockade, airlift, diplomacy };
	cardType ctype;

	public:
	//special order played by the player and sent back to the deck once it is played
		Cards();
		int display_card();
		Cards(int x);
		void play();


};

class Deck {

private:

	// vector that contains a list of Card objects
	Cards card;
	vector<Cards> cards;
	

public:
	Deck();
	void add_to_deck(Cards c);
	void print_deck();
	Cards draw();
	void returnToDeck(Cards);
	


};


class Hand {

public:

private:

	// vector that contains a list of Card objects
	vector<Cards> cards;

};