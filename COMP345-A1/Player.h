#pragma once
#include <iostream>
#include <vector>
#include "Deck.h"
#include "OrdersList.h"
#include "Map.h"

using namespace std;

class Player {

public:
	
	string playerName;
	// vectors that contain a list of Territory objects
	vector<Territory*> listOfTerritoriesOwned;
	vector<Territory*> listOfTerritoriesToAttack;
	vector<Territory*> listOfTerritoriesToDefend;
	
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
	void issueOrder();

private:

	// vector that contains a list of Card objects
	vector<Cards*> listOfCards;

	// vector that contains a list of Orders objects
	vector<Order*> listOfOrders;


};

