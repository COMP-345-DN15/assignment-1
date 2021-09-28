#pragma once
#include <iostream>
#include <vector>
#include "Cards.h"
#include "Orders.h"
#include "Map.h"

using namespace std;

class Player {

public:

	// vectors that contain a list of Territory objects
	vector<Territory*> listOfTerritoriesOwned;
	vector<Territory*> listOfTerritoriesToAttack;
	vector<Territory*> listOfTerritoriesToDefend;


private:

	string playerName;

	// vector that contains a list of Card objects
	vector<Cards*> listOfCards;

	// vector that contains a list of Orders objects
	vector<Order*> listOfOrders;

	//void issueOrder();

};

