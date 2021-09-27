#pragma once
#include <vector>

using namespace std;

class Cards {

	// could have enum values for the card types
	enum cardType { bomb, reinforcement, blockade, airlift, diplomacy };


};

class Deck {

public:

	

private:

	// vector that contains a list of Card objects
	vector<Cards*> cards;

	Cards* draw();
	void returnToDeck(Cards);

};


class Hand {

public:

private:

	// vector that contains a list of Card objects
	vector<Cards*> cards;

};